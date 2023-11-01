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

    const std::vector<std::pair<Color, std::vector<std::shared_ptr<Transformation>>>> TRANSFORMATIONS = {
        {
            Color(Color::RED +Color::YELLOW * 0.5f),
            {
                std::make_shared<Translation>(glm::vec3(0, -3.2 * SCALE_FACTOR, -2.5)),
                std::make_shared<Scale>(glm::vec3(1.1, 0.03, 0.7)),
            },
        },
    };

    Cuboid cube(shaderProgram, 1, 1, 1);

    CuboidShape pyramide(
        cube,
        {
            { "b-left", Color(Color::BLUE), { -1, -1, -1.5 } }, { "b-center", Color(Color::YELLOW), { 0, -1, -1.5 } }, { "b-right", Color(Color::RED), { 1, -1, -1.5 } },
            { "m-left", Color(Color::GREEN), { -0.5, 0, -1.5 } }, { "m-right", Color(Color::CYAN), { 0.5, 0, -1.5 } },
            { "t-center", Color(Color::MAGENTA), { 0, 1, -1.5 } },
        },
        0.3
    );

    shaderProgram.compile();

    glm::mat4 projection = glm::perspective(glm::radians(70.0f), (GLfloat) window.getBufferWidth() / (GLfloat) window.getBufferHeight(), 0.1f, 100.0f);

    while (!window.shouldClose()) {
        glfwPollEvents();
        Renderer::clear();

        shaderProgram.bind();
        shaderProgram.setUniform("projection", projection);

        pyramide.draw();

        cube.applyTransformations("model", {
            std::make_shared<Translation>(glm::vec3(0, -3.2 * SCALE_FACTOR, -2.5)),
            std::make_shared<Scale>(glm::vec3(1.1, 0.03, 0.7)),
        });
        cube.setColor(Color(Color::RED +Color::YELLOW * 0.5f));
        //Renderer::draw(cube);

        shaderProgram.unbind();
        window.swapBuffers();
    }

    return 0;
}
