//
// Created by wangly on 2024/10/16.
//

#pragma once

class MyVulkanSurface {

public:
    MyVulkanSurface() = default;

    ~MyVulkanSurface() = default;
    //创建窗口表面
    static void createSurface(VkInstance instance, GLFWwindow *glfWwindow, VkSurfaceKHR *vkSurfaceKhr);
};

