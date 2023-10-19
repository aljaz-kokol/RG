#include <iostream>
#include <gl/glew.h>
#include "OpenGLWindow.h"
#include "object/Cuboid/Cuboid.h"
#include "shader/Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int main() {
    OpenGLWindow window("TEST", 800, 600);

    Shader shader({
        {"vertex.vert", GL_VERTEX_SHADER},
        {"fragment.frag", GL_FRAGMENT_SHADER}
    });

    Cuboid cube(shader, 1, 1, 1);
    Cuboid floor(shader, 3, -0.1, 2);

    cube.create();
    floor.create();
    shader.compile();

    float angle = 0.0;
    glm::mat4 projection = glm::perspective(glm::radians(65.0f), (GLfloat)window.getBufferWidth() / (GLfloat)window.getBufferHeight(), 0.1f, 100.0f);

    while (!window.shouldClose()) {
        glfwPollEvents();
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shader.use();
        glUniformMatrix4fv(shader.getProjectionLocation(), 1, GL_FALSE, glm::value_ptr(projection));

        cube.translate(glm::vec3(-0.3, -0.6f, -2.5f));
        cube.scale(glm::vec3(0.3f, 0.3f, 0.3f));
        cube.applyTransformations();
        cube.setColor({1.0, 1.0, 0.0, 1.0});
        cube.draw();

        cube.translate(glm::vec3(0.3, -0.6f, -2.5f));
        cube.scale(glm::vec3(0.3f, 0.3f, 0.3f));
        cube.applyTransformations();
        cube.setColor({1.0, 0.0, 0.0, 1.0});
        cube.draw();

        cube.translate(glm::vec3(0.0f, 0.0f, -2.5f));
        cube.scale(glm::vec3(0.3f, 0.3f, 0.3f));
        cube.applyTransformations();
        cube.setColor({1.0, 0.0, 1.0, 1.0});
        cube.draw();

        floor.translate( glm::vec3(0, -0.9f, -2.5f));
        floor.scale(glm::vec3(0.3, 0.3, 0.3));
        floor.applyTransformations();
        floor.setColor({0.0, 1.0, 0.0, 1.0});
        floor.draw();

        glUseProgram(0);
        angle += 0.5;
        if (angle > 360) angle -= 360;

        window.swapBuffers();
    }
    return 0;
}
