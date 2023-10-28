#include "ShaderProgram.h"
#include <sstream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

ShaderProgram::ShaderProgram(const std::vector<Shader>& shaders)
: id(0), shaders(shaders) {}

ShaderProgram::~ShaderProgram() {
    if (id != 0) {
        glDeleteProgram(id);
    }
}

void ShaderProgram::compile() {
    id = glCreateProgram();

    for (const Shader& shader : shaders) {
        shader.compile();
        glAttachShader(id, shader.getId());
    }

    GLint result = 0;
    GLchar errorLog[1024] = { 0 };

    glLinkProgram(id);
    glGetProgramiv(id, GL_LINK_STATUS, &result);
    if (!result) {
        glGetProgramInfoLog(id, sizeof(errorLog), nullptr, errorLog);
        throw std::runtime_error(errorLog);
    }
}

void ShaderProgram::bind() const {
    glUseProgram(id);
}

void ShaderProgram::unbind() const {
    glUseProgram(0);
}

GLuint ShaderProgram::getId() const noexcept {
    return id;
}

GLint ShaderProgram::getUniformLocation(std::string_view uniformName) const {
    GLint  location = glGetUniformLocation(id, uniformName.data());
    if (location == -1) {
        std::stringstream errorStr;
        errorStr << "\"" << uniformName << "\" is not a valid uniform variable";
        throw std::invalid_argument(errorStr.str());
    }
    return location;
}

template<typename T>
void ShaderProgram::setUniform(std::string_view uniformName, const T& value) const{
    throw std::invalid_argument("Unsupported uniform data type");
}

template<>
void ShaderProgram::setUniform<glm::mat4>(std::string_view uniformName, const glm::mat4& value) const {
    GLint location = getUniformLocation(uniformName);
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

template<>
void ShaderProgram::setUniform<glm::vec4>(std::string_view uniformName, const glm::vec4& value) const {
    GLint location = getUniformLocation(uniformName);
    glUniform4fv(location, 1,  glm::value_ptr(value));
}