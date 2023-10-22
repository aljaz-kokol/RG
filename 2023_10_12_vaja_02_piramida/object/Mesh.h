#ifndef INC_2023_10_12_VAJA_2_PIRAMIDA_MESH_H
#define INC_2023_10_12_VAJA_2_PIRAMIDA_MESH_H

#include <GL/glew.h>
#include <GL/glew.h>
#include <vector>
#include "../shader/ShaderProgram.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Mesh {
protected:
    GLuint vao;
    GLuint vbo;
    GLuint ibo;
    std::vector<GLfloat> vertices;
    std::vector<unsigned int> indices;
    glm::mat4 model;
    const ShaderProgram& shader;
public:
    Mesh(const ShaderProgram& shader, const std::vector<GLfloat>& vertices, const std::vector<unsigned int>& indices);
    ~Mesh();
    void draw() const;
    void create();
    void clear();
    void rotateXYZ(float angle, const glm::vec3& coordAmount);
    void scale(const glm::vec3& factors);
    void scale(float factor);
    void translate(const glm::vec3& values);
    void applyTransformations();
    void setColor(const glm::vec4& color);
};


#endif
