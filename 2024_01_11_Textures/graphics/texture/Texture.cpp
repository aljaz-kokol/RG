#include "Texture.h"
#include <string>

Texture::Texture(std::string_view textureLocation): id(0), width(0), height(0), bitDepth(0), textureLocation(textureLocation) {
    loadRGBA();
}

Texture::Texture(): Texture("") {}

Texture::~Texture() {
    clear();
}

void Texture::clear() {
    glDeleteTextures(1, &id);
    id = 0;
    width = 0;
    bitDepth = 0;
}

void Texture::bind() const {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::loadRGBA() {
    uint8_t* textureData = stbi_load(textureLocation.data(), &width, &height, &bitDepth, 0);
    if (!textureData) {
        throw std::invalid_argument("Texture not found : " + std::string(textureLocation));
    }

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // x axis wrap
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // y axis wrap
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Liner --> try to blend pixels together when zoomin out
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Liner --> try to blend pixels together when zoomin in

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(textureData);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::loadRGB() {
    uint8_t* textureData = stbi_load(textureLocation.data(), &width, &height, &bitDepth, 0);
    if (!textureData) {
        throw std::invalid_argument("Texture not found : " + std::string(textureLocation));
    }

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // x axis wrap
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // y axis wrap
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Liner --> try to blend pixels together when zoomin out
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Liner --> try to blend pixels together when zoomin in

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(textureData);
    glBindTexture(GL_TEXTURE_2D, 0);
}