//
// Created by wangly on 2024/10/16.
// 物理设备

#include "MyVulkanPhysicalDevices.h"

void MyVulkanPhysicalDevices::pickPhysicalDevice(VkInstance instance, VkPhysicalDevice *physicalDevice,
                                                 VkSurfaceKHR surface) {
    // 获取显卡设备数量
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
    //如果有 0 台设备支持 Vulkan，那么就没有必要再进一步了。
    if (deviceCount == 0) {
        throw std::runtime_error("failed to find GPUs with Vulkan support!");
    }
    //分配一个数组来保存所有 VkPhysicalDevice 句柄
    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

    //检查是否有任何物理设备满足我们将添加到该功能中的要求
    for (const auto &device: devices) {
        if (isDeviceSuitable(device, surface)) {
            *physicalDevice = device;
            break;
        }
    }

    if (physicalDevice == VK_NULL_HANDLE) {
        throw std::runtime_error("failed to find a suitable GPU!");
    }
}

//评估物理设备中的每一个并检查它们是否适合我们想要执行的操作
bool MyVulkanPhysicalDevices::isDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR surface) {
    QueueFamilyIndices indices = MyVulkanPhysicalDevices::findQueueFamilies(device, surface);

    bool extensionsSupported = checkDeviceExtensionSupport(device);
    //验证交换链支持是否足够
    bool swapChainAdequate = false;
    if (extensionsSupported) {
        //至少有一种受支持的图像格式和一种受支持的演示模式
        SwapChainSupportDetails swapChainSupport = MyVulkanSwapChain::querySwapChainSupport(device, surface);
        swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
    }
    return indices.isComplete() && extensionsSupported && swapChainAdequate;
}

bool MyVulkanPhysicalDevices::checkDeviceExtensionSupport(VkPhysicalDevice device) {
    //检查是否所有必需的扩展都包含在其中
    uint32_t extensionCount;
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

    std::vector<VkExtensionProperties> availableExtensions(extensionCount);
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

    std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

    for (const auto &extension: availableExtensions) {
        requiredExtensions.erase(extension.extensionName);
    }

    return requiredExtensions.empty();
}

QueueFamilyIndices MyVulkanPhysicalDevices::findQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surface) {
    QueueFamilyIndices indices;
    //检索队列列表
    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

    //需要找到至少一个支持 VK_QUEUE_GRAPHICS_BIT
    int i = 0;
    for (const auto &queueFamily: queueFamilies) {
        if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            indices.graphicsFamily = i;
        }
        //查找能够呈现到窗口表面的队列系列
        VkBool32 presentSupport = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);
        if (presentSupport) {
            indices.presentFamily = i;
        }

        if (indices.isComplete()) {
            break;
        }
        i++;
    }
    return indices;
}
