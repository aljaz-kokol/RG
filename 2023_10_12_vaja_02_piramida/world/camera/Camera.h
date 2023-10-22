#ifndef INC_2023_10_12_VAJA_2_PIRAMIDA_CAMERA_H
#define INC_2023_10_12_VAJA_2_PIRAMIDA_CAMERA_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Camera {
private:
    static constexpr glm::vec3 WORLD_UP = { 0.0f, 1.0f, 0.0f };
    glm::vec3 position;
    glm::vec3 right;
    glm::vec3 up;
    glm::vec3 direction;

    GLfloat yaw; // left-right
    GLfloat pitch; // up-down
    GLfloat movementSpeed;
    GLfloat rotationSpeed;
public:
    Camera(GLfloat startYaw, GLfloat startPitch, GLfloat startMovementSpeed, GLfloat startRotationSpeed);
};

#endif
