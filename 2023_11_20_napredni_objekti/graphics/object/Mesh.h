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
#include "../utils/DrawMode.h"
#include "../texture/Texture.h"
#include "../world/camera/Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/type_ptr.hpp>

typedef std::vector<std::shared_ptr<Transformation>> Transformations;

struct Dimensions {
    float width = 0;
    float height = 0;
    float depth = 0;
};

class Mesh {
protected:
    VertexArray vao;
    VertexBuffer vbo;
    IndexBuffer ibo;
    BufferLayout bufferLayout;
    Dimensions dimensions;
    const ShaderProgram& shader;
public:
    Mesh(const ShaderProgram& shader, const std::vector<GLfloat>& vertices, const std::vector<unsigned int>& indices);
    void applyTransformations(std::string_view uniformVariable, const Transformations &transformations) const;
    void applyTransformationsFixedToCamera(std::string_view uniformVariable, const Camera& camera, const Transformations &transformations) const;
    void setColor(const Color& color) const;
    void setColor(const glm::vec4& color) const;

    [[nodiscard]] const VertexArray &getVao() const;
    [[nodiscard]] const VertexBuffer &getVbo() const;
    [[nodiscard]] const IndexBuffer &getIbo() const;
    [[nodiscard]] const ShaderProgram &getShaderProgram() const;
    [[nodiscard]] const Dimensions& getDimensions() const;
};

#endif
