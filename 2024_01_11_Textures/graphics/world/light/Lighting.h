#ifndef INC_2023_12_20_SHADEING_LIGHTING_H
#define INC_2023_12_20_SHADEING_LIGHTING_H

#include <vector>
#include "Light.h"
#include "../../material/Material.h"

class Lighting {
private:
    std::vector<std::shared_ptr<Light>> lights;
    std::shared_ptr<Material> material;
public:
    explicit Lighting(const std::shared_ptr<Material>& material);
    void setLights(const std::vector<std::shared_ptr<Light>>& lights);
    void use() const;
};

#endif