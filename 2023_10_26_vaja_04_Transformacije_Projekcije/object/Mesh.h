#ifndef INC_2023_10_12_VAJA_2_PIRAMIDA_MESH_H
#define INC_2023_10_12_VAJA_2_PIRAMIDA_MESH_H

#include <GL/glew.h>
#include <GL/glew.h>
#include <vector>
#include "../shader/program/ShaderProgram.h"
#include "../vertex_array/VertexArray.h"
#include "../buffer/index/IndexBuffer.h"
#include "../buffer/vertex/VertexBuffer.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Mesh {
protected:
    VertexArray vao;
    VertexBuffer vbo;
    IndexBuffer ibo;
    glm::mat4 model;
    const ShaderProgram& shader;
public:
    Mesh(const ShaderProgram& shader, const std::vector<GLfloat>& vertices, const std::vector<unsigned int>& indices);
    void draw() const;
    void rotateXYZ(float angle, const glm::vec3& coordAmount);
    void scale(const glm::vec3& factors);
    void scale(float factor);
    void translate(const glm::vec3& values);
    void applyTransformations();
    void setColor(const glm::vec4& color);
};


#endif
