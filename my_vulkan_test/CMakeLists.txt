#需求的最低cmake程序版本
cmake_minimum_required(VERSION 3.12)

#本工程的名字
project(my_vulkan_test)

#本工程支持的C++版本
set(CMAKE_CXX_STANDARD 17)

# 添加子目录
add_subdirectory(0001_hello_triangle)
add_subdirectory(0002_hello_triangle)