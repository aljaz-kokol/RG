#ifndef INC_2023_10_12_VAJA_2_PIRAMIDA_SHADERPROGRAM_H
#define INC_2023_10_12_VAJA_2_PIRAMIDA_SHADERPROGRAM_H

#include <GL/glew.h>
#include <vector>
#include <unordered_map>
#include "../Shader.h"

class ShaderProgram {
private:
    GLuint id;
    const std::vector<Shader> shaders;
    [[nodiscard]] GLint getUniformLocation(std::string_view uniformName) const;
public:
    explicit ShaderProgram(const std::vector<Shader>& shaders);
    ~ShaderProgram();
    void compile();
    void bind() const;
    void unbind() const;
    [[nodiscard]] GLuint getId() const noexcept;

    template<typename T>
    void setUniform(std::string_view uniformName, const T& value) const;
};

#endif
