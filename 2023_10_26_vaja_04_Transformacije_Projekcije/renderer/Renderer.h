#ifndef INC_2023_10_26_VAJA_04_TRANSFORMACIJE_PROJEKCIJE_RENDERER_H
#define INC_2023_10_26_VAJA_04_TRANSFORMACIJE_PROJEKCIJE_RENDERER_H

#include <GL/glew.h>
#include <exception>
#include "../vertex_array/VertexArray.h"
#include "../buffer/index/IndexBuffer.h"
#include "../shader/program/ShaderProgram.h"
#include "../object/Mesh.h"
#include "../utils/DrawMode.h"

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class Renderer {
public:
    Renderer() = delete;
    Renderer(const Renderer&) = delete;
    Renderer(Renderer&&) = delete;
    static void clear();

    template<DrawMode mode>
    static void draw(const Mesh& mesh);
};

template<DrawMode mode>
void Renderer::draw(const Mesh& mesh) {
    mesh.getShaderProgram().bind();
    mesh.getVao().bind();
    mesh.getIbo().bind();
    uint32_t modeValue = static_cast<std::underlying_type<DrawMode>::type>(mode);
    glDrawElements(modeValue, mesh.getIbo().getCount(), GL_UNSIGNED_INT, nullptr);
}

#endif
