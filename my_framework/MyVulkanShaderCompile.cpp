//
// Created by wangly on 2024/10/17.
// shader编译器


#include "MyVulkanShaderCompile.h"

void MyVulkanShaderCompile::compileSingleShader(const char *path, const char *shaderName) {
    std::string shaderPath = std::string(path) + std::string(shaderName);
    const char *shaderNameT = extractBeforeDot(shaderName);
    std::string fullOutputPath = std::string(path) + shaderNameT + ".spv";
    // 构建命令字符串
    std::string command = R"(E:\B_software\vulkan\Bin\glslc.exe )" + shaderPath + " -o " + fullOutputPath;
    int result = std::system(command.c_str());
    if (result == 0) {
        std::cout << "成功生成 " << shaderNameT << ".spv" << std::endl;
    } else {
        std::cerr << "生成  " << shaderNameT << ".spv 失败" << std::endl;
    }
}

void MyVulkanShaderCompile::compileShader() {
    compileSingleShader(shaderPath, vertShaderName);
    compileSingleShader(shaderPath, fragShaderName);
}

// 读取UTF - 8文件并转换为 std::vector<char>&
std::vector<char> MyVulkanShaderCompile::loadShader(const char *shaderName) {
    std::string shaderPathT = std::string(shaderPath) + std::string(extractBeforeDot(shaderName)) + ".spv";
    std::ifstream file(shaderPathT, std::ios::in | std::ios::binary);
    if (!file) {
        std::cerr << "无法打开文件: " << shaderPathT << std::endl;
        static std::vector<char> emptyResult;
        return emptyResult;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();

    return std::vector<char>(content.begin(), content.end());

}

//获取文件名
const char *MyVulkanShaderCompile::extractBeforeDot(const char *input) {
    const char *dotPos = std::strchr(input, '.');
    if (dotPos != nullptr) {
        int length = dotPos - input;
        char *result = new char[length + 1];
        std::strncpy(result, input, length);
        result[length] = '\0';
        return result;
    }
    return input;
}
