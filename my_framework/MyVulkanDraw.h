//
// Created by wangly on 2024/10/17.
// 绘图

#pragma once

#include <vector>
#include "core.h"
#include "MyVulkanRenderPass.h"
#include "MyVulkanImageView.h"
#include "MyVulkanGraphicsPipeline.h"

class MyVulkanDraw {
public:
    MyVulkanDraw() = default;

    ~MyVulkanDraw() = default;

    //创建帧缓冲区
    void createFrameBuffers(MyVulkanImageView myVulkanImageView, MyVulkanRenderPass myVulkanRenderPass,
                            MyVulkanSwapChain myVulkanSwapChain, VkDevice *device);

    //创建命令池
    void createCommandPool(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, VkDevice *device);

    //创建命令缓冲区
    void createCommandBuffer(VkDevice *device);

    //命令缓冲区录制 处理将要执行的命令写入命令缓冲区的
    void recordCommandBuffer(uint32_t imageIndex, VkRenderPass renderPass, VkExtent2D swapChainExtent,
                             VkPipeline graphicsPipeline);

    //绘制
    void drawFrame(VkDevice device, VkSwapchainKHR swapChain, VkRenderPass renderPass, VkExtent2D swapChainExtent,
                   VkPipeline graphicsPipeline, VkQueue graphicsQueue, VkQueue presentQueue);

    //创建同步对象
    void createSyncObjects(VkDevice device);


    //获取帧缓冲区
    std::vector<VkFramebuffer> getSwapChainFramebuffers() {
        return swapChainFramebuffers;
    }

    //清理命令池
    void cleanUpCommandPool(VkDevice device) {
        vkDestroyCommandPool(device, commandPool, nullptr);
    }

    //清理同步对象
    void cleanUpSyncObjects(VkDevice device) {
        vkDestroySemaphore(device, *renderFinishedSemaphore, nullptr);
        vkDestroySemaphore(device, *imageAvailableSemaphore, nullptr);
        vkDestroyFence(device, *inFlightFence, nullptr);
    }

private:
    //帧缓冲区
    std::vector<VkFramebuffer> swapChainFramebuffers;
    //命令池
    VkCommandPool commandPool;
    //命令缓冲区
    VkCommandBuffer commandBuffer;

    //信号量
    VkSemaphore *imageAvailableSemaphore;
    //渲染完成的信号
    VkSemaphore *renderFinishedSemaphore;
    //等待信号量
    VkFence *inFlightFence;
};

