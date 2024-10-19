//
// Created by wangly on 2024/10/17.
// 绘图

#include "MyVulkanDraw.h"

void MyVulkanDraw::createFrameBuffers(VkRenderPass renderPass, MyVulkanSwapChain myVulkanSwapChain,
                                      VkDevice *device) {
    swapChainFramebuffers.resize(swapChainImageViews.size());
    //遍历视图创建帧缓冲区
    for (size_t i = 0; i < swapChainImageViews.size(); i++) {
        VkImageView attachments[] = {
                swapChainImageViews[i]
        };

        VkFramebufferCreateInfo framebufferInfo{};
        framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferInfo.renderPass = renderPass;
        framebufferInfo.attachmentCount = 1;
        framebufferInfo.pAttachments = attachments;
        framebufferInfo.width = myVulkanSwapChain.getSwapChainExtent().width;
        framebufferInfo.height = myVulkanSwapChain.getSwapChainExtent().height;
        framebufferInfo.layers = 1;

        if (vkCreateFramebuffer(*device, &framebufferInfo, nullptr, &swapChainFramebuffers[i]) != VK_SUCCESS) {
            throw std::runtime_error("failed to create framebuffer!");
        }
    }
}

void MyVulkanDraw::createCommandPool(VkPhysicalDevice *physicalDevice, VkSurfaceKHR *surface, VkDevice *device) {
    QueueFamilyIndices queueFamilyIndices = MyVulkanDevices::findQueueFamilies(physicalDevice, surface);

    VkCommandPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();

    if (vkCreateCommandPool(*device, &poolInfo, nullptr, &commandPool) != VK_SUCCESS) {
        throw std::runtime_error("failed to create command pool!");
    }

}

//创建多个命令缓冲区
void MyVulkanDraw::createCommandBuffers(VkDevice *device) {
    //调整命令缓冲区大小--大小和同时处理的帧数保持一致
    commandBuffers.resize(MAX_FRAMES_IN_FLIGHT);

    //每个帧都应该有自己的命令缓冲区、信号量集和栅栏
    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.commandPool = commandPool;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandBufferCount = (uint32_t) commandBuffers.size();

    //创建多个
    if (vkAllocateCommandBuffers(*device, &allocInfo, commandBuffers.data()) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate command buffers!");
    }
}

void MyVulkanDraw::recordCommandBuffer(uint32_t imageIndex, VkRenderPass renderPass, VkExtent2D swapChainExtent,
                                       VkPipeline graphicsPipeline) {
    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

    if (vkBeginCommandBuffer(commandBuffers[currentFrame], &beginInfo) != VK_SUCCESS) {
        throw std::runtime_error("failed to begin recording command buffer!");
    }
    //启动渲染过程
    VkRenderPassBeginInfo renderPassInfo{};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassInfo.renderPass = renderPass;
    renderPassInfo.framebuffer = swapChainFramebuffers[imageIndex];

    renderPassInfo.renderArea.offset = {0, 0};
    renderPassInfo.renderArea.extent = swapChainExtent;

    VkClearValue clearColor = {{{0.0f, 0.0f, 0.0f, 1.0f}}};
    renderPassInfo.clearValueCount = 1;
    renderPassInfo.pClearValues = &clearColor;

    vkCmdBeginRenderPass(commandBuffers[currentFrame], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

    vkCmdBindPipeline(commandBuffers[currentFrame], VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);

    VkViewport viewport{};
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = static_cast<float>(swapChainExtent.width);
    viewport.height = static_cast<float>(swapChainExtent.height);
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;
    vkCmdSetViewport(commandBuffers[currentFrame], 0, 1, &viewport);

    VkRect2D scissor{};
    scissor.offset = {0, 0};
    scissor.extent = swapChainExtent;
    vkCmdSetScissor(commandBuffers[currentFrame], 0, 1, &scissor);

    //发出draw命令
    vkCmdDraw(commandBuffers[currentFrame], 3, 1, 0, 0);
    vkCmdEndRenderPass(commandBuffers[currentFrame]);
    if (vkEndCommandBuffer(commandBuffers[currentFrame]) != VK_SUCCESS) {
        throw std::runtime_error("failed to record command buffer!");
    }
}

void
MyVulkanDraw::drawFrame(VkDevice *device, VkSwapchainKHR *swapChain, MyVulkanSwapChain *myVulkanSwapChain,
                        VkPipeline graphicsPipeline, VkQueue graphicsQueue, VkQueue presentQueue,
                        VkPhysicalDevice *physicalDevice, VkSurfaceKHR *surface,
                        GLFWwindow *window, VkRenderPass renderPass) {
    //等待上一帧
    vkWaitForFences(*device, 1, &inFlightFences[currentFrame], VK_TRUE, UINT64_MAX);

    //获取下一个图像
    uint32_t imageIndex;
    VkResult result = vkAcquireNextImageKHR(*device, *swapChain, UINT64_MAX, imageAvailableSemaphores[currentFrame],
                                            VK_NULL_HANDLE, &imageIndex);
    //如果窗口大小改变，重新创建swapchain
    if (result == VK_ERROR_OUT_OF_DATE_KHR) {
        recreateSwapChain(physicalDevice, surface, window, swapChain, device, myVulkanSwapChain, renderPass);
        return;
    } else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
        throw std::runtime_error("failed to acquire swap chain image!");
    }

    //调用手动将 fence 重置为 unsignaled 状态
    vkResetFences(*device, 1, &inFlightFences[currentFrame]);

    //录制命令缓冲区
    vkResetCommandBuffer(commandBuffers[currentFrame], 0);
    recordCommandBuffer(imageIndex, renderPass, myVulkanSwapChain->getSwapChainExtent(),
                        graphicsPipeline);
    //提交命令缓冲区
    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

    VkSemaphore waitSemaphores[] = {imageAvailableSemaphores[currentFrame]};
    VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = waitSemaphores;
    submitInfo.pWaitDstStageMask = waitStages;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &commandBuffers[currentFrame];


    VkSemaphore signalSemaphores[] = {renderFinishedSemaphores[currentFrame]};
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = signalSemaphores;


    if (vkQueueSubmit(graphicsQueue, 1, &submitInfo, inFlightFences[currentFrame]) != VK_SUCCESS) {
        throw std::runtime_error("failed to submit draw command buffer!");
    }

    VkPresentInfoKHR presentInfo{};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores = signalSemaphores;

    VkSwapchainKHR swapChains[] = {*swapChain};
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = swapChains;
    presentInfo.pImageIndices = &imageIndex;

    vkQueuePresentKHR(presentQueue, &presentInfo);

    if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || framebufferResized) {
        framebufferResized = false;
        recreateSwapChain(physicalDevice, surface, window, swapChain, device, myVulkanSwapChain, renderPass);
    } else if (result != VK_SUCCESS) {
        throw std::runtime_error("failed to present swap chain image!");
    }

    //更新帧计数器--到下一帧
    currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
}

