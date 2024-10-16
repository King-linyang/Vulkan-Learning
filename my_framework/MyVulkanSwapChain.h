//
// Created by wangly on 2024/10/16.
//

#include <vector>
#include "core.h"
#include "MyVulkanPhysicalDevices.h"

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

    //设备是否合适
    static bool isDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR surface);

    //检查设备是否支持
    static bool checkDeviceExtensionSupport(VkPhysicalDevice device);

    //获取交换链支持详情
    static SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR surface);

    //选择表面格式
    static VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);

    //选择交换链模式
    static VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);

    //选择交换范围
    static VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities, GLFWwindow *window);

    //创建交换链
    static void
    createSwapChain(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, GLFWwindow *window,
                    VkSwapchainKHR *swapChain,
                    VkDevice device, std::vector<VkImage> swapChainImages, VkFormat &swapChainImageFormat,
                    VkExtent2D &swapChainExtent);
};

