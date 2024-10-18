//
// Created by wangly on 2024/10/16.
// 逻辑设备

#pragma once

#include <stdexcept>
#include <set>
#include "core.h"
#include "MyValidationLayers.h"
#include "MyVulkanPhysicalDevices.h"
#include "MyVulkanSwapChain.h"

class MyVulkanLogicalDevices {
public:
    MyVulkanLogicalDevices() = default;

    ~MyVulkanLogicalDevices() = default;

    //创建逻辑设备
    static void
    createLogicalDevice(VkPhysicalDevice *physicalDevice, VkDevice *device, VkQueue *graphicsQueue, VkSurfaceKHR *surface,
                        VkQueue presentQueue);
};
