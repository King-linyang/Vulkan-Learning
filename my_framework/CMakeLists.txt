#递归将本文件夹下所有cpp放到 FW 中
file(GLOB_RECURSE FW ./  *.cpp)

# 查找 Vulkan
find_package(Vulkan REQUIRED)
# 添加包含目录
include_directories(${Vulkan_INCLUDE_DIRS})

#将APP 中所有cpp编译为 fw 这个lib库
add_library(my_fw ${FW})
