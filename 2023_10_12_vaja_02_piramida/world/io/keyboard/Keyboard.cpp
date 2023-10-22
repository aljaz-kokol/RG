#include "Keyboard.h"

Keyboard::Keyboard(): keys({ false }) {}

bool Keyboard::isKeySets(uint16_t key) const {
    if (key >= keys.size()) return false;
    return keys[key];
}

void Keyboard::setKey(uint16_t key, bool value) {
    if (key >= keys.size()) return;
    keys[key] = value;
}