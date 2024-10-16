//
// Created by wangly on 2024/10/16.
// 逻辑设备

#pragma once

class MyVulkanLogicalDevices {
public:
    MyVulkanLogicalDevices() = default;

    ~MyVulkanLogicalDevices() = default;

    //创建逻辑设备
    static void
    createLogicalDevice(VkPhysicalDevice physicalDevice, VkDevice *device, VkQueue *graphicsQueue, VkSurfaceKHR surface,
                        VkQueue presentQueue);
};
