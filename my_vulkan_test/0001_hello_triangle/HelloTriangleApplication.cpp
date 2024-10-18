//
// Created by wangly on 2024/10/15.
//
#include "HelloTriangleApplication.h"

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
    MyValidationLayers::setupDebugMessenger(instance, &debugMessenger);
    //创建窗口表面
    MyVulkanSurface::createSurface(instance, window, &surface);
    //选择物理设备
    MyVulkanPhysicalDevices::pickPhysicalDevice(instance, &physicalDevice, surface);
    //创建逻辑设备
    MyVulkanLogicalDevices::createLogicalDevice(&physicalDevice, &device, &graphicsQueue, surface, presentQueue);
    //创建交换链
    myVulkanSwapChain.createSwapChain(&physicalDevice, surface, window, &swapChain, &device);
    //创建图像视图
    myVulkanImageView.createImageViews(myVulkanSwapChain, &device);
    //创建渲染过程
    myVulkanRenderPass.createRenderPass(myVulkanSwapChain, &device);
    //创建shader编译器
    MyVulkanShaderCompile myVulkanShaderCompile = MyVulkanShaderCompile();
    myVulkanShaderCompile.setShaderPath(
            "E:\\A_learning_data\\vulkan_learning001\\vulkan_learing\\cmake-build-debug\\assets\\0001_shader\\");
    myVulkanShaderCompile.setVertShaderName("vertex.vert");
    myVulkanShaderCompile.setFragShaderName("fragment.frag");
    myVulkanShaderCompile.compileShader();
    //创建图形管线
    myVulkanGraphicsPipeline.createGraphicsPipeline(myVulkanShaderCompile, &device, myVulkanSwapChain,
                                                    myVulkanFixedFuncs, myVulkanRenderPass.getRenderPass(),
                                                    myVulkanGraphicsPipeline.getGraphicsPipeline());
    //创建帧缓冲
    myVulkanDraw.createFrameBuffers(myVulkanImageView, myVulkanRenderPass, myVulkanSwapChain, &device);
    //创建命令池
    myVulkanDraw.createCommandPool(&physicalDevice, surface, &device);
    //创建命令缓冲
    myVulkanDraw.createCommandBuffer(&device);
    //创建同步对象
//    myVulkanDraw.createSyncObjects(device);
}

void HelloTriangleApplication::mainLoop() {
    //窗口循环
    while (!glfwWindowShouldClose(window)) {
        //glfw事件
        glfwPollEvents();
        //渲染
//        myVulkanDraw.drawFrame(device, swapChain, myVulkanRenderPass.getRenderPass(),
//                               myVulkanSwapChain.getSwapChainExtent(), myVulkanGraphicsPipeline.getGraphicsPipeline(),
//                               graphicsQueue, presentQueue);
    }
}

void HelloTriangleApplication::cleanup() {
    //清理同步对象
//    myVulkanDraw.cleanUpSyncObjects(device);
    //清理命令池
    myVulkanDraw.cleanUpCommandPool(device);
    //清理帧缓冲
    myVulkanRenderPass.cleanUp(myVulkanDraw.getSwapChainFramebuffers(), device);
    //清理图形管线
    myVulkanGraphicsPipeline.cleanUp(device);
    //清理渲染过程
    myVulkanRenderPass.cleanUp(device);
    //清理图像视图
    myVulkanImageView.cleanUp(device);
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
        throw std::runtime_error("failed to create instance! 创建 vulkan 实例失败!");
    }
}

void HelloTriangleApplication::run() {
    initWindow();
    initVulkan();
    mainLoop();
    cleanup();
}
