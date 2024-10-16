//
// Created by wangly on 2024/10/15.
//
#include "HelloTriangleApplication.h"
#include "../../my_framework/MyValidationLayers.h"
#include "../../my_framework/MyVulkanPhysicalDevices.h"
#include "../../my_framework/MyVulkanLogicalDevices.h"
#include "../../my_framework/MyVulkanSurface.h"

void HelloTriangleApplication::initWindow() {
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
}

void HelloTriangleApplication::initVulkan() {
    //创建实例
    createInstance();
    //验证层
    MyValidationLayers::setupDebugMessenger(instance, debugMessenger);
    //创建窗口表面
    MyVulkanSurface::createSurface(instance, window, &surface);
    //选择物理设备
    MyVulkanPhysicalDevices::pickPhysicalDevice(instance, &physicalDevice, surface);
    //创建逻辑设备
    MyVulkanLogicalDevices::createLogicalDevice(physicalDevice, &device, &graphicsQueue, surface, presentQueue);
    //创建交换链
    myVulkanSwapChain.createSwapChain(physicalDevice, surface, window, &swapChain, device);
}

void HelloTriangleApplication::mainLoop() {
    //窗口循环
    while (!glfwWindowShouldClose(window)) {
        //glfw事件
        glfwPollEvents();
    }
}

void HelloTriangleApplication::cleanup() {
    //清理交换链
    vkDestroySwapchainKHR(device, swapChain, nullptr);
    //销毁逻辑设备
    vkDestroyDevice(device, nullptr);
    if (enableValidationLayers) {
        MyValidationLayers::DestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
    }
    //销毁窗口表面
    vkDestroySurfaceKHR(instance, surface, nullptr);
    //清理 vulkan 实例
    vkDestroyInstance(instance, nullptr);
    //清理窗口
    glfwDestroyWindow(window);
    //清理 glfw
    glfwTerminate();
}

void HelloTriangleApplication::createInstance() {
    //检查是否所有请求的图层都可用
    if (enableValidationLayers && !MyValidationLayers::checkValidationLayerSupport()) {
        throw std::runtime_error("validation layers requested, but not available!");
    }
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Hello Triangle";
    //vulkan api 版本号
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 3, 290);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 3, 290);
    appInfo.apiVersion = VK_API_VERSION_1_3;
    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;
    auto extensions = MyValidationLayers::getRequiredExtensions();
    createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    createInfo.ppEnabledExtensionNames = extensions.data();

    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
    if (enableValidationLayers) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();
        MyValidationLayers::populateDebugMessengerCreateInfo(debugCreateInfo);
        createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT *) &debugCreateInfo;
    } else {
        createInfo.enabledLayerCount = 0;
        createInfo.pNext = nullptr;
    }
    if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
        throw std::runtime_error("failed to create instance!");
    }
}

void HelloTriangleApplication::run() {
    initWindow();
    initVulkan();
    mainLoop();
    cleanup();
}
