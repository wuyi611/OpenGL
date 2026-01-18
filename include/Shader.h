#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
    // 着色器程序 ID
    unsigned int ID;

    // 构造函数：读取并构建着色器
    Shader(const char* vertexPath, const char* fragmentPath);

    // 使用/激活程序
    void use();

    // uniform 工具函数
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;

private:
    // 检查着色器编译/链接错误的辅助函数
    void checkCompileErrors(unsigned int shader, std::string type);
};

#endif
