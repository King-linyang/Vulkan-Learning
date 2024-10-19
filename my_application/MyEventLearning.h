//
// Created by wangly on 2024/10/19.
// 事件监听，鼠标等

#pragma once

#include <GLFW/glfw3.h>
#include <iostream>
#include "./my_memory_pool/MyMemoryPoolManager.h"
#include "MyApplication.h"

#define myEventLearning MyEventLearning::getInstance()

class MyEventLearning {
public:
    MyEventLearning() = default;

    ~MyEventLearning() = default;

    //用于访问实例的静态函数
    static MyEventLearning *getInstance();

    // 鼠标按键事件
    static void mouseCallback(GLFWwindow *window, int button, int action, int mods);

    //窗口大小改变
    static void framebufferResizeCallback(GLFWwindow *window, int width, int height);

private:
    //定义一个全局唯一的静态实例
    static MyEventLearning *myEventLearningTmp;
};

