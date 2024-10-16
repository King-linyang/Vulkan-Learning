//
// Created by wangly on 2024/10/16.
// 逻辑设备

#include <stdexcept>
#include "core.h"
#include "MyValidationLayers.h"
#include "MyVulkanLogicalDevices.h"
#include "MyVulkanPhysicalDevices.h"

void
MyVulkanLogicalDevices::createLogicalDevice(VkPhysicalDevice physicalDevice, VkDevice *device,
                                            VkQueue *graphicsQueue) {
    //单个队列系列的队列数量
    QueueFamilyIndices indices = MyVulkanPhysicalDevices::findQueueFamilies(physicalDevice);

    VkDeviceQueueCreateInfo queueCreateInfo{};
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.queueFamilyIndex = indices.graphicsFamily.value();
    queueCreateInfo.queueCount = 1;

    //队列分配优先级
    float queuePriority = 1.0f;
    queueCreateInfo.pQueuePriorities = &queuePriority;

    //使用的设备功能
    VkPhysicalDeviceFeatures deviceFeatures{};

    //创建逻辑设备
    VkDeviceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    //添加指向队列创建信息和设备功能结构的指针
    createInfo.pQueueCreateInfos = &queueCreateInfo;
    createInfo.queueCreateInfoCount = 1;

    createInfo.pEnabledFeatures = &deviceFeatures;
    createInfo.enabledExtensionCount = 0;

    if (enableValidationLayers) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();
    } else {
        createInfo.enabledLayerCount = 0;
    }

    if (vkCreateDevice(physicalDevice, &createInfo, nullptr, device) != VK_SUCCESS) {
        throw std::runtime_error("failed to create logical device!");
    }
    //检索队列句柄
    vkGetDeviceQueue(*device, indices.graphicsFamily.value(), 0, graphicsQueue);
}
