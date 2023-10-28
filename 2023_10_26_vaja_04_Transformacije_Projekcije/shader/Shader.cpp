#include <iostream>
#include "Shader.h"

Shader::Shader(std::string_view fileName, GLenum type): id(0), type(type) {
    id = glCreateShader(type);
    std::ifstream file(fileName);
    if (!file.is_open()) {
        throw std::invalid_argument("Passed file for shader does not exist");
    }
    std::string sourceStr = (static_cast<std::stringstream const &>(std::stringstream() << file.rdbuf()).str());
    const char* source = sourceStr.c_str();
    glShaderSource(id, 1, &source, nullptr);
    file.close();
}

void Shader::compile() const {
    GLchar log[1024] = { 0 };
    GLint result = 0;
    glCompileShader(id);
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (!result) {
        glGetShaderInfoLog(id, sizeof(log), nullptr, log);
        throw std::runtime_error(log);
    }
}

GLuint Shader::getId() const {
    return id;
}
