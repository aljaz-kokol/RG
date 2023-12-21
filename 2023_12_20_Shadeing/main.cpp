#define STB_IMAGE_IMPLEMENTATION
#include <gl/glew.h>
#include "graphics/world/window/OpenGLWindow.h"
#include "graphics/shader/program/ShaderProgram.h"
#include "graphics/object/model/Model.h"
#include "graphics/world/light/Light.h"
#include "graphics/material/Material.h"
#include "toolbar/Toolbar.h"
#include "graphics/utils/font/Font.h"
#include "graphics/world/light/Lighting.h"
#include "graphics/world/light/diffuse/DiffuseLight.h"
#include "graphics/renderer/Renderer.h"
#include <memory>
#include <sstream>

enum class LightEditMode {
    SHINE,
    SPECULAR_INTENSITY,
    DIFFUSE_INTENSITY,
    AMBIENT_INTENSITY,
    LIGHT_MOVE,
};

int main() {
    OpenGLWindow window( "06 - Shaders", 1920, 1080);

    ShaderProgram modelShader({
      { "assets/shaders/model/vertex.vert",   GL_VERTEX_SHADER },
      { "assets/shaders/model/fragment.frag", GL_FRAGMENT_SHADER }
    });

    ShaderProgram textShader({
      { "assets/shaders/text/vertex.vert",   GL_VERTEX_SHADER },
      { "assets/shaders/text/fragment.frag", GL_FRAGMENT_SHADER }
    });

    modelShader.compile();
    textShader.compile();
    window.setTextRenderShader(std::make_shared<ShaderProgram>(textShader));

    Toolbar toolbar(modelShader, window.getCamera());
    toolbar.addModelsFromFolder("assets/models");
    std::shared_ptr<Material> shinnyMaterial = std::make_shared<Material>(modelShader, 0.4, 50);
    Lighting lighting(shinnyMaterial);
    AmbientLight maxLight(modelShader, Color::WHITE, 1);

    std::shared_ptr<AmbientLight> ambientLight = std::make_shared<AmbientLight>(modelShader, Color::WHITE * 0.9f, 0.3f);
    std::shared_ptr<DiffuseLight> diffuseLight = std::make_shared<DiffuseLight>(modelShader, glm::vec3(1, 1, 1), 0.8);

    LightEditMode lightEditMode = LightEditMode::SHINE;
    Cuboid light(modelShader, 1, 1, 1);

    window.setKeyActions({
         { GLFW_KEY_ESCAPE, [&](GLfloat delta) { window.closeWindow(); } },
         { GLFW_KEY_TAB,  [&](GLfloat delta) {
             switch (lightEditMode) {
                 case LightEditMode::SHINE: lightEditMode = LightEditMode::SPECULAR_INTENSITY; break;
                 case LightEditMode::SPECULAR_INTENSITY: lightEditMode = LightEditMode::DIFFUSE_INTENSITY; break;
                 case LightEditMode::DIFFUSE_INTENSITY: lightEditMode = LightEditMode::AMBIENT_INTENSITY; break;
                 case LightEditMode::AMBIENT_INTENSITY: lightEditMode = LightEditMode::LIGHT_MOVE; break;
                 case LightEditMode::LIGHT_MOVE: lightEditMode = LightEditMode::SHINE; break;
             }
         } },
         { GLFW_KEY_W, [&](GLfloat) { window.moveCamera(Direction::FRONT); } },
         { GLFW_KEY_S, [&](GLfloat) { window.moveCamera(Direction::BACK); } },
         { GLFW_KEY_A, [&](GLfloat) { window.moveCamera(Direction::LEFT); } },
         { GLFW_KEY_D, [&](GLfloat) { window.moveCamera(Direction::RIGHT); } },
         { GLFW_KEY_R, [&](GLfloat) {
             toolbar.clear();
             toolbar.addModelsFromFolder("assets/models");
         }},
         { GLFW_KEY_W + GLFW_KEY_LEFT_SHIFT, [&](GLfloat) { window.moveSelectedModel(Direction::UP); } },
         { GLFW_KEY_S + GLFW_KEY_LEFT_SHIFT, [&](GLfloat) { window.moveSelectedModel(Direction::DOWN); } },
         { GLFW_KEY_A + GLFW_KEY_LEFT_SHIFT, [&](GLfloat) { window.moveSelectedModel(Direction::LEFT); } },
         { GLFW_KEY_D + GLFW_KEY_LEFT_SHIFT, [&](GLfloat) { window.moveSelectedModel(Direction::RIGHT); } },
         { GLFW_KEY_Q + GLFW_KEY_LEFT_SHIFT, [&](GLfloat) { window.moveSelectedModel(Direction::FRONT); } },
         { GLFW_KEY_E + GLFW_KEY_LEFT_SHIFT, [&](GLfloat) { window.moveSelectedModel(Direction::BACK); } },

         { GLFW_KEY_CAPS_LOCK + GLFW_KEY_W, [&](GLfloat) {
             glm::vec3 pos = diffuseLight->getDirection();
             pos.y += 0.05;
             diffuseLight->setDirection(pos);
         } },

         { GLFW_KEY_CAPS_LOCK + GLFW_KEY_S, [&](GLfloat) {
             glm::vec3 pos = diffuseLight->getDirection();
             pos.y -= 0.05;
             diffuseLight->setDirection(pos);
         } },

         { GLFW_KEY_CAPS_LOCK + GLFW_KEY_A, [&](GLfloat) {
             glm::vec3 pos = diffuseLight->getDirection();
             pos.x -= 0.05;
             diffuseLight->setDirection(pos);
         } },

         { GLFW_KEY_CAPS_LOCK + GLFW_KEY_D, [&](GLfloat) {
             glm::vec3 pos = diffuseLight->getDirection();
             pos.x += 0.05;
             diffuseLight->setDirection(pos);
         } },

         { GLFW_KEY_CAPS_LOCK + GLFW_KEY_Q, [&](GLfloat) {
             glm::vec3 pos = diffuseLight->getDirection();
             pos.z += 0.05;
             diffuseLight->setDirection(pos);
         } },

         { GLFW_KEY_CAPS_LOCK + GLFW_KEY_E, [&](GLfloat) {
             glm::vec3 pos = diffuseLight->getDirection();
             pos.z -= 0.05;
             diffuseLight->setDirection(pos);
         } },

         { GLFW_KEY_1, [&](GLfloat) { toolbar.selectItem(0); } },
         { GLFW_KEY_2, [&](GLfloat) { toolbar.selectItem(1); } },
         { GLFW_KEY_3, [&](GLfloat) { toolbar.selectItem(2); } },
         { GLFW_KEY_4, [&](GLfloat) { toolbar.selectItem(3); } },
         { GLFW_KEY_5, [&](GLfloat) { toolbar.selectItem(4); } },
         { GLFW_KEY_6, [&](GLfloat) { toolbar.selectItem(5); } },
         { GLFW_KEY_7, [&](GLfloat) { toolbar.selectItem(6); } },
         { GLFW_KEY_8, [&](GLfloat) { toolbar.selectItem(7); } },
         { GLFW_KEY_9, [&](GLfloat) { toolbar.selectItem(8); } },

         { GLFW_KEY_UP + GLFW_KEY_LEFT_SHIFT, [&](GLfloat) { window.rotateSelectedModel(RotationDirection::X_NEG); } },
         { GLFW_KEY_DOWN + GLFW_KEY_LEFT_SHIFT, [&](GLfloat) { window.rotateSelectedModel(RotationDirection::X_POS); } },
         { GLFW_KEY_RIGHT, [&](GLfloat) { window.rotateSelectedModel(RotationDirection::Y_POS); } },
         { GLFW_KEY_LEFT, [&](GLfloat) { window.rotateSelectedModel(RotationDirection::Y_NEG); } },

         { GLFW_KEY_UP, [&](GLfloat) {
             if (lightEditMode == LightEditMode::SHINE) {
                 shinnyMaterial->setShininess(shinnyMaterial->getShininess() + 0.5);
             } else if (lightEditMode == LightEditMode::SPECULAR_INTENSITY) {
                 shinnyMaterial->setSpecularIntensity(shinnyMaterial->getSpecularIntensity() + 0.01);
             } else if (lightEditMode == LightEditMode::DIFFUSE_INTENSITY) {
                 diffuseLight->setIntensity(diffuseLight->getIntensity() + 0.01);
             } else if (lightEditMode == LightEditMode::AMBIENT_INTENSITY) {
                 ambientLight->setIntensity(ambientLight->getIntensity() + 0.01);
             }
         } },
         { GLFW_KEY_DOWN, [&](GLfloat) {
             if (lightEditMode == LightEditMode::SHINE) {
                 shinnyMaterial->setShininess(shinnyMaterial->getShininess() - 0.5);
             } else if (lightEditMode == LightEditMode::SPECULAR_INTENSITY) {
                 shinnyMaterial->setSpecularIntensity(shinnyMaterial->getSpecularIntensity() - 0.01);
             } else if (lightEditMode == LightEditMode::DIFFUSE_INTENSITY) {
                 diffuseLight->setIntensity(diffuseLight->getIntensity() - 0.01);
             } else if (lightEditMode == LightEditMode::AMBIENT_INTENSITY) {
                 ambientLight->setIntensity(ambientLight->getIntensity() - 0.01);
             }
         } },
     });

    window.addFont("roboto", "assets/fonts/Roboto/Roboto-Regular.ttf");

    window.setOnClick([&]() {
        if (window.selectModel()) return;
        Model model(modelShader, window.getCamera());
        model.load(toolbar.getSelectedModelName());
        window.addDrawModel(std::make_shared<Model>(model));
    });

    std::stringstream strBuilder;

    window.run(modelShader, [&]() {
        maxLight.use();
        light.setColor(Color::WHITE);
        light.applyTransformations("model", {
            std::make_shared<Translation>(diffuseLight->getDirection()),
            std::make_shared<Scale>(0.1),
        });
        Renderer::draw<DrawMode::TRIANGLES>(light);
        maxLight.unbind();

        lighting.setLights({ ambientLight, diffuseLight });
        lighting.use();
        toolbar.draw();

        strBuilder.str("");
        strBuilder << "Shine : " << shinnyMaterial->getShininess();
        window.renderText("roboto", strBuilder.str(), 50, 1050, 0.5, lightEditMode == LightEditMode::SHINE ? Color::GREEN : Color::WHITE);

        strBuilder.str("");
        strBuilder << "Specular Intensity : " << shinnyMaterial->getSpecularIntensity();
        window.renderText("roboto", strBuilder.str(), 50, 1020, 0.5, lightEditMode == LightEditMode::SPECULAR_INTENSITY ? Color::GREEN : Color::WHITE);

        strBuilder.str("");
        strBuilder << "Diffuse Intensity : " << diffuseLight->getIntensity();
        window.renderText("roboto", strBuilder.str(), 50, 990, 0.5, lightEditMode == LightEditMode::DIFFUSE_INTENSITY ? Color::GREEN : Color::WHITE);

        strBuilder.str("");
        strBuilder << "Ambient Intensity : " << ambientLight->getIntensity();
        window.renderText("roboto", strBuilder.str(), 50, 960, 0.5, lightEditMode == LightEditMode::AMBIENT_INTENSITY ? Color::GREEN : Color::WHITE);

        strBuilder.str("");
        strBuilder << "Light pos. : (x : " << diffuseLight->getDirection().x << ", y: " << diffuseLight->getDirection().y << ", z: " << diffuseLight->getDirection().z << ")";
        window.renderText("roboto", strBuilder.str(), 50, 930, 0.5, lightEditMode == LightEditMode::LIGHT_MOVE ? Color::GREEN : Color::WHITE);
    });

    return 0;
}
