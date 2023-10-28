#include "Mesh.h"
#include "../renderer/Renderer.h"

Mesh::Mesh(const ShaderProgram& shader, const std::vector<GLfloat>& vertices, const std::vector<unsigned int>& indices)
: vbo(vertices), ibo(indices), shader(shader), model(1) {
    BufferLayout layout;
    vao.bind();
    vbo.bind();
    layout.push<GL_FLOAT>(3);
    vao.addBuffer(vbo, layout);
}

void Mesh::draw() const {
    Renderer::draw(vao, ibo, shader);
}

void Mesh::rotateXYZ(float angle, const glm::vec3 &coordAmount) {
    model = glm::rotate(model, glm::radians(angle), coordAmount);
}

void Mesh::scale(const glm::vec3 &factors) {
    model = glm::scale(model, factors);
}

void Mesh::scale(float factor) {
    scale(glm::vec3(factor, factor, factor));
}

void Mesh::translate(const glm::vec3 &values) {
    model = glm::translate(model, values);
}

void Mesh::applyTransformations() {
    shader.setUniform("model", model);
    model = glm::mat4(1);
}

void Mesh::setColor(const glm::vec4& color) {
    shader.setUniform("meshColor", color);
}