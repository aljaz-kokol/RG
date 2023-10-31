#ifndef INC_2023_10_26_VAJA_04_TRANSFORMACIJE_PROJEKCIJE_RENDERER_H
#define INC_2023_10_26_VAJA_04_TRANSFORMACIJE_PROJEKCIJE_RENDERER_H

#include <GL/glew.h>
#include <exception>
#include "../vertex_array/VertexArray.h"
#include "../buffer/index/IndexBuffer.h"
#include "../shader/program/ShaderProgram.h"
#include "../object/Mesh.h"

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class Renderer {
public:
    Renderer() = delete;
    Renderer(const Renderer&) = delete;
    Renderer(Renderer&&) = delete;
    static void clear();
    static void draw(const Mesh& mesh);
};


#endif
