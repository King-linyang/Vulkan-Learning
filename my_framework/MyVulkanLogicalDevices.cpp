//
// Created by wangly on 2024/10/16.
// 逻辑设备

#include "MyVulkanLogicalDevices.h"

void
MyVulkanLogicalDevices::createLogicalDevice(VkPhysicalDevice *physicalDevice, VkDevice *device,
                                            VkQueue *graphicsQueue, VkSurfaceKHR *surface, VkQueue presentQueue) {
    //单个队列系列的队列数量
    QueueFamilyIndices indices = MyVulkanPhysicalDevices::findQueueFamilies(physicalDevice, surface);

    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    std::set<uint32_t> uniqueQueueFamilies = {
            indices.graphicsFamily.value(),
            indices.presentFamily.value()
    };
    //队列分配优先级
    float queuePriority = 1.0f;
    for (uint32_t queueFamily: uniqueQueueFamilies) {
        VkDeviceQueueCreateInfo queueCreateInfo{};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = queueFamily;
        queueCreateInfo.queueCount = 1;
        queueCreateInfo.pQueuePriorities = &queuePriority;
        queueCreateInfos.push_back(queueCreateInfo);
    }

    //使用的设备功能
    VkPhysicalDeviceFeatures deviceFeatures{};

    //创建逻辑设备
    VkDeviceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    //添加指向队列创建信息和设备功能结构的指针
    createInfo.pQueueCreateInfos = queueCreateInfos.data();
    createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());

    createInfo.pEnabledFeatures = &deviceFeatures;

    //启用设备扩展
    createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
    createInfo.ppEnabledExtensionNames = deviceExtensions.data();

    if (enableValidationLayers) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();
    } else {
        createInfo.enabledLayerCount = 0;
    }

    if (vkCreateDevice(*physicalDevice, &createInfo, nullptr, device) != VK_SUCCESS) {
        throw std::runtime_error("failed to create logical device!");
    }
    //检索队列句柄
    vkGetDeviceQueue(*device, indices.graphicsFamily.value(), 0, graphicsQueue);
    vkGetDeviceQueue(*device, indices.presentFamily.value(), 0, &presentQueue);
}
