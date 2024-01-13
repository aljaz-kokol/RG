#include "Toolbar.h"
#include "../graphics/renderer/Renderer.h"

Toolbar::Toolbar(const ShaderProgram& program, const Camera &camera)
: camera(camera), baseRectangle(program, 1, 0.03, 0.05),
light(program, Color::WHITE * 0.9f, 0.2), selectedItem(0), program(program)
{}

void Toolbar::draw() const {
    static float selectedItemRotationAngle = 0.0;
    baseRectangle.applyTransformationsFixedToCamera("model", camera, {
        std::make_shared<Translation>(glm::vec3(0, -0.6, -1)),
    });

    baseRectangle.setColor(Color::WHITE * 0.45f);
    Renderer::draw<DrawMode::TRIANGLES>(baseRectangle);

    float containerWidth = baseRectangle.getWidth() + 0.1f;
    float containerHeight = baseRectangle.getHeight() + 0.1f;

    glm::mat3 rotationMatrix = glm::mat3(camera.getViewMatrix());
    float yawAngle = atan2(rotationMatrix[0][2], rotationMatrix[2][2]);
    float pitchAngle = asin(-rotationMatrix[1][2]); // Invert the sign due to OpenGL coordinate system

    for (int32_t i = 0; i < models.size(); i++) {
        const Dimensions& dimensions = models[i]->getDimensions();

        float innerObjectWidth = dimensions.width;
        float innerObjectHeight = dimensions.height;

        float scale = 1.0;
        if (innerObjectWidth > containerWidth || innerObjectHeight > containerHeight) {
            scale = std::min(containerWidth / innerObjectWidth, containerHeight / innerObjectHeight);
        }

        float rotation = i == selectedItem ? selectedItemRotationAngle : 0;

        models[i]->applyTransformAndDraw({
         std::make_shared<Translation>(camera.getPosition()),
         std::make_shared<Rotation>(glm::degrees(yawAngle), glm::vec3(0.0, 1.0, 0.0)),
         std::make_shared<Rotation>(glm::degrees(pitchAngle), glm::vec3(1.0, 0.0, 0.0)),
         std::make_shared<Translation>(glm::vec3(1.0 / models.size() * (i - ((int32_t )models.size()) / 2), -0.32, -0.65)),
         std::make_shared<Rotation>(rotation, glm::vec3(0, 1, 0)),
         std::make_shared<Scale>(scale),
     });
    }

    selectedItemRotationAngle += 1;
    if (selectedItemRotationAngle > 360) selectedItemRotationAngle -= 360;

}

void Toolbar::addModel(const std::string &modelName) {
    Model model(program);
    model.load(modelName);
    models.push_back(std::make_shared<Model>(model));
    modelNames.push_back(modelName);
}

void Toolbar::addModelsFromFolder(std::string_view folder) {
    for (const auto & entry : std::filesystem::directory_iterator(folder)) {
        if (entry.path().string().ends_with(".obj")) {
            addModel(entry.path().string());
        }
    }
}

void Toolbar::clear() {
    modelNames.clear();
    models.clear();
}

void Toolbar::selectItem(uint32_t item) {
    if (item >= models.size()) return;
    selectedItem = item;
}

std::string_view Toolbar::getSelectedModelName() const {
    return modelNames[selectedItem];
}