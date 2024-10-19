//
// Created by wangly on 2024/10/15.
//
#pragma once

#include "../../my_framework/core.h"
#include "../../my_framework/MyValidationLayers.h"
#include "../../my_framework/MyVulkanShaderCompile.h"
#include "../../my_framework/MyVulkanFixedFuncs.h"
#include "MyEventLearning.h"

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdint>
#include <limits>
#include <optional>
#include <set>

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;
//Swap Chain 支持详情
struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};


//设备队列族索引
struct QueueFamilyIndices {
    //图形队列家族索引
    std::optional<uint32_t> graphicsFamily;
    //呈现队列家族索引
    std::optional<uint32_t> presentFamily;

    bool isComplete() {
        return graphicsFamily.has_value() && presentFamily.has_value();
    }
};

//设备扩展
const std::vector<const char *> deviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
};


class MyApplication {
public:
    MyApplication() = default;

    ~MyApplication() = default;

    //选择物理设备 显卡等
    void pickPhysicalDevice();

    //寻找一个支持 graphics 命令的队列
    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice _physicalDevice);

    //检查设备是否支持
    bool checkDeviceExtensionSupport(VkPhysicalDevice _physicalDevice_t);

    bool isDeviceSuitable(VkPhysicalDevice _physicalDevice);

    //创建逻辑设备
    void createLogicalDevice();

    // 实例化方法，传入shader文件路径
    void run(const char *path);

    //创建窗口表面
    void createSurface();

    //创建渲染过程
    void createRenderPass();

    //创建一个图形管线
    void createGraphicsPipeline(const char *path);

    //创建着色器模块 采用一个以字节码为参数的缓冲区，并从中创建一个 VkShaderModule
    VkShaderModule createShaderModule(const std::vector<char> &code);

    //获取交换链支持详情
    SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice _physicalDevice);

    //选择表面格式
    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);

    //选择交换链模式
    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);

    //选择交换范围
    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities);

    //创建交换链
    void createSwapChain();

    //创建帧缓冲区
    void createFrameBuffers();

    //创建命令池
    void createCommandPool();

    //创建多个命令缓冲区
    void createCommandBuffers();

    //命令缓冲区录制 处理将要执行的命令写入命令缓冲区的
    void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

    //绘制
    void drawFrame();

    //重建交换链--适配窗口大小变化
    void recreateSwapChain();

    //为每一帧创建同步对象
    void createSyncObjects();

    //创建图像视图
    void createImageViews();

    //清理
    void cleanupSwapChain();

public:
    //窗口发生调整
    bool framebufferResized = false;
private:
    //固定功能
    MyVulkanFixedFuncs myVulkanFixedFuncs;

    // 窗口
    GLFWwindow *window{};
    // vulkan 实例，实例只有一个
    VkInstance instance{};
    //debug 信息
    VkDebugUtilsMessengerEXT debugMessenger{};
    //物理设备
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    //逻辑设备
    VkDevice device{};
    //图形队列
    VkQueue graphicsQueue{};
    //窗口表面
    VkSurfaceKHR surface{};
    //渲染队列
    VkQueue presentQueue{};
    //交换链
    VkSwapchainKHR swapChain;
    //渲染通道
    VkRenderPass renderPass;

    //管线布局
    VkPipelineLayout pipelineLayout;
    //图形管线
    VkPipeline graphicsPipeline;


    //交换链图像
    std::vector<VkImage> swapChainImages;
    //交换链图像视图
    VkFormat swapChainImageFormat;
    //交换链扩展
    VkExtent2D swapChainExtent{};


    //存储图像视图
    std::vector<VkImageView> swapChainImageViews;
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
private:
    // 初始化窗口
    void initWindow();

    // 初始化Vulkan
    void initVulkan(const char *string);

    // 主循环
    void mainLoop();

    // 清理资源
    void cleanup();

    // 创建实例
    void createInstance();
};


