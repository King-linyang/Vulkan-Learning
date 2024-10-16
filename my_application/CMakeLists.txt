#递归将本文件夹下所有cpp放到 APP 中
file(GLOB_RECURSE APP ./  *.cpp)

#将APP 中所有cpp编译为 app 这个lib库
add_library(my_app ${APP})
