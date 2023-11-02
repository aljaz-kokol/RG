#include "Keyboard.h"
#include <iostream>

Keyboard::Keyboard(): keys({ false }) {}

bool Keyboard::isPressed(uint16_t key) const noexcept {
    if (key >= 1024) return false;
    return keys[key];
}

void Keyboard::execute(uint16_t key) const {
    if (actions.contains(key)) {
        actions.at(key)();
    }
}

void Keyboard::setOnPress(uint16_t key, const std::function<void()>& action) {
    if (key >= 1024) return;
    actions[key] = action;
}

void Keyboard::handleOnKeyAction(uint16_t key, int action) {
    if (key >= 1024) return;
    if (action == GLFW_PRESS) {
        keys[key] = true;
        pressedKeys.insert(key);
    } else if (action == GLFW_RELEASE) {
        keys[key] = false;
        pressedKeys.erase(key);
    }

    std::unordered_set<uint16_t> unusableKeys;
    for (const auto& entry : actions) {
        const uint16_t combination = entry.first;
        for (uint16_t key1 : pressedKeys) {
            if (unusableKeys.contains(key1)) continue;
            for (uint16_t key2 : pressedKeys) {
                if (unusableKeys.contains(key2)) break;
                if (combination == (key1 | key2)) {
                    execute(combination);
                    unusableKeys.insert(key1);
                    unusableKeys.insert(key2);
                }
            }
        }
    }
}

