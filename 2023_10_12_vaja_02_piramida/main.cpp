#include <iostream>
#include <gl/glew.h>
#include "world/window/OpenGLWindow.h"
#include "object/Cuboid/Cuboid.h"
#include "shader/ShaderProgram.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int main() {
    OpenGLWindow window("02 - piramida", 800, 800);

    ShaderProgram shaderProgram({
        {"vertex.vert", GL_VERTEX_SHADER},
        {"fragment.frag", GL_FRAGMENT_SHADER}
    });

    Cuboid cube(shaderProgram, 1, 1, 1);
    Cuboid floor(shaderProgram, 3, 0.1, 2);

    cube.create();
    floor.create();
    shaderProgram.compile();

    glm::mat4 projection = glm::perspective(glm::radians(70.0f), (GLfloat)window.getBufferWidth() / (GLfloat)window.getBufferHeight(), 0.1f, 100.0f);

    while (!window.shouldClose()) {
        glfwPollEvents();
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaderProgram.use();
        glUniformMatrix4fv(shaderProgram.getProjectionLocation(), 1, GL_FALSE, glm::value_ptr(projection));

        glm::vec3 center = (glm::vec3(-0.3, -0.6f, -2.5f) + glm::vec3(0.3, -0.6f, -2.5f) + glm::vec3(0.0f, 0.0f, -2.5f)) / 3.0f;

        cube.translate(center);
        cube.rotateXYZ(45, {0, 1, 0});
        cube.translate(glm::vec3(-0.3, -0.6f, -2.5f) - center);
        cube.scale(0.3f);
        cube.applyTransformations();
        cube.setColor({1.0, 1.0, 0.0, 1.0});
        cube.draw();

        cube.translate(center);
        cube.rotateXYZ(45, {0, 1, 0});
        cube.translate(glm::vec3(0.3, -0.6f, -2.5f) - center);
        cube.scale(0.3f);
        cube.applyTransformations();
        cube.setColor({1.0, 0.0, 0.0, 1.0});
        cube.draw();

        cube.translate(center);
        cube.rotateXYZ(45, {0, 1, 0});
        cube.translate(glm::vec3(0.0f, 0.0f, -2.5f) - center);
        cube.scale(0.3f);
        cube.applyTransformations();
        cube.setColor({1.0, 0.0, 1.0, 1.0});
        cube.draw();

//        floor.translate( glm::vec3(0, -0.9f, -2.5f));
//        floor.scale(0.3f);
//        floor.applyTransformations();
//        floor.setColor({0.0, 1.0, 0.0, 1.0});
//        floor.draw();

        glUseProgram(0);
        window.swapBuffers();
    }
    return 0;
}
