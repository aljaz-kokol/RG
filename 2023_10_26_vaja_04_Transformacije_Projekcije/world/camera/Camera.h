#ifndef INC_2023_10_26_VAJA_04_TRANSFORMACIJE_PROJEKCIJE_CAMERA_H
#define INC_2023_10_26_VAJA_04_TRANSFORMACIJE_PROJEKCIJE_CAMERA_H

#include <glm/glm.hpp>
#include <GL/glew.h>
#include "../../utils/Direction.h"

class Camera {
private:
    static constexpr glm::vec3 WORLD_UP = { 0, 1, 0 };

    glm::vec3 position;
    glm::vec3 up;
    glm::vec3 front;
    glm::vec3 right;

    GLfloat yaw;
    GLfloat pitch;
    GLfloat movementSpeed;
    GLfloat rotationSpeed;

    void update();
public:
    Camera(const glm::vec3& position, GLfloat yaw, GLfloat pitch, GLfloat movementSpeed, GLfloat rotationSpeed);
    Camera(GLfloat yaw, GLfloat pitch, GLfloat movementSpeed, GLfloat rotationSpeed);
    [[nodiscard]] glm::mat4 getViewMatrix() const;
    void move(Direction direction, GLfloat deltaTime);
    void rotate(GLfloat xChange, GLfloat yChange);
};


#endif
