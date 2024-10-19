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
    void createCommandPool(VkPhysicalDevice *physicalDevice, VkSurfaceKHR *surface, VkDevice *device);

    //创建多个命令缓冲区
    void createCommandBuffers(VkDevice *device);

    //命令缓冲区录制 处理将要执行的命令写入命令缓冲区的
    void recordCommandBuffer(uint32_t imageIndex, VkRenderPass renderPass, VkExtent2D swapChainExtent,
                             VkPipeline graphicsPipeline);

    //绘制
    void drawFrame(VkDevice *device, VkSwapchainKHR swapChain, VkRenderPass renderPass, VkExtent2D swapChainExtent,
                   VkPipeline graphicsPipeline, VkQueue graphicsQueue, VkQueue presentQueue);

    //为每一帧创建同步对象
    void createSyncObjects(VkDevice *device);


    //获取帧缓冲区
    std::vector<VkFramebuffer> getSwapChainFramebuffers() {
        return swapChainFramebuffers;
    }

    //清理命令池
    void cleanUpCommandPool(VkDevice *device) {
        vkDestroyCommandPool(*device, commandPool, nullptr);
    }

    //清理每一帧的同步对象
    void cleanUpSyncObjects(VkDevice *device) {
        //在释放命令池时会释放命令缓冲区，因此无需执行任何额外操作即可进行命令缓冲区清理
        for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
            vkDestroySemaphore(*device, renderFinishedSemaphores[i], nullptr);
            vkDestroySemaphore(*device, imageAvailableSemaphores[i], nullptr);
            vkDestroyFence(*device, inFlightFences[i], nullptr);
        }
    }

private:
    //帧缓冲区
    std::vector<VkFramebuffer> swapChainFramebuffers;
    //命令池
    VkCommandPool commandPool;

    //指定同时可以处理的帧数
    const int MAX_FRAMES_IN_FLIGHT = 2;
    //要每帧都使用正确的对象，我们需要跟踪当前帧。为此，我们将使用帧索引
    uint32_t currentFrame = 0;
    //为每一帧都创建一个命令缓冲区
    std::vector<VkCommandBuffer> commandBuffers;
    //每一帧的信号量
    std::vector<VkSemaphore> imageAvailableSemaphores;
    //每一帧渲染完成的信号
    std::vector<VkSemaphore> renderFinishedSemaphores;
    //每一帧飞行中的栅栏
    std::vector<VkFence> inFlightFences;
};

