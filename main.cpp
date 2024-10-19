
#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <vulkan/vulkan.h>

#include <iostream>
#include "my_application/MyMemoryPoolManager.h"

int main() {
    // 使用小内存池分配内存
    auto smallPtr = static_cast<int *>(ALLOCATE_SMALL_MEMORY(sizeof(int)));
    *smallPtr = 42;
    std::cout << "Small memory value: " << *smallPtr << std::endl;

    // 使用中内存池分配内存
    auto *mediumPtr = static_cast<double *>(ALLOCATE_MEDIUM_MEMORY(sizeof(double)));
    *mediumPtr = 3.14;
    std::cout << "Medium memory value: " << *mediumPtr << std::endl;

    // 使用大内存池分配内存
    auto largeArray = static_cast<char *>(ALLOCATE_LARGE_MEMORY(100 * sizeof(char)));
    std::cout << "Large memory allocated." << std::endl;

    // 释放内存
    DEALLOCATE_MEMORY(MemoryType::SMALL, smallPtr);
    DEALLOCATE_MEMORY(MemoryType::MEDIUM, mediumPtr);
    DEALLOCATE_MEMORY(MemoryType::LARGE, largeArray);

//    glfwInit();
//
//    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
//    GLFWwindow *window = glfwCreateWindow(800, 600, "Vulkan window", nullptr, nullptr);
//
//    uint32_t extensionCount = 0;
//    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
//
//    std::cout << extensionCount << " extensions supported\n";
//
//    glm::mat4 matrix;
//    glm::vec4 vec;
//    auto test = matrix * vec;
//
//    while (!glfwWindowShouldClose(window)) {
//        glfwPollEvents();
//    }
//
//    glfwDestroyWindow(window);
//
//    glfwTerminate();

    return 0;
}
