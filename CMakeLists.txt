# 设置最低 CMake 版本要求
cmake_minimum_required(VERSION 3.10)

# 设置项目名称
project(MyVulkanProject)

#本工程支持的C++版本
set(CMAKE_CXX_STANDARD 17)

#拷贝assets文件夹
file(GLOB ASSETS "./assets")
file(COPY ${ASSETS} DESTINATION ${CMAKE_BINARY_DIR})

#设置头文件查找
include_directories(
        SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/include
        # 引入 boost 头文件
        SYSTEM "E:\\B_software\\cpp_soft\\boost_1_86_0"
)
# 连接
link_directories(
        SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/lib
        # 链接 boost 编译库
        SYSTEM "E:\\B_software\\cpp_soft\\boost_1_86_0\\stage\\lib"
)

# 查找 Vulkan
find_package(Vulkan REQUIRED)

#把需要拷贝的资源路径放到 ASSETS 中
file(GLOB ASSETS "./assets" "./thirdParty")
#把 ASSETS 指定的目录集合内容拷贝到可执行文件目录
file(COPY ${ASSETS} DESTINATION ${CMAKE_BINARY_DIR})

# 添加可执行文件目标
add_executable(MyVulkanApp main.cpp)

# 添加包含目录
include_directories(${Vulkan_INCLUDE_DIRS})

#添加子目录 这个要放在添加第三方jar之后,子目录才能共享
add_subdirectory(my_vulkan_test)
add_subdirectory(my_application)
add_subdirectory(my_framework)

# 链接 Vulkan 库和可能的验证层库（如果启用验证层）
target_link_libraries(MyVulkanApp ${Vulkan_LIBRARIES} glfw3.lib my_app my_fw)
# 可选：设置编译定义以启用调试信息（如果需要）
#if (CMAKE_BUILD_TYPE MATCHES Debug)
#    target_compile_definitions(MyVulkanApp PRIVATE DEBUG)
#endif ()
