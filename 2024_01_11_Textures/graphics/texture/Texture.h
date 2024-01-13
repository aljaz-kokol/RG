#ifndef INC_03_TEXTURES_TEXTURE_H
#define INC_03_TEXTURES_TEXTURE_H

#include <GL/glew.h>
#include <string_view>
#include "../stb_image.h"

class Texture {
private:
    GLuint id;
    int32_t width;
    int32_t height;
    int32_t bitDepth;
    std::string_view textureLocation;
public:
    explicit Texture(std::string_view textureLocation);
    Texture();

    ~Texture();
    void bind() const;
    void unbind() const;
    void clear();
    void loadRGBA();
    void loadRGB();
};

#endif