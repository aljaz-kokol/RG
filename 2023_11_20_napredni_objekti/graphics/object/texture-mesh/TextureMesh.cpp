#include "TextureMesh.h"

std::vector<GLfloat> TextureMesh::calcAverageNormals(const std::vector<GLfloat> &vertices, const std::vector<unsigned int> &indices, uint32_t vertexLength, uint32_t normalOffset) {
    std::vector<GLfloat> normalized(vertices);
    for (size_t i = 0; i < indices.size(); i += 3) {
        uint32_t index0 = indices[i] * vertexLength; // point to where in vertices we are pointing to
        uint32_t index1 = indices[i + 1] * vertexLength;
        uint32_t index2 = indices[i + 2] * vertexLength;

        glm::vec3 vertex1(normalized[index1] - normalized[index0], normalized[index1 + 1] - normalized[index0 + 1], normalized[index1 + 2] - normalized[index0 + 2]);
        glm::vec3 vertex2(normalized[index2] - normalized[index0], normalized[index2 + 1] - normalized[index0 + 1], normalized[index2 + 2] - normalized[index0 + 2]);

        glm::vec3 normal = glm::cross(vertex1, vertex2);

        index0 += normalOffset;
        index1 += normalOffset;
        index2 += normalOffset;

        normalized[index0] += normal.x; normalized[index0 + 1] += normal.y; normalized[index0 + 2] += normal.z;
        normalized[index1] += normal.x; normalized[index1 + 1] += normal.y; normalized[index1 + 2] += normal.z;
        normalized[index2] += normal.x; normalized[index2 + 1] += normal.y; normalized[index2 + 2] += normal.z;
    }
    for (size_t i = 0; i < (normalized.size() / vertexLength); i++) {
        uint32_t nOffset = i * vertexLength + normalOffset;
        glm::vec3 vec(normalized[nOffset], normalized[nOffset + 1], normalized[nOffset + 2]);
        vec = glm::normalize(vec);
        normalized[nOffset] = vec.x;
        normalized[nOffset + 1] = vec.y;
        normalized[nOffset + 2] = vec.z;
    }
    return normalized;
}

TextureMesh::TextureMesh(const ShaderProgram &shader, const std::vector<GLfloat> &vertices,const std::vector<unsigned int> &indices) : Mesh(shader, calcAverageNormals(vertices, indices, 8, 5), indices) {
    bufferLayout.push<GL_FLOAT>(2); // 2 additional data points for texture position
    bufferLayout.push<GL_FLOAT>(3); // 3 additional data points for normals
    vao.addBuffer(vbo, bufferLayout);
}