void MyVulkanDraw::createSyncObjects(VkDevice *device) {
    //调整大小为同时处理的帧数
    imageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
    renderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
    inFlightFences.resize(MAX_FRAMES_IN_FLIGHT);
    VkSemaphoreCreateInfo semaphoreInfo{};
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    VkFenceCreateInfo fenceInfo{};
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        if (vkCreateSemaphore(*device, &semaphoreInfo, nullptr, &imageAvailableSemaphores[i]) != VK_SUCCESS ||
            vkCreateSemaphore(*device, &semaphoreInfo, nullptr, &renderFinishedSemaphores[i]) != VK_SUCCESS ||
            vkCreateFence(*device, &fenceInfo, nullptr, &inFlightFences[i]) != VK_SUCCESS) {

            throw std::runtime_error("failed to create synchronization objects for a frame!");
        }
    }
}

void MyVulkanDraw::recreateSwapChain(VkPhysicalDevice *physicalDevice, VkSurfaceKHR *surface,
                                     GLFWwindow *window, VkSwapchainKHR *swapChain, VkDevice *device,
                                     MyVulkanSwapChain *myVulkanSwapChain, VkRenderPass renderPass) {
    vkDeviceWaitIdle(*device);

    cleanupSwapChain(*device, swapChain);

    myVulkanSwapChain->createSwapChain(physicalDevice, surface, window, swapChain, device);
    createImageViews(device, myVulkanSwapChain);
    createFrameBuffers(renderPass, *myVulkanSwapChain, device);
}

void MyVulkanDraw::createImageViews(VkDevice *device, MyVulkanSwapChain *myVulkanSwapChain) {
    //调整列表的大小以适合我们将创建的所有图像视图
    swapChainImageViews.resize(myVulkanSwapChain->getSwapChainImages().size());
    //设置迭代所有交换链映像的循环
    for (size_t i = 0; i < myVulkanSwapChain->getSwapChainImages().size(); i++) {
        //subresourceRange 字段描述图像的用途以及应访问图像的哪个部分。我们的图像将用作颜色目标，无需任何 mipmap 级别或多个图层。
        VkImageViewCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        createInfo.image = myVulkanSwapChain->getSwapChainImages()[i];

        //viewType 参数允许您将图像视为 1D 纹理、2D 纹理、3D 纹理和立方体贴图。
        createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        createInfo.format = myVulkanSwapChain->getSwapChainImageFormat();

        //components 字段允许您重排颜色通道。例如，可以将所有通道映射到单色纹理的红色通道。您还可以将 0 和 1 的常量值映射到通道
        createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;

        //subresourceRange 字段描述图像的用途以及应访问图像的哪个部分。我们的图像将用作颜色目标，无需任何 mipmap 级别或多个图层。
        createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        createInfo.subresourceRange.baseMipLevel = 0;
        createInfo.subresourceRange.levelCount = 1;
        createInfo.subresourceRange.baseArrayLayer = 0;
        createInfo.subresourceRange.layerCount = 1;

        //创建 image 视图
        if (vkCreateImageView(*device, &createInfo, nullptr, &swapChainImageViews[i]) != VK_SUCCESS) {
            throw std::runtime_error("failed to create image views!");
        }
    }
}

void MyVulkanDraw::cleanupSwapChain(VkDevice device, VkSwapchainKHR *swapChain) {
    for (auto framebuffer: swapChainFramebuffers) {
        vkDestroyFramebuffer(device, framebuffer, nullptr);
    }

    for (auto imageView: swapChainImageViews) {
        vkDestroyImageView(device, imageView, nullptr);
    }

    vkDestroySwapchainKHR(device, *swapChain, nullptr);
}
