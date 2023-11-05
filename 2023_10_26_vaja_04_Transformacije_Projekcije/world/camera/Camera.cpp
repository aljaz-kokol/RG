#include "Camera.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>


Camera::Camera(const glm::vec3 &position, GLfloat yaw, GLfloat pitch, GLfloat movementSpeed, GLfloat rotationSpeed)
: position(position), yaw(yaw), pitch(pitch), up(0), movementSpeed(movementSpeed), rotationSpeed(rotationSpeed) {
    update();
}

Camera::Camera(GLfloat yaw, GLfloat pitch, GLfloat movementSpeed, GLfloat rotationSpeed)
: Camera(glm::vec3(0, 0, 0), yaw, pitch, movementSpeed, rotationSpeed) {}


void Camera::update() {
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front);

    right = glm::normalize(glm::cross(front, WORLD_UP));
    up = glm::normalize(glm::cross(right, front));
}

glm::mat4 Camera::getViewMatrix() const {
//    glm::vec3 cameraRight = glm::normalize(glm::cross(up, -front));
//    glm::vec3 cameraUp = glm::normalize(glm::cross(-front, cameraRight));
//
//    glm::mat4 viewMatrix = {
//            glm::vec4(cameraRight.x, up.x, -front.x, 0.0f),
//            glm::vec4(cameraRight.y, up.y, -front.y, 0.0f),
//            glm::vec4(cameraRight.z, up.z, -front.z, 0.0f),
//            glm::vec4(-glm::dot(cameraRight, position), -glm::dot(up, position), glm::dot(front, position), 1.0f)
//    };

    return glm::lookAt(position, position + front, up);
}

void Camera::move(Direction direction, GLfloat deltaTime) {
    const GLfloat VELOCITY = movementSpeed * deltaTime;
    if (direction == Direction::FRONT) {
        position += front * VELOCITY;
    } else if (direction == Direction::BACK) {
        position -= front * VELOCITY;
    } else if (direction == Direction::RIGHT) {
        position += right * VELOCITY;
    } else if (direction == Direction::LEFT) {
        position -= right * VELOCITY;
    }
}

void Camera::rotate(GLfloat xChange, GLfloat yChange) {
    xChange *= rotationSpeed;
    yChange *= rotationSpeed;

    yaw += xChange;
    pitch -= yChange;

    if (pitch > 89.0f) {
        pitch = 89.0f;
    } else if (pitch < -89.0f) {
        pitch = -89.0f;
    }
    update();
}