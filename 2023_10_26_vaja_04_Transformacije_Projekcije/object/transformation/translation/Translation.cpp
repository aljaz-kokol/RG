#include <iostream>
#include "Translation.h"
#include "glm/gtc/matrix_transform.hpp"

Translation::Translation(const glm::vec3 &values)
: values(values) {}

glm::mat4 Translation::transform() const {
    glm::mat4 model(1);
    return glm::translate(model, values);
}

