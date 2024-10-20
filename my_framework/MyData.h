//
// Created by wangly on 2024/10/20.
// 数据

#pragma once

#include "MyVulkanFixedFuncs.h"
#include <vector>
#include <stdexcept>
#include <array>

//顶点颜色数据
struct Vertex_PointColor {
    //顶点位置
    glm::vec3 pos;
    //顶点颜色
    glm::vec3 color;
    //纹理坐标
    glm::vec2 texCoord;

    //绑定描述
    static VkVertexInputBindingDescription getBindingDescription() {
        VkVertexInputBindingDescription bindingDescription{};
        //顶点绑定描述在整个顶点中从内存中加载数据的速率。它指定数据条目之间的字节数，以及是移动到每个顶点之后还是每个实例之后的下一个数据条目。
        //binding 参数指定绑定数组中绑定的索引
        bindingDescription.binding = 0;
        //stride 参数指定从一个条目到下一个条目的字节数
        bindingDescription.stride = sizeof(Vertex_PointColor);
        //移动到每个顶点之后的下一个数据条目
        bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

        return bindingDescription;
    }

    //属性描述--如何处理顶点输入
    static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions() {
        //描述如何从源自绑定描述的顶点数据块中提取顶点属性
        std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions{};
        //binding 参数告诉 Vulkan 每个顶点数据的绑定来自哪个
        attributeDescriptions[0].binding = 0;
        //location 参数引用顶点着色器中输入的 location 指令
        attributeDescriptions[0].location = 0;
        //顶点着色器中具有 location 0 的输入是 position 它有两个 32 位浮点分量
        attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
        //format 参数描述属性的数据类型
        attributeDescriptions[0].offset = offsetof(Vertex_PointColor, pos);

        attributeDescriptions[1].binding = 0;
        attributeDescriptions[1].location = 1;
        //format 参数隐式定义属性数据的字节大小
        attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
        //offset 参数指定自要从中读取的每顶点数据开始以来的字节数,绑定一次加载一个 Vertex ，并且 position 属性 （ pos ） 与此结构的开头相距字节数 0
        attributeDescriptions[1].offset = offsetof(Vertex_PointColor, color);

        //纹理
        attributeDescriptions[2].binding = 0;
        attributeDescriptions[2].location = 2;
        attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
        attributeDescriptions[2].offset = offsetof(Vertex_PointColor, texCoord);
        return attributeDescriptions;
    }
};

//顶点索引
//从 0, 0 左上角到 1, 1 右下角的坐标简单地用纹理填充方块
const std::vector<Vertex_PointColor> vertices = {
        {{-0.5f, -0.5f, 0.0f},  {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
        {{0.5f,  -0.5f, 0.0f},  {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
        {{0.5f,  0.5f,  0.0f},  {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
        {{-0.5f, 0.5f,  0.0f},  {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},

        {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
        {{0.5f,  -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
        {{0.5f,  0.5f,  -0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
        {{-0.5f, 0.5f,  -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}}
};

//索引缓冲区
const std::vector<uint16_t> indices = {
        0, 1, 2, 2, 3, 0,
        4, 5, 6, 6, 7, 4
};

//uniform 变量,alignas(16) 表示对齐到 16 字节,不写这个会有奇怪问题
struct UniformBufferObject {
    alignas(16) glm::mat4 model;
    alignas(16) glm::mat4 view;
    alignas(16) glm::mat4 proj;
};
