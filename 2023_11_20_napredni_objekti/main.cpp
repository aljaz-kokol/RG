#define STB_IMAGE_IMPLEMENTATION
#include <gl/glew.h>
#include "world/window/OpenGLWindow.h"
#include "renderer/Renderer.h"
#include "shader/program/ShaderProgram.h"
#include "object/transformation/translation/Translation.h"
#include "object/transformation/scale/Scale.h"
#include "object/cuboid/cuboid-shape/CuboidShape.h"
#include <glm/glm.hpp>


int main() {
    OpenGLWindow window("02 - piramida", 1920, 1080);

    ShaderProgram shaderProgram({
        { "vertex.vert",   GL_VERTEX_SHADER },
        { "fragment.frag", GL_FRAGMENT_SHADER }
    });

    const std::vector<std::shared_ptr<Transformation>> CUBE_TRANSFORMATIONS = {
            std::make_shared<Translation>(glm::vec3(0, 0, -2.5)),
            std::make_shared<Rotation>(glm::vec3(0, 45, 0)),
            std::make_shared<Scale>(1),
    };

    const std::vector<std::shared_ptr<Transformation>> CUBE_TRANSFORMATIONS2 = {
            std::make_shared<Translation>(glm::vec3(0, -3, -2.5)),
            std::make_shared<Rotation>(glm::vec3(0, 45, 0)),
            std::make_shared<Scale>(1),
    };

    shaderProgram.compile();

    Cuboid cube(shaderProgram, 1, 1, 1);

    window.setKeyActions({
         { GLFW_KEY_ESCAPE, [&](GLfloat delta) { window.closeWindow(); } },
         // Camera movement
         { GLFW_KEY_W, [&](GLfloat) { window.moveCamera(Direction::FRONT); } },
         { GLFW_KEY_S, [&](GLfloat) { window.moveCamera(Direction::BACK); } },
         { GLFW_KEY_A, [&](GLfloat) { window.moveCamera(Direction::LEFT); } },
         { GLFW_KEY_D, [&](GLfloat) { window.moveCamera(Direction::RIGHT); } },
     });

    window.run(shaderProgram, [&]() {
        cube.applyTransformations("model", CUBE_TRANSFORMATIONS);
        cube.setColor(Color::RED + Color::YELLOW * 0.5f);
        Renderer::draw<DrawMode::TRIANGLES>(cube);

        cube.applyTransformations("model", CUBE_TRANSFORMATIONS2);
        cube.setColor(Color::RED + Color::RED * 0.5f);
        Renderer::draw<DrawMode::TRIANGLES>(cube);

    });

    return 0;
}
