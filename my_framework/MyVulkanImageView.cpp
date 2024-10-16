//
// Created by wangly on 2024/10/16.
// 图像视图

#include <stdexcept>
#include "MyVulkanImageView.h"

void
MyVulkanImageView::createImageViews(MyVulkanSwapChain myVulkanSwapChain, VkDevice device) {
    //调整列表的大小以适合我们将创建的所有图像视图
    swapChainImageViews.resize(myVulkanSwapChain.getSwapChainImages().size());
    //设置迭代所有交换链映像的循环
    for (size_t i = 0; i < myVulkanSwapChain.getSwapChainImages().size(); i++) {
        //subresourceRange 字段描述图像的用途以及应访问图像的哪个部分。我们的图像将用作颜色目标，无需任何 mipmap 级别或多个图层。
        VkImageViewCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        createInfo.image = myVulkanSwapChain.getSwapChainImages()[i];

        //viewType 参数允许您将图像视为 1D 纹理、2D 纹理、3D 纹理和立方体贴图。
        createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        createInfo.format = myVulkanSwapChain.getSwapChainImageFormat();

        //components 字段允许您重排颜色通道。例如，可以将所有通道映射到单色纹理的红色通道。您还可以将 0 和 1 的常量值映射到通道
        createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;

        //subresourceRange 字段描述图像的用途以及应访问图像的哪个部分。我们的图像将用作颜色目标，无需任何 mipmap 级别或多个图层。
        createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        createInfo.subresourceRange.baseMipLevel = 0;
        createInfo.subresourceRange.levelCount = 1;
        createInfo.subresourceRange.baseArrayLayer = 0;
        createInfo.subresourceRange.layerCount = 1;

        //创建 image 视图
        if (vkCreateImageView(device, &createInfo, nullptr, &swapChainImageViews[i]) != VK_SUCCESS) {
            throw std::runtime_error("failed to create image views!");
        }
    }
}

void MyVulkanImageView::cleanUp(VkDevice device) {
    //清理图像视图
    for (auto imageView: swapChainImageViews) {
        vkDestroyImageView(device, imageView, nullptr);
    }
}
