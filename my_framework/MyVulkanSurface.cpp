//
// Created by wangly on 2024/10/16.
//

#include <stdexcept>
#include "core.h"
#include "MyVulkanSurface.h"


void MyVulkanSurface::createSurface(VkInstance instance, GLFWwindow *glfWwindow, VkSurfaceKHR *vkSurfaceKhr) {
    if (glfwCreateWindowSurface(instance, glfWwindow, nullptr, vkSurfaceKhr) != VK_SUCCESS) {
        throw std::runtime_error("failed to create window surface!");
    }
}
