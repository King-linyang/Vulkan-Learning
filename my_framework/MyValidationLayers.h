
//
// Created by wangly on 2024/10/15.
// vulkan 验证层

#pragma once

#include "core.h"
#include <vector>

//vulkan 验证层
const std::vector<const char *> validationLayers = {
        "VK_LAYER_KHRONOS_validation"
};
#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif
//vulkan 验证层

class MyValidationLayers {

public:
    MyValidationLayers() = default;

    ~MyValidationLayers() = default;

    // 检查是否所有请求的图层都可用
    static bool checkValidationLayerSupport();

    // 根据是否启用验证层返回所需的扩展列表
    static std::vector<const char *> getRequiredExtensions();

    // 消息回调
    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
            VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT messageType,
            const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
            void *pUserData);

    // 设置调试信息
    static void setupDebugMessenger(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger);

    static void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo);

    static void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger,
                                              const VkAllocationCallbacks *pAllocator);

private:

    static VkResult
    CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo,
                                 const VkAllocationCallbacks *pAllocator,
                                 VkDebugUtilsMessengerEXT *pDebugMessenger);
};
