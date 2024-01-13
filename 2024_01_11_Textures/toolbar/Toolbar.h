#ifndef INC_2023_11_20_NAPREDNI_OBJEKTI_TOOLBAR_H
#define INC_2023_11_20_NAPREDNI_OBJEKTI_TOOLBAR_H

#include "../graphics/world/camera/Camera.h"
#include "memory"
#include "../graphics/object/model/Model.h"
#include "../graphics/object/cuboid/Cuboid.h"
#include "../graphics/world/light/Light.h"
#include "../graphics/world/light/ambient/AmbientLight.h"

class Toolbar {
private:
    const Camera& camera;
    const ShaderProgram& program;
    Cuboid baseRectangle;
    AmbientLight light;
    std::vector<std::shared_ptr<Model>> models;
    std::vector<std::string> modelNames;
    uint32_t selectedItem;

public:
    Toolbar(const ShaderProgram& program, const Camera& camera);
    void draw() const;
    void addModel(const std::string &modelName);
    void addModelsFromFolder(std::string_view folder);
    void selectItem(uint32_t item);
    void clear();
    [[nodiscard]] std::string_view getSelectedModelName() const;
};


#endif