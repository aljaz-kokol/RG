#include "Renderer.h"
#include <iostream>

void Renderer::clear() {
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::draw(const Mesh& mesh) {
    mesh.getShaderProgram().bind();
    mesh.getVao().bind();
    mesh.getIbo().bind();
    glDrawElements(GL_TRIANGLES, mesh.getIbo().getCount(), GL_UNSIGNED_INT, nullptr);
}