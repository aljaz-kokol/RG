#ifndef INC_2023_10_12_VAJA_2_PIRAMIDA_SHADERPROGRAM_H
#define INC_2023_10_12_VAJA_2_PIRAMIDA_SHADERPROGRAM_H

#include <GL/glew.h>
#include <vector>
#include <string>

class ShaderProgram {
private:
    GLint projectionLocation;
    GLint modelLocation;
    GLint meshColorLocation;
public:
    GLint getMeshColorLocation() const;

private:
    GLuint shaderID;
    std::vector<std::pair<std::string, GLenum>> shaders;
    void addShaderFromFile(const std::string& fileName, GLenum type) const;
public:
    ShaderProgram(const std::vector<std::pair<std::string, GLenum>>& shaders);
    ~ShaderProgram();
    void compile();
    void clear();
    void use() const;
    GLint getProjectionLocation() const;
    GLint getModelLocation() const;
    GLuint getShaderId() const;
};


#endif
