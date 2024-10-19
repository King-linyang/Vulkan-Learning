//
// Created by wangly on 2024/10/19.
// vulkan 设备，物理和逻辑设备

#pragma once

#include "MyVulkanSwapChain.h"
#include "MyValidationLayers.h"
#include <optional>
#include <stdexcept>
#include <vector>
#include <set>
#include "core.h"

//队列族索引
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

class MyVulkanDevices {
public:
    MyVulkanDevices() = default;

    ~MyVulkanDevices() = default;

    //选择物理设备 显卡等
    static void pickPhysicalDevice(VkInstance *instance, VkPhysicalDevice *physicalDevice, VkSurfaceKHR *surface);

    //寻找一个支持 graphics 命令的队列
    static QueueFamilyIndices findQueueFamilies(VkPhysicalDevice *device, VkSurfaceKHR *surface);

    //检查设备是否支持
    static bool checkDeviceExtensionSupport(VkPhysicalDevice device);

    //创建逻辑设备
    static void
    createLogicalDevice(VkPhysicalDevice *physicalDevice, VkDevice *device, VkQueue *graphicsQueue, VkSurfaceKHR *surface,
                        VkQueue *presentQueue);

private:
    static bool isDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR surface);
};

