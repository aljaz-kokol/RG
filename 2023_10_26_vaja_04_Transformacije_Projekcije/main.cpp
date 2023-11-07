#include <gl/glew.h>
#include "world/window/OpenGLWindow.h"
#include "renderer/Renderer.h"
#include "shader/program/ShaderProgram.h"
#include "object/transformation/translation/Translation.h"
#include "object/transformation/scale/Scale.h"
#include "object/cuboid/cuboid-shape/CuboidShape.h"
#include <glm/glm.hpp>

int main() {
    OpenGLWindow window("02 - piramida", 800, 800);

    ShaderProgram shaderProgram({
        { "vertex.vert",   GL_VERTEX_SHADER },
        { "fragment.frag", GL_FRAGMENT_SHADER }
    });

    const std::vector<std::shared_ptr<Transformation>> FLOOR_TRANSFORMATIONS = {
            std::make_unique<Translation>(glm::vec3(0, -0.9, -3.05)),
            std::make_unique<Scale>(glm::vec3(1.3, 0.01, 1.3 )),
    };

    Cuboid cube(shaderProgram, 1, 1, 1);

    CuboidShape pyramid(
        cube,
        {
            { { -1, -1, -1.5 }, Color(Color::BLUE) }, { { 0, -1, -1.5 }, Color(Color::YELLOW) }, { { 1, -1, -1.5 }, Color(Color::RED) },
            { { -0.5, 0, -1.5 }, Color(Color::GREEN) }, { { 0.5, 0, -1.5 }, Color(Color::CYAN) },
            { { 0, 1, -1.5 }, Color(Color::MAGENTA) },
        },
        0.3
    );

    shaderProgram.compile();

    window.setKeyActions({
         { GLFW_KEY_ESCAPE, [&](GLfloat delta) { window.closeWindow(); } },
         // Pyramid movement
         { GLFW_KEY_W + GLFW_KEY_LEFT_SHIFT, [&](GLfloat delta) { pyramid.move(Direction::UP, 2.5, delta); } },
         { GLFW_KEY_S + GLFW_KEY_LEFT_SHIFT, [&](GLfloat delta) { pyramid.move(Direction::DOWN, 2.5, delta);} },
         { GLFW_KEY_A + GLFW_KEY_LEFT_SHIFT, [&](GLfloat delta) { pyramid.move(Direction::LEFT, 2.5, delta); } },
         { GLFW_KEY_D + GLFW_KEY_LEFT_SHIFT, [&](GLfloat delta) { pyramid.move(Direction::RIGHT, 2.5, delta); } },
         { GLFW_KEY_Q + GLFW_KEY_LEFT_SHIFT, [&](GLfloat delta) { pyramid.move(Direction::FRONT, 2.5, delta); } },
         { GLFW_KEY_E + GLFW_KEY_LEFT_SHIFT, [&](GLfloat delta) { pyramid.move(Direction::BACK, 2.5, delta); } },
         // Camera movement
         { GLFW_KEY_W, [&](GLfloat delta) { window.moveCamera(Direction::FRONT); } },
         { GLFW_KEY_S, [&](GLfloat delta) { window.moveCamera(Direction::BACK); } },
         { GLFW_KEY_A, [&](GLfloat delta) { window.moveCamera(Direction::LEFT); } },
         { GLFW_KEY_D, [&](GLfloat delta) { window.moveCamera(Direction::RIGHT); } },
         // Pyramid scale
         { GLFW_KEY_UP + GLFW_KEY_LEFT_SHIFT, [&](GLfloat delta) { pyramid.scale(Direction::UP, 0.005); } },
         { GLFW_KEY_DOWN + GLFW_KEY_LEFT_SHIFT, [&](GLfloat delta) { pyramid.scale(Direction::DOWN, 0.005); } },
         // Pyramid rotation
         { GLFW_KEY_DOWN, [&](GLfloat delta) { pyramid.rotate(RotationDirection::X_POS, 12, delta); } },
         { GLFW_KEY_UP, [&](GLfloat delta) { pyramid.rotate(RotationDirection::X_NEG, 12, delta); } },
         { GLFW_KEY_RIGHT, [&](GLfloat delta) { pyramid.rotate(RotationDirection::Y_POS, 12, delta); } },
         { GLFW_KEY_LEFT, [&](GLfloat delta) { pyramid.rotate(RotationDirection::Y_NEG, 12, delta); } },
         { GLFW_KEY_RIGHT + GLFW_KEY_LEFT_SHIFT, [&](GLfloat delta) { pyramid.rotate(RotationDirection::Z_NEG, 12, delta); } },
         { GLFW_KEY_LEFT + GLFW_KEY_LEFT_SHIFT, [&](GLfloat delta) { pyramid.rotate(RotationDirection::Z_POS, 12, delta); } },
         // Projection Change
         { GLFW_KEY_P, [&](GLfloat delta) { window.setProjectionToPerspective(); } },
         { GLFW_KEY_O, [&](GLfloat delta) { window.setProjectionToOrthographic(); } }
    });

    window.run(shaderProgram, [&]() {
        pyramid.draw<DrawMode::TRIANGLES>();

        cube.applyTransformations("model", FLOOR_TRANSFORMATIONS);
        cube.setColor(Color::RED + Color::YELLOW * 0.5f);
        Renderer::draw<DrawMode::TRIANGLES>(cube);
    });

    return 0;
}
