#ifndef INC_2023_10_12_VAJA_2_PIRAMIDA_MESH_H
#define INC_2023_10_12_VAJA_2_PIRAMIDA_MESH_H

#include <GL/glew.h>
#include <GL/glew.h>
#include <vector>
#include "../shader/program/ShaderProgram.h"
#include "../vertex_array/VertexArray.h"
#include "../buffer/index/IndexBuffer.h"
#include "../buffer/vertex/VertexBuffer.h"
#include "transformation/Transformation.h"
#include "../color/Color.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Mesh {
protected:
    VertexArray vao;
    VertexBuffer vbo;
    IndexBuffer ibo;
    const ShaderProgram& shader;
public:
    Mesh(const ShaderProgram& shader, const std::vector<GLfloat>& vertices, const std::vector<unsigned int>& indices);
    void applyTransformations(std::string_view uniformVariable, const std::vector<std::shared_ptr<Transformation>> &transformations) const;
    void setColor(const Color& color) const;

    const VertexArray &getVao() const;
    const VertexBuffer &getVbo() const;
    const IndexBuffer &getIbo() const;
    [[nodiscard]] const ShaderProgram &getShaderProgram() const;
};


#endif
