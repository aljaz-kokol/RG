#include "Model.h"
#include "../../renderer/Renderer.h"
#include "../transformation/scale/Scale.h"
#include "../transformation/translation/Translation.h"

Model::Model(const ShaderProgram &program): program(program) {}

void Model::load(std::string_view fileName) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(fileName.data(), aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);
    if (!scene) {
        throw std::invalid_argument("Model " + std::string(fileName) + " failed to load : " + importer.GetErrorString());
    }
    loadNodes(scene->mRootNode, scene);
    loadMaterials(scene);
}

void Model::loadNodes(aiNode *node, const aiScene *scene) {
    for (size_t i = 0; i < node->mNumMeshes; i++) {
        loadMesh(scene->mMeshes[node->mMeshes[i]], scene);
    }
    for (size_t i = 0; i < node->mNumChildren; i++) {
        loadNodes(node->mChildren[i], scene);
    }
}

void Model::loadMesh(aiMesh *mesh, const aiScene *scene) {
    std::vector<GLfloat> vertices;
    std::vector<uint32_t> indices;
    for (size_t i = 0; i < mesh->mNumVertices; i++) {
        vertices.insert(vertices.end(), { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z });
        if (mesh->mTextureCoords[0]) { // load first texture
            vertices.insert(vertices.end(), { mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y });
        } else {
            vertices.insert(vertices.end(), { 0.0f, 0.0f });
        }
        vertices.insert(vertices.end(), { -mesh->mNormals[i].x, -mesh->mNormals[i].y, -mesh->mNormals[i].z  });
    }

    for (size_t i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (size_t j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    std::shared_ptr<TextureMesh> newMesh = std::make_shared<TextureMesh>(program, vertices, indices);
    meshList.push_back(newMesh);
    meshToTex.push_back(mesh->mMaterialIndex);
}

void Model::loadMaterials(const aiScene *scene) {
    textureList.resize(scene->mNumMaterials);
    for (size_t i = 0; i < scene->mNumMaterials; i++) {
        aiMaterial* material = scene->mMaterials[i];
        textureList[i] = nullptr;
        if (material->GetTextureCount(aiTextureType_DIFFUSE)) {
            aiString path;
            if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS) {
                int32_t index = std::string(path.data).rfind('\\');
                std::string fileName = std::string(path.data).substr(index + 1);
                std::string texPath = "textures/" + fileName;
                textureList[i] = std::make_shared<Texture>(texPath);
                try {
                    textureList[i]->loadRGB();
                } catch (const std::exception& ex) {
                    textureList[i] = nullptr;
                }
            }
        }
        if (!textureList[i]) {
            textureList[i] = std::make_shared<Texture>("textures/plain.png");
            textureList[i]->loadRGBA();
        }
    }
}

void Model::draw() const {
    for (size_t i = 0; i < meshList.size(); i++) {
        uint32_t materialIndex = meshToTex[i];
        if (materialIndex < textureList.size() && textureList[materialIndex]) {
            textureList[materialIndex]->bind();
        }
        meshList[i]->applyTransformations("model", {
            std::make_shared<Translation>(glm::vec3(-7, 0.0, 10)),
            std::make_shared<Scale>(0.006f),
        });
        Renderer::draw<DrawMode::TRIANGLES>(*meshList[i]);
    }
}