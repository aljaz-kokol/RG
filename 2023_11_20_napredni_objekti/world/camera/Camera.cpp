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

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(position, position + front, up);
}

const glm::vec3 &Camera::getPosition() const {
    return position;
}
