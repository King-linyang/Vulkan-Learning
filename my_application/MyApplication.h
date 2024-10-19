//
// Created by wangly on 2024/10/15.
//
#pragma once

#include "../../my_framework/core.h"
#include "../my_framework/MyVulkanDevices.h"
#include "../../my_framework/MyValidationLayers.h"
#include "../../my_framework/MyVulkanShaderCompile.h"
#include "../../my_framework/MyVulkanFixedFuncs.h"
#include "../../my_framework/MyVulkanDraw.h"
#include "MyEventLearning.h"

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

class MyApplication {
public:
    MyApplication() = default;

    ~MyApplication() = default;

    // 实例化方法
    void run();

    //创建窗口表面
    void createSurface();

    //创建渲染过程
    void createRenderPass();

    //清理工作
    void cleanUpRenderPass() {
        vkDestroyRenderPass(device, renderPass, nullptr);
    }

    //创建一个图形管线
    void createGraphicsPipeline();

    //创建着色器模块 采用一个以字节码为参数的缓冲区，并从中创建一个 VkShaderModule
    VkShaderModule createShaderModule(const std::vector<char> &code);

    //销毁图形管线
    void cleanUpGraphicsPipeline() {
        vkDestroyPipeline(device, graphicsPipeline, nullptr);
    }

    //销毁管道
    void cleanUpPipelineLayout() {
        vkDestroyPipelineLayout(device, pipelineLayout, nullptr);
    }

private:
    // 交换链
    MyVulkanSwapChain myVulkanSwapChain;
    //固定功能
    MyVulkanFixedFuncs myVulkanFixedFuncs;
    //绘图
    MyVulkanDraw myVulkanDraw;

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
private:
    // 初始化窗口
    void initWindow();

    // 初始化Vulkan
    void initVulkan();

    // 主循环
    void mainLoop();

    // 清理资源
    void cleanup();

    // 创建实例
    void createInstance();
};


