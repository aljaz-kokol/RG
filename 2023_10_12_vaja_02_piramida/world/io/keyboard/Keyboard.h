#ifndef INC_2023_10_12_VAJA_2_PIRAMIDA_KEYBOARD_H
#define INC_2023_10_12_VAJA_2_PIRAMIDA_KEYBOARD_H

#include <cstdint>
#include <array>

class Keyboard {
private:
    std::array<bool, 1024> keys;
public:
    Keyboard();
    void setKey(uint16_t key, bool value);
    [[nodiscard]] bool isKeySets(uint16_t key) const;
};

#endif
