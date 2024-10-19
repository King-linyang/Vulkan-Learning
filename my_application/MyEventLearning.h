//
// Created by wangly on 2024/10/19.
// 事件监听，鼠标等

#pragma once

#include <GLFW/glfw3.h>
#include <iostream>
#include "MyMemoryPoolManager.h"

#define myEventLearning MyEventLearning::getInstance()

class MyEventLearning {
public:
    ~MyEventLearning() {
        //释放内存
        DEALLOCATE_MEDIUM_MEMORY(myEventLearningTmp);
    };

    //用于访问实例的静态函数
    static MyEventLearning *getInstance();

    // 鼠标按键事件
    static void mouseCallback(GLFWwindow *window, int button, int action, int mods);

private:
    //定义一个全局唯一的静态实例
    static MyEventLearning *myEventLearningTmp;
};

