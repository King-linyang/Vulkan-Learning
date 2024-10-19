////
//// Created by wangly on 2024/10/15.
////
//
//#pragma once
//
//#include "../../my_framework/core.h"
//#include "../../my_framework/MyVulkanImageView.h"
//#include "../../my_framework/MyVulkanGraphicsPipeline.h"
//#include "../../my_framework/MyValidationLayers.h"
//#include "../../my_framework/MyVulkanLogicalDevices.h"
//#include "../../my_framework/MyVulkanSurface.h"
//#include "../../my_framework/MyVulkanShaderCompile.h"
//#include "../../my_framework/MyVulkanFixedFuncs.h"
//#include "../../my_framework/MyVulkanRenderPass.h"
//#include "../../my_framework/MyVulkanDraw.h"
//
//#include <iostream>
//#include <stdexcept>
//#include <cstdlib>
//#include <vector>
//
//const uint32_t WIDTH = 800;
//const uint32_t HEIGHT = 600;
//
//class HelloTriangleApplication {
//public:
//    HelloTriangleApplication() = default;
//
//    ~HelloTriangleApplication() = default;
//
//    // 实例化方法
//    void run();
//
//private:
//    // 交换链
//    MyVulkanSwapChain myVulkanSwapChain;
//    //图像视图
//    MyVulkanImageView myVulkanImageView;
//    //图形渲染管线
//    MyVulkanGraphicsPipeline myVulkanGraphicsPipeline;
//    //固定功能
//    MyVulkanFixedFuncs myVulkanFixedFuncs;
//    //渲染过程
//    MyVulkanRenderPass myVulkanRenderPass;
//    //绘图
//    MyVulkanDraw myVulkanDraw;
//
//    // 窗口
//    GLFWwindow *window{};
//    // vulkan 实例，实例只有一个
//    VkInstance instance{};
//    //debug 信息
//    VkDebugUtilsMessengerEXT debugMessenger{};
//    //物理设备
//    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
//    //逻辑设备
//    VkDevice device{};
//    //图形队列
//    VkQueue graphicsQueue{};
//    //窗口表面
//    VkSurfaceKHR surface{};
//    //渲染队列
//    VkQueue presentQueue{};
//    //交换链
//    VkSwapchainKHR swapChain;
//private:
//    // 初始化窗口
//    void initWindow();
//
//    // 初始化Vulkan
//    void initVulkan();
//
//    // 主循环
//    void mainLoop();
//
//    // 清理资源
//    void cleanup();
//
//    // 创建实例
//    void createInstance();
//};
