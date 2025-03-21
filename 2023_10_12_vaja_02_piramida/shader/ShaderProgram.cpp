#include "ShaderProgram.h"
#include <fstream>
#include <sstream>

ShaderProgram::ShaderProgram(const std::vector<std::pair<std::string, GLenum>> &shaders)
: projectionLocation(0), modelLocation(0), shaderID(0), meshColorLocation(0), shaders(shaders) {}

ShaderProgram::~ShaderProgram() {
    clear();
}

void ShaderProgram::clear() {
    if (shaderID != 0) {
        glDeleteProgram(shaderID);
    }
    modelLocation = 0;
    projectionLocation = 0;
}

void ShaderProgram::addShaderFromFile(const std::string &fileName, GLenum type) const {
    std::stringstream codeStream;
    std::string line;
    std::ifstream file(fileName);

    if (!file.is_open()) throw std::invalid_argument("File does not exists");
    while (std::getline(file, line)) {
        codeStream << line << std::endl;
    }

    std::string code = codeStream.str();

    GLuint shader = glCreateShader(type);

    const GLchar* SHADER_CODE[] = { code.c_str() };
    const GLint SHADER_LENGTH[] = { static_cast<GLint>(code.size()) };

    glShaderSource(shader, 1, SHADER_CODE, SHADER_LENGTH);

    GLint result = 0;
    GLchar errorLog[1024] = { 0 };

    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    if (!result) {
        glGetShaderInfoLog(shader, sizeof(errorLog), nullptr, errorLog);
        throw std::runtime_error(errorLog);
    }

    glAttachShader(shaderID, shader);
}

void ShaderProgram::compile() {
    shaderID = glCreateProgram();

    for (const std::pair<std::string, GLenum>& shader : shaders) {
        addShaderFromFile(shader.first, shader.second);
    }

    GLint result = 0;
    GLchar errorLog[1024] = { 0 };

    glLinkProgram(shaderID);
    glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
    if (!result) {
        glGetProgramInfoLog(shaderID, sizeof(errorLog), nullptr, errorLog);
        throw std::runtime_error(errorLog);
    }

    modelLocation = glGetUniformLocation(shaderID, "model");
    projectionLocation = glGetUniformLocation(shaderID, "projection");
    meshColorLocation = glGetUniformLocation(shaderID, "meshColor");

}

void ShaderProgram::use() const {
    glUseProgram(shaderID);
}

GLint ShaderProgram::getProjectionLocation() const {
    return projectionLocation;
}

GLint ShaderProgram::getModelLocation() const {
    return modelLocation;
}

GLuint ShaderProgram::getShaderId() const {
    return shaderID;
}

GLint ShaderProgram::getMeshColorLocation() const {
    return meshColorLocation;
}
