#include <gl/glew.h>
#include "world/window/OpenGLWindow.h"
#include "renderer/Renderer.h"
#include "shader/program/ShaderProgram.h"
#include "object/transformation/translation/Translation.h"
#include "object/transformation/scale/Scale.h"
#include "object/cuboid/cuboid-shape/CuboidShape.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>

int main() {
    float SCALE_FACTOR = 0.3;
    OpenGLWindow window("02 - piramida", 800, 800);

    ShaderProgram shaderProgram({
        { "vertex.vert",   GL_VERTEX_SHADER },
        { "fragment.frag", GL_FRAGMENT_SHADER }
    });

    Cuboid cube(shaderProgram, 1, 1, 1);

    CuboidShape pyramide(
        cube,
        {
            { { -1, -1, -1.5 }, Color(Color::BLUE) }, { { 0, -1, -1.5 }, Color(Color::YELLOW) }, { { 1, -1, -1.5 }, Color(Color::RED) },
            { { -0.5, 0, -1.5 }, Color(Color::GREEN) }, { { 0.5, 0, -1.5 }, Color(Color::CYAN) },
            { { 0, 1, -1.5 }, Color(Color::MAGENTA) },
        },
        0.3
    );

    shaderProgram.compile();

    glm::mat4 projection = glm::perspective(glm::radians(70.0f), (GLfloat) window.getBufferWidth() / (GLfloat) window.getBufferHeight(), 0.1f, 100.0f);

    window.addKeyAction(GLFW_KEY_W, [&]() { pyramide.move(Direction::UP, 0.3); });
    window.addKeyAction(GLFW_KEY_S, [&]() { pyramide.move(Direction::DOWN, 0.3); });
    window.addKeyAction(GLFW_KEY_A, [&]() { pyramide.move(Direction::LEFT, 0.3); });
    window.addKeyAction(GLFW_KEY_D, [&]() { pyramide.move(Direction::RIGHT, 0.3); });

    window.addKeyAction(GLFW_KEY_DOWN, [&]() { pyramide.scale(Direction::UP, 0.04); });
    window.addKeyAction(GLFW_KEY_UP, [&]() { pyramide.scale(Direction::DOWN, 0.05); });
    window.addKeyAction(GLFW_KEY_RIGHT, [&]() { pyramide.rotate(Direction::RIGHT, 5); });

    while (!window.shouldClose()) {
        glfwPollEvents();
        Renderer::clear();

        shaderProgram.bind();
        shaderProgram.setUniform("projection", projection);

        pyramide.draw();

        shaderProgram.unbind();
        window.swapBuffers();
    }

    return 0;
}
