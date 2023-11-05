#include "Keyboard.h"
#include <iostream>

Keyboard::Keyboard(): keys({ false }) {}

bool Keyboard::isPressed(uint32_t key) const noexcept {
    if (key >= 1024) return false;
    return keys[key];
}

void Keyboard::execute(uint32_t key, GLfloat delta) const {
    if (actions.contains(key)) {
        actions.at(key)(delta);
    }
}

void Keyboard::setOnPress(uint32_t key, const std::function<void(GLfloat)>& action) {
    if (key >= 1024) return;
    actions[key] = action;
}

void Keyboard::handleOnKeyAction(uint32_t key, int action, GLfloat deltaTime) {
    if (key >= 5000) return;
    if (action == GLFW_PRESS) {
        keys[key] = true;
        pressedKeys.insert(key);
    } else if (action == GLFW_RELEASE) {
        keys[key] = false;
        pressedKeys.erase(key);
    }

}

void Keyboard::handlePressedKeys(GLfloat deltaTime) const {
    std::unordered_set<uint32_t> usableKeys(pressedKeys);
    for (const auto& entry : actions) {
        const uint32_t combination = entry.first;
        for (uint32_t key1 : pressedKeys) {
            if (!usableKeys.contains(key1)) continue;
            for (uint32_t key2 : pressedKeys) {
                if (!usableKeys.contains(key2)) break;
                if (combination == (key1 + key2)) {
                    execute(combination, deltaTime);
                    usableKeys.erase(key1);
                    usableKeys.erase(key2);
                }
            }
        }
    }

    for (uint32_t key  : usableKeys) {
        execute(key, deltaTime);
    }
}

