
#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <vulkan/vulkan.h>

#include <iostream>
#include "my_application/my_memory_pool/MyMemoryPoolManager.h"

// 用于测试的简单类
class TestObject {
public:
    TestObject() : data(0) { std::cout << "TestObject constructed\n"; }

    explicit TestObject(int d) : data(d) { std::cout << "TestObject constructed with " << d << "\n"; }

    ~TestObject() { std::cout << "TestObject destructed\n"; }

    int getData() const { return data; }

private:
    int data;
};

int main() {

    // 测试基本的分配和释放
    TestObject *obj1 = POOL_ALLOCATE(TestObject);
    assert(obj1 != nullptr);
    new(obj1) TestObject();  // 显式调用构造函数
    POOL_DEALLOCATE(obj1);

    // 测试使用POOL_NEW和poolDelete
    TestObject *obj2 = POOL_NEW(TestObject, 42);
    assert(obj2->getData() == 42);
    POOL_DELETE(obj2);

    // 测试多次分配和释放
    const int NUM_OBJECTS = 10;
    std::vector<TestObject *> objects;
    for (int i = 0; i < NUM_OBJECTS; ++i) {
        objects.push_back(POOL_NEW(TestObject, i));
    }
    for (auto &obj: objects) {
        POOL_DELETE(obj);
    }

    // 测试获取统计信息
    size_t allocatedCount = MyMemoryPoolManager::getInstance().getAllocatedCount<TestObject>();
    size_t totalCapacity = MyMemoryPoolManager::getInstance().getTotalCapacity<TestObject>();
    size_t freeCount = MyMemoryPoolManager::getInstance().getFreeCount<TestObject>();

    std::cout << "Allocated count: " << allocatedCount << std::endl;
    std::cout << "Total capacity: " << totalCapacity << std::endl;
    std::cout << "Free count: " << freeCount << std::endl;

    assert(allocatedCount == 0);
    assert(totalCapacity >= NUM_OBJECTS);
    assert(freeCount == totalCapacity);

    std::cout << "All tests passed!" << std::endl;

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
