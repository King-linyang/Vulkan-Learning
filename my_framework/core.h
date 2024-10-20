//
// Created by wangly on 2024/10/15.
// 框架引入的包

#pragma once

#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>

#define GLM_FORCE_DEPTH_ZERO_TO_ONE
//GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//包含 GLM 类型的哈希函数
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>

//glm需要开启这个宏
#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/string_cast.hpp>

//vulkan
#include <vulkan/vulkan.h>

//内存管理
#include "../my_application/my_memory_pool/MyMemoryPoolManager.h"
