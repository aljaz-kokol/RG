#include "Mesh.h"

Mesh::Mesh(const Shader& shader, const std::vector<GLfloat>& vertices, const std::vector<unsigned int>& indices)
: vao(0), vbo(0), ibo(0), vertices(vertices), indices(indices), shader(shader), model(1) {}

Mesh::~Mesh() {
    clear();
    vertices.clear();
}

void Mesh::create() {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ibo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), indices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
            glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Mesh::draw() const {
    glBindVertexArray(vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
            glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    glBindVertexArray(0);
}

void Mesh::clear() {
    if (vbo != 0) {
        glDeleteBuffers(1, &vbo);
    }
    if (ibo != 0) {
        glDeleteBuffers(1, &ibo);
    }
    if (vao != 0) {
        glDeleteVertexArrays(1, &vao);
    }
    indices.clear();
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
    glUniformMatrix4fv(shader.getModelLocation(), 1, GL_FALSE, glm::value_ptr(model));
    model = glm::mat4(1);
}

void Mesh::setColor(const glm::vec4& color) {
    glUniform4fv(shader.getMeshColorLocation(), 1, glm::value_ptr(color));
}