#ifndef INC_2023_10_26_VAJA_04_TRANSFORMACIJE_PROJEKCIJE_KEYBOARD_H
#define INC_2023_10_26_VAJA_04_TRANSFORMACIJE_PROJEKCIJE_KEYBOARD_H

#include <array>
#include <unordered_map>
#include <glfw/glfw3.h>
#include <functional>
#include <unordered_set>

class Keyboard {
private:
    std::unordered_map<uint32_t, std::function<void(GLfloat)>> actions;
    std::array<bool, 5000> keys;
    std::unordered_set<uint32_t> pressedKeys;
    [[nodiscard]] std::vector<uint32_t> keyList(uint32_t combination) const;
public:
    Keyboard();
    [[nodiscard]] bool isPressed(uint32_t key) const noexcept;
    void execute(uint32_t key, GLfloat deltaTime) const;
    void setOnPress(uint32_t key, const std::function<void(GLfloat)>& action);
    void handleOnKeyAction(uint32_t key, int action, GLfloat deltaTime);
    void handlePressedKeys(GLfloat deltaTime) const;
};

#endif