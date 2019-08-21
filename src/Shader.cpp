//
// Created by roundedglint585 on 8/1/19.
//

#include "../include/Shader.h"

Shader::Shader(std::string_view vertexShaderPath, std::string_view fragmentShaderPath): shaderID_(-1) {
    uint32_t vertexShader = compileVertexShader(vertexShaderPath);
    uint32_t fragmentShader = compileFragmentShader(fragmentShaderPath);
    linkShader(vertexShader, fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

uint32_t Shader::compileVertexShader(std::string_view vertexShaderPath) {
    std::string vertexShaderData = getFile(vertexShaderPath);
    const char* vertexShaderSource = vertexShaderData.c_str();
    uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success){
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        ERROR(std::string("ERROR::SHADER::VERTEX::COMPILATION_FAILED: ") + infoLog);
    }
    return vertexShader;
}

uint32_t Shader::compileFragmentShader(std::string_view fragmentShaderPath) {
    std::string fragmentShaderData = getFile(fragmentShaderPath);
    const char* fragmentShaderSource = fragmentShaderData.c_str();
    uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    int success;
    char infoLog[512];
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success){
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
    }
    return fragmentShader;
}

void Shader::linkShader(uint32_t vertexShader, uint32_t fragmentShader) {
    shaderID_ = glCreateProgram();
    glAttachShader(shaderID_, vertexShader);
    glAttachShader(shaderID_, fragmentShader);
    glLinkProgram(shaderID_);
    int success = 0;
    char infoLog[512];
    glGetShaderiv(shaderID_, GL_COMPILE_STATUS, &success);
    if (!success){
        glGetShaderInfoLog(shaderID_, 512, nullptr, infoLog);
        ERROR(std::string("SHADER::VERTEX::COMPILATION_FAILED: ") + infoLog);
    }
}

std::string Shader::getFile(std::string_view path) const{
    std::ifstream file(&path.front(), std::ios::binary|std::ios::ate);
    if (file){
        uint64_t fileSize = file.tellg();
        file.seekg(std::ios::beg);
        std::string result(fileSize,0);
        file.read(result.data(),fileSize);
        return result;
    }
    return {};
}

void Shader::use() const {
    glUseProgram(shaderID_);
}

void Shader::setBool(std::string_view name, bool value) const {
    glUniform1i(glGetUniformLocation(shaderID_, name.data()), (int) value);
}

void Shader::setInt(std::string_view name, int value) const {
    glUniform1i(glGetUniformLocation(shaderID_, name.data()), value);
}

void Shader::setFloat(std::string_view name, float value) const {
    glUniform1f(glGetUniformLocation(shaderID_, name.data()), value);
}

void Shader::setVec2(std::string_view name, const glm::vec2 &value) const {
    glUniform2fv(glGetUniformLocation(shaderID_, name.data()), 1, &value[0]);
}

void Shader::setVec2(std::string_view name, float x, float y) const {
    glUniform2f(glGetUniformLocation(shaderID_, name.data()), x, y);
}

void Shader::setVec3(std::string_view name, const glm::vec3 &value) const {
    glUniform3fv(glGetUniformLocation(shaderID_, name.data()), 1, &value[0]);
}

void Shader::setVec3(std::string_view name, float x, float y, float z) const {
    glUniform3f(glGetUniformLocation(shaderID_, name.data()), x, y, z);
}

void Shader::setVec4(std::string_view name, const glm::vec4 &value) const {
    glUniform4fv(glGetUniformLocation(shaderID_, name.data()), 1, &value[0]);
}

void Shader::setVec4(std::string_view name, float x, float y, float z, float w) {
    glUniform4f(glGetUniformLocation(shaderID_, name.data()), x, y, z, w);
}

void Shader::setMat2(std::string_view name, const glm::mat2 &mat) const {
    glUniformMatrix2fv(glGetUniformLocation(shaderID_, name.data()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat3(std::string_view name, const glm::mat3 &mat) const {
    glUniformMatrix3fv(glGetUniformLocation(shaderID_, name.data()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat4(std::string_view name, const glm::mat4 &mat) const {
    glUniformMatrix4fv(glGetUniformLocation(shaderID_, name.data()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setFloatArray(std::string_view name, const std::vector<float> &data) const {
    glUniform1fv(glGetUniformLocation(shaderID_, name.data()), data.size(), data.data());
}
