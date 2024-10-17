//
// Created by wangly on 2024/10/17.
// 绘图

#include "MyVulkanDraw.h"

void MyVulkanDraw::createFrameBuffers(MyVulkanImageView myVulkanImageView, MyVulkanRenderPass myVulkanRenderPass,
                                      MyVulkanSwapChain myVulkanSwapChain, VkDevice device) {
    swapChainFramebuffers.resize(myVulkanImageView.getSwapChainImageViews().size());
    //遍历视图创建帧缓冲区
    for (size_t i = 0; i < myVulkanImageView.getSwapChainImageViews().size(); i++) {
        VkImageView attachments[] = {
                myVulkanImageView.getSwapChainImageViews()[i]
        };

        VkFramebufferCreateInfo framebufferInfo{};
        framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferInfo.renderPass = myVulkanRenderPass.getRenderPass();
        framebufferInfo.attachmentCount = 1;
        framebufferInfo.pAttachments = attachments;
        framebufferInfo.width = myVulkanSwapChain.getSwapChainExtent().width;
        framebufferInfo.height = myVulkanSwapChain.getSwapChainExtent().height;
        framebufferInfo.layers = 1;

        if (vkCreateFramebuffer(device, &framebufferInfo, nullptr, &swapChainFramebuffers[i]) != VK_SUCCESS) {
            throw std::runtime_error("failed to create framebuffer!");
        }
    }
}
