#ifndef INC_2023_10_26_VAJA_04_TRANSFORMACIJE_PROJEKCIJE_RENDERER_H
#define INC_2023_10_26_VAJA_04_TRANSFORMACIJE_PROJEKCIJE_RENDERER_H

#include <GL/glew.h>
#include <exception>
#include "../vertex_array/VertexArray.h"
#include "../buffer/index/IndexBuffer.h"
#include "../shader/program/ShaderProgram.h"

#define ASSERT(x) if (!(x)) assert(x);
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class Renderer {
public:
    Renderer() = delete;
    Renderer(const Renderer&) = delete;
    Renderer(Renderer&&) = delete;
    static void clear();
    static void draw(const VertexArray& vao, const IndexBuffer& ibo, const ShaderProgram& program);
};


#endif
