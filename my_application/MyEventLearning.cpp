//
// Created by wangly on 2024/10/19.
//

#include "MyEventLearning.h"

//初始化 MyEventLearning 的静态变量
MyEventLearning *MyEventLearning::myEventLearningTmp = nullptr;

void MyEventLearning::mouseCallback(GLFWwindow *window, int button, int action, int mods) {
    std::cout << "OnMouse-" << button << "--" << action << "--" << mods << std::endl;
}

MyEventLearning *MyEventLearning::getInstance() {
    //从内存池中申请内存实例
    if (myEventLearningTmp == nullptr) {
        myEventLearningTmp = new MyEventLearning();
    }
    return myEventLearningTmp;
}
