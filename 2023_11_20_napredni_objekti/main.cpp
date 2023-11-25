#define STB_IMAGE_IMPLEMENTATION
#include <gl/glew.h>
#include "graphics/world/window/OpenGLWindow.h"
#include "graphics/shader/program/ShaderProgram.h"
#include "graphics/object/cuboid/cuboid-shape/CuboidShape.h"
#include "graphics/object/model/Model.h"
#include "graphics/world/light/Light.h"
#include "graphics/material/Material.h"
#include "toolbar/Toolbar.h"
#include <filesystem>
#include <memory>

int main() {

    OpenGLWindow window("02 - piramida", 1920, 1080);

    ShaderProgram shaderProgram({
        { "vertex.vert",   GL_VERTEX_SHADER },
        { "fragment.frag", GL_FRAGMENT_SHADER }
    });

    shaderProgram.compile();

    Cuboid cursor(shaderProgram, 0.1, 0.1, 0.1);

    Material shinnyMaterial(shaderProgram, 0.4  , 4);
    Light ambientLight(shaderProgram, Color::WHITE, 0.5, glm::vec3(2, -1, -2), 0.5);
    Light brightLight(shaderProgram, Color::WHITE, 1, glm::vec3(2, -1, -2), 1);
    Toolbar toolbar(shaderProgram, window.getCamera());

    std::string path = "models";
    for (const auto & entry : std::filesystem::directory_iterator(path)) {
        toolbar.addModel(shaderProgram, entry.path().string());
    }

    window.setKeyActions({
         { GLFW_KEY_ESCAPE, [&](GLfloat delta) { window.closeWindow(); } },
         // Camera movement

         { GLFW_KEY_TAB,  [&](GLfloat delta) { window.selectNextModel(); } },

         { GLFW_KEY_W, [&](GLfloat) { window.moveCamera(Direction::FRONT); } },
         { GLFW_KEY_S, [&](GLfloat) { window.moveCamera(Direction::BACK); } },
         { GLFW_KEY_A, [&](GLfloat) { window.moveCamera(Direction::LEFT); } },
         { GLFW_KEY_D, [&](GLfloat) { window.moveCamera(Direction::RIGHT); } },
         { GLFW_KEY_R, [&](GLfloat) {
             std::string path = "models";
             toolbar.clear();
             for (const auto & entry : std::filesystem::directory_iterator(path)) {
                 toolbar.addModel(shaderProgram, entry.path().string());
             }
         } },

         { GLFW_KEY_W +  GLFW_KEY_LEFT_SHIFT, [&](GLfloat) { window.moveSelectedModel(Direction::UP); } },
         { GLFW_KEY_S +  GLFW_KEY_LEFT_SHIFT, [&](GLfloat) { window.moveSelectedModel(Direction::DOWN); } },
         { GLFW_KEY_A +  GLFW_KEY_LEFT_SHIFT, [&](GLfloat) { window.moveSelectedModel(Direction::LEFT); } },
         { GLFW_KEY_D +  GLFW_KEY_LEFT_SHIFT, [&](GLfloat) { window.moveSelectedModel(Direction::RIGHT); } },
         { GLFW_KEY_Q +  GLFW_KEY_LEFT_SHIFT, [&](GLfloat) { window.moveSelectedModel(Direction::FRONT); } },
         { GLFW_KEY_E +  GLFW_KEY_LEFT_SHIFT, [&](GLfloat) { window.moveSelectedModel(Direction::BACK); } },

         { GLFW_KEY_1, [&](GLfloat) { toolbar.selectItem(0); } },
         { GLFW_KEY_2, [&](GLfloat) { toolbar.selectItem(1); } },
         { GLFW_KEY_3, [&](GLfloat) { toolbar.selectItem(2); } },
         { GLFW_KEY_4, [&](GLfloat) { toolbar.selectItem(3); } },
         { GLFW_KEY_5, [&](GLfloat) { toolbar.selectItem(4); } },
         { GLFW_KEY_6, [&](GLfloat) { toolbar.selectItem(5); } },
         { GLFW_KEY_7, [&](GLfloat) { toolbar.selectItem(6); } },
         { GLFW_KEY_8, [&](GLfloat) { toolbar.selectItem(7); } },
         { GLFW_KEY_9, [&](GLfloat) { toolbar.selectItem(8); } },
     });

    window.setOnClick([&]() {
        Model model(shaderProgram, window.getCamera());
        model.load(toolbar.getSelectedModelName());
        window.addDrawModel(std::make_shared<Model>(model));
    });


    window.run(shaderProgram, [&]() {
        brightLight.use();
        cursor.setColor(Color::WHITE);
        cursor.applyTransformationsFixedToCamera("model", window.getCamera(), {
                std::make_shared<Translation>(glm::vec3{0, 0, -2}),
                std::make_shared<Scale>(0.1),
        });
        Renderer::draw<DrawMode::TRIANGLES>(cursor);

        ambientLight.use();
        shinnyMaterial.bind();
        toolbar.draw();
    });

    return 0;
}
