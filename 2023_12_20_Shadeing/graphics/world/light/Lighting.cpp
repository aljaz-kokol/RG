#include "Lighting.h"

Lighting::Lighting(const std::shared_ptr<Material> &material): material(material) {}

void Lighting::setLights(const std::vector<std::shared_ptr<Light>> &lights) {
    this->lights = lights;
}

void Lighting::use() const {
    material->use();
    for (const auto& light : lights) {
        light->use();
    }
}