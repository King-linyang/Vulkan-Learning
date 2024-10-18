//
// Created by wangly on 2024/10/16.
// 交换链

#pragma once

#include "MyVulkanPhysicalDevices.h"
#include <vector>
#include "core.h"
#include <algorithm>
#include <stdexcept>

//设备扩展
const std::vector<const char *> deviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
};
//Swap Chain 支持详情
struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

class MyVulkanSwapChain {
public:
    MyVulkanSwapChain() = default;

    ~MyVulkanSwapChain() = default;

    //获取交换链支持详情
    static SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR surface);

    //选择表面格式
    static VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);

    //选择交换链模式
    static VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);

    //选择交换范围
    static VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities, GLFWwindow *window);

    //创建交换链
    void createSwapChain(VkPhysicalDevice *physicalDevice, VkSurfaceKHR *surface, GLFWwindow *window,
                         VkSwapchainKHR *swapChain, VkDevice *device);

    //获取交换链图像
    std::vector<VkImage> getSwapChainImages() { return swapChainImages; }

    //获取交换链图像视图
    VkFormat getSwapChainImageFormat() { return swapChainImageFormat; }

    //获取交换链扩展
    VkExtent2D getSwapChainExtent() { return swapChainExtent; }

private:
    //交换链图像
    std::vector<VkImage> swapChainImages;
    //交换链图像视图
    VkFormat swapChainImageFormat;
    //交换链扩展
    VkExtent2D swapChainExtent{};
};

