#ifndef INC_2023_10_26_VAJA_04_TRANSFORMACIJE_PROJEKCIJE_KEYBOARD_H
#define INC_2023_10_26_VAJA_04_TRANSFORMACIJE_PROJEKCIJE_KEYBOARD_H

#include <array>
#include <unordered_map>
#include <glfw/glfw3.h>
#include <functional>
#include <unordered_set>

class Keyboard {
private:
    std::unordered_map<uint16_t, std::function<void()>> actions;
    std::array<bool, 1024> keys;
    std::unordered_set<uint16_t> pressedKeys;

    bool checkForKeyCombinations() const;
public:
    Keyboard();
    [[nodiscard]] bool isPressed(uint16_t key) const noexcept;
    void execute(uint16_t key) const;
    void setOnPress(uint16_t key, const std::function<void()>& action);
    void handleOnKeyAction(uint16_t key, int action);
};

#endif