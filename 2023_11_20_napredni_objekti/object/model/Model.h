#ifndef INC_03_TEXTURES_MODEL_H
#define INC_03_TEXTURES_MODEL_H

#include <vector>
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "../texture-mesh/TextureMesh.h"
#include "../../texture/Texture.h"

class Model {
private:
    const ShaderProgram& program;

    std::vector<std::shared_ptr<TextureMesh>> meshList;
    std::vector<std::shared_ptr<Texture>> textureList;
    std::vector<uint32_t> meshToTex; // Meshes may use the same texutre

    void loadNodes(aiNode* node, const aiScene* scene);
    void loadMesh(aiMesh* mesh, const aiScene* scene);
    void loadMaterials(const aiScene* scene); // more detailed textures
public:
    Model(const ShaderProgram& program);

    void load(std::string_view fileName);
    void draw() const;
    void clear();
};

#endif