#ifndef INC_03_TEXTURES_TEXTUREMESH_H
#define INC_03_TEXTURES_TEXTUREMESH_H


#include "../Mesh.h"

class TextureMesh : public Mesh {
private:
    static std::vector<GLfloat> calcAverageNormals(const std::vector<GLfloat> &vertices, const std::vector<unsigned int> &indices, uint32_t vertexLength,  uint32_t normalOffset);
public:
    TextureMesh(const ShaderProgram &shader, const std::vector<GLfloat> &vertices, const std::vector<unsigned int> &indices);
};

#endif