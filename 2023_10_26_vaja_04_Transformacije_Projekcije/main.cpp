#include <gl/glew.h>
#include "world/window/OpenGLWindow.h"
#include "renderer/Renderer.h"
#include "object/Cuboid/Cuboid.h"
#include "shader/program/ShaderProgram.h"
#include "object/transformation/translation/Translation.h"
#include "object/transformation/scale/Scale.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>

int main() {
    const float SCALE_FACTOR = 0.3;
    OpenGLWindow window("02 - piramida", 800, 800);

    ShaderProgram shaderProgram({
        { "vertex.vert", GL_VERTEX_SHADER },
        { "fragment.frag", GL_FRAGMENT_SHADER }
    });

    const std::vector<std::pair<Color, std::vector<std::shared_ptr<Transformation>>>> TRANSFORMATIONS = {
        {
            Color(Color::BLUE),
            {
                std::make_shared<Translation>(glm::vec3(0.0, -2 * SCALE_FACTOR, -2.5f)),
                std::make_shared<Scale>(SCALE_FACTOR),
            },
        },
        {
            Color(Color::YELLOW),
            {
                std::make_shared<Translation>(glm::vec3(-2 * SCALE_FACTOR, -2 * SCALE_FACTOR, -2.5f)),
                std::make_shared<Scale>(SCALE_FACTOR),
            },
        },
        {
            Color(Color::RED),
            {
                std::make_shared<Translation>(glm::vec3(2 * SCALE_FACTOR, -2 * SCALE_FACTOR, -2.5f)),
                std::make_shared<Scale>(SCALE_FACTOR),
            },
        },
        {
            Color(Color::GREEN),
            {
                    std::make_shared<Translation>(glm::vec3(SCALE_FACTOR, 0, -2.5f)),
                    std::make_shared<Scale>(SCALE_FACTOR),
            },
        },
        {
            Color(Color::CYAN),
            {
                    std::make_shared<Translation>(glm::vec3(-SCALE_FACTOR, 0, -2.5f)),
                    std::make_shared<Scale>(SCALE_FACTOR),
            },
        },
        {
            Color(Color::MAGENTA),
            {
                    std::make_shared<Translation>(glm::vec3(0, 2 * SCALE_FACTOR, -2.5f)),
                    std::make_shared<Scale>(SCALE_FACTOR),
            },
        },
    };

    Cuboid cube(shaderProgram, 1, 1, 1);

    shaderProgram.compile();

    glm::mat4 projection = glm::perspective(glm::radians(70.0f), (GLfloat)window.getBufferWidth() / (GLfloat)window.getBufferHeight(), 0.1f, 100.0f);

    while (!window.shouldClose()) {
        glfwPollEvents();
        Renderer::clear();

        shaderProgram.bind();
        shaderProgram.setUniform("projection", projection);

        for (const auto & transformation : TRANSFORMATIONS) {
            cube.applyTransformations("model", transformation.second);
            cube.setColor(transformation.first);
            Renderer::draw(cube);
        }

        shaderProgram.unbind();
        window.swapBuffers();
    }

    return 0;
}
