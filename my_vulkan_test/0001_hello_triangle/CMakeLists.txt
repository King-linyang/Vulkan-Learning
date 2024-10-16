#需求的最低cmake程序版本
cmake_minimum_required(VERSION 3.12)

#本工程的名字
project(0001_hello_triangle)

#本工程支持的C++版本
set(CMAKE_CXX_STANDARD 17)

# 查找 Vulkan
find_package(Vulkan REQUIRED)
# 添加包含目录
include_directories(${Vulkan_INCLUDE_DIRS})

file(GLOB_RECURSE ALL_CPP_FILES "./*.cpp")

#本工程所有cpp文件编译链接，生成exe
add_executable(0001_hello_triangle ${ALL_CPP_FILES})

# 链接 Vulkan 库和可能的验证层库（如果启用验证层）
target_link_libraries(0001_hello_triangle ${Vulkan_LIBRARIES} glfw3.lib my_app my_fw)
