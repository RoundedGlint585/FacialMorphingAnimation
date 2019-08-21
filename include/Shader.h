//
// Created by roundedglint585 on 8/1/19.
//

#ifndef OPENGL_SHADER_H
#define OPENGL_SHADER_H
#include <cstdint>
#include <fstream>
#include <string>
#include <string_view>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include "Logger.h"
class Shader {
public:
    Shader(std::string_view vertexShaderPath, std::string_view fragmentShaderPath);
    void use() const;

    void setBool(std::string_view name, bool value) const;

    void setInt(std::string_view name, int value) const;

    void setFloat(std::string_view name, float value) const;

    void setFloatArray(std::string_view name, const std::vector<float> &data) const;

    void setVec2(std::string_view name, const glm::vec2 &value) const;

    void setVec2(std::string_view name, float x, float y) const;

    void setVec3(std::string_view name, const glm::vec3 &value) const;

    void setVec3(std::string_view name, float x, float y, float z) const;

    void setVec4(std::string_view name, const glm::vec4 &value) const;

    void setVec4(std::string_view name, float x, float y, float z, float w);

    void setMat2(std::string_view name, const glm::mat2 &mat) const;

    void setMat3(std::string_view name, const glm::mat3 &mat) const;

    void setMat4(std::string_view name, const glm::mat4 &mat) const;

private:
    uint32_t compileVertexShader(std::string_view vertexShaderPath);
    uint32_t compileFragmentShader(std::string_view fragmentShaderPath);
    void linkShader(uint32_t vertexShader, uint32_t fragmentShader);
    [[nodiscard]] std::string getFile(std::string_view path) const;
private:
    uint32_t shaderID_;
};


#endif //OPENGL_SHADER_H
