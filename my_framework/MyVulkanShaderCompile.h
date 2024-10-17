//
// Created by wangly on 2024/10/17.
// shader编译器

#pragma once

#include "core.h"

class MyVulkanShaderCompile {
public:
    MyVulkanShaderCompile() = default;

    ~MyVulkanShaderCompile() = default;

    //编译shader
    void compileShader();

    //编译单个shader
    static void compileSingleShader(const char *path, const char *shaderName);

    //读取加载shader
    std::vector<char> loadShader(const char *shaderName);

    //获取文件名
    static const char *extractBeforeDot(const char *input);

    //设置shader路径
    void setShaderPath(const char *path) { shaderPath = path; }

    //设置vertShader名字
    void setVertShaderName(const char *name) { vertShaderName = name; }

    //设置fragShader名字
    void setFragShaderName(const char *name) { fragShaderName = name; }

private:
    //shader的路径
    const char *shaderPath;
    //vertShader名字
    const char *vertShaderName;
    //fragShader名字
    const char *fragShaderName;
};

