#include "Mesh.h"
#include "../renderer/Renderer.h"

Mesh::Mesh(const ShaderProgram& shader, const std::vector<GLfloat>& vertices, const std::vector<unsigned int>& indices)
: vbo(vertices), ibo(indices), shader(shader) {
    vao.bind();
    vbo.bind();
    bufferLayout.push<GL_FLOAT>(3);
    vao.addBuffer(vbo, bufferLayout);
}

void Mesh::applyTransformations(std::string_view uniformVariable, const std::vector<std::shared_ptr<Transformation>> &transformations) const {
    glm::mat4 model(1);
    for (const std::shared_ptr<Transformation>& transformation : transformations) {
        model *= transformation->transform();
    }
    shader.setUniform(uniformVariable, model);
}

void Mesh::setColor(const Color& color) const {
    shader.setUniform("meshColor", color.getRGBA());
}

void Mesh::setColor(const glm::vec4& color) const {
    shader.setUniform("meshColor", color);
}

const VertexArray &Mesh::getVao() const {
    return vao;
}

const VertexBuffer &Mesh::getVbo() const {
    return vbo;
}

const IndexBuffer &Mesh::getIbo() const {
    return ibo;
}

const ShaderProgram &Mesh::getShaderProgram() const {
    return shader;
}
