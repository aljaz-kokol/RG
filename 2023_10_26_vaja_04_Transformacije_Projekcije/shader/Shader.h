#ifndef INC_2023_10_26_VAJA_04_TRANSFORMACIJE_PROJEKCIJE_SHADER_H
#define INC_2023_10_26_VAJA_04_TRANSFORMACIJE_PROJEKCIJE_SHADER_H

#include <GL/glew.h>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string_view>
#include <sstream>

class Shader {
private:
    GLint id;
    GLenum type;
public:
    Shader(std::string_view fileName, GLenum type);
    void compile() const;
    GLuint getId() const;
};


#endif //INC_2023_10_26_VAJA_04_TRANSFORMACIJE_PROJEKCIJE_SHADER_H
