#include "Mesh.h"
#include "../renderer/Renderer.h"
#include "transformation/translation/Translation.h"
#include "transformation/rotation/Rotation.h"

Mesh::Mesh(const ShaderProgram& shader, const std::vector<GLfloat>& vertices, const std::vector<unsigned int>& indices)
: vbo(vertices), ibo(indices), shader(shader) {
    vao.bind();
    vbo.bind();
    bufferLayout.push<GL_FLOAT>(3);
    vao.addBuffer(vbo, bufferLayout);


    // Initialize min and max coordinates
    float minX = vertices[0];
    float minY = vertices[1];
    float minZ = vertices[2];
    float maxX = vertices[0];
    float maxY = vertices[1];
    float maxZ = vertices[2];

    // Find min and max coordinates
    for (size_t i = 0; i < vertices.size(); i += 3) {
        minX = std::min(minX, vertices[i]);
        minY = std::min(minY, vertices[i + 1]);
        minZ = std::min(minZ, vertices[i + 2]);
        maxX = std::max(maxX, vertices[i]);
        maxY = std::max(maxY, vertices[i + 1]);
        maxZ = std::max(maxZ, vertices[i + 2]);
    }

    // Calculate dimensions
    dimensions.width = maxX - minX;
    dimensions.height = maxY - minY;
    dimensions.depth = maxZ - minZ;
}

void Mesh::applyTransformations(std::string_view uniformVariable, const Transformations &transformations) const {
    glm::mat4 model(1);
    for (const std::shared_ptr<Transformation>& transformation : transformations) {
        std::shared_ptr<Translation> translation = std::dynamic_pointer_cast<Translation>(transformation);
        model *= transformation->transform();
    }
    shader.setUniform(uniformVariable, model);
}

void Mesh::applyTransformationsFixedToCamera(std::string_view uniformVariable, const Camera& camera, const Transformations &transformations) const {
    glm::mat3 rotationMatrix = glm::mat3(camera.getViewMatrix());
    float yawAngle = atan2(rotationMatrix[0][2], rotationMatrix[2][2]);
    float pitchAngle = asin(-rotationMatrix[1][2]); // Invert the sign due to OpenGL coordinate system

    glm::mat4 model(1);
    model *= Translation(camera.getPosition()).transform();
    model *= Rotation(glm::degrees(yawAngle), glm::vec3(0.0, 1.0, 0.0)).transform();
    model *= Rotation(glm::degrees(pitchAngle), glm::vec3(1.0, 0.0, 0.0)).transform();

    for (const std::shared_ptr<Transformation>& transformation : transformations) {
        std::shared_ptr<Translation> translation = std::dynamic_pointer_cast<Translation>(transformation);
        model *= transformation->transform();
    }
    shader.setUniform(uniformVariable, model);
}

void Mesh::setColor(const Color& color) const {
    shader.setUniform("meshColor", color.getRGBA());
}

void Mesh::setColor(const glm::vec4& color) const {
    shader.setUniform("meshColor", color);
}

const VertexArray &Mesh::getVao() const {
    return vao;
}

const VertexBuffer &Mesh::getVbo() const {
    return vbo;
}

const IndexBuffer &Mesh::getIbo() const {
    return ibo;
}

const ShaderProgram &Mesh::getShaderProgram() const {
    return shader;
}

const Dimensions& Mesh::getDimensions() const {
    return dimensions;
}
