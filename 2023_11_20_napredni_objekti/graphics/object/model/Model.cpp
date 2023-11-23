#include "Model.h"
#include "../../renderer/Renderer.h"

Model::Model(const ShaderProgram &program): program(program), positions(0), rotation(0), translation(glm::vec3(0)), scale(1), color(Color::WHITE) {
    transformations = {
        std::make_shared<Translation>(translation),
        std::make_shared<Rotation>(rotation),
        std::make_shared<Scale>(scale),
    };
}

Model::Model(const ShaderProgram &program, const Camera& camera)
: program(program), positions(glm::vec3(camera.getPosition().x, camera.getPosition().y,camera.getPosition().z -5)),
rotation(0), scale(1), color(Color::WHITE),
translation(glm::vec3(0, 0, -5)) {
    glm::mat3 rotationMatrix = glm::mat3(camera.getViewMatrix());
    float yawAngle = atan2(rotationMatrix[0][2], rotationMatrix[2][2]);
    float pitchAngle = asin(-rotationMatrix[1][2]);

    translation = Translation(camera.getPosition() - glm::vec3(0, 0, -5));

    transformations = {
        std::make_shared<Translation>(camera.getPosition()),
        std::make_shared<Rotation>(glm::degrees(yawAngle), glm::vec3(0.0, 1.0, 0.0)),
        std::make_shared<Rotation>(glm::degrees(pitchAngle), glm::vec3(1.0, 0.0, 0.0)),
        std::make_shared<Translation>(glm::vec3{0, 0, -5})
    };


}

void Model::load(std::string_view fileName) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(fileName.data(), aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);
    if (!scene) {
        throw std::invalid_argument("Model " + std::string(fileName) + " failed to load : " + importer.GetErrorString());
    }
    loadNodes(scene->mRootNode, scene);
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
    dimensions.width += newMesh->getDimensions().width;
    dimensions.height += newMesh->getDimensions().height;
    dimensions.depth += newMesh->getDimensions().depth;

    meshList.push_back(newMesh);
}

void Model::move(Direction direction, float value, GLfloat delta) {
    const GLfloat VELOCITY = value * delta;
    if (direction == Direction::LEFT) {
        positions[0] -= value * VELOCITY;
    } else if (direction == Direction::RIGHT) {
        positions[0] += value * VELOCITY;
    } else if (direction == Direction::UP) {
        positions[1] += value * VELOCITY;
    } else if (direction == Direction::DOWN) {
        positions[1] -= value * VELOCITY;
    } else if (direction == Direction::FRONT) {
        positions[2] += value * VELOCITY;
    } else if (direction == Direction::BACK) {
        positions[2] -= value * VELOCITY;
    }

    translation.setValues(glm::vec3(
        2 * 1 * positions[0] * 1,
        2 * 1 * positions[1] * 1,
        2 * positions[2]
    ));

    transformations = {
            std::make_shared<Translation>(translation),
            std::make_shared<Rotation>(rotation),
            std::make_shared<Scale>(scale),
    };
}

void Model::draw() const {
    for (size_t i = 0; i < meshList.size(); i++) {
        meshList[i]->setColor(color);
        meshList[i]->applyTransformations("model", transformations);
        Renderer::draw<DrawMode::TRIANGLES>(*meshList[i]);
    }
}

void Model::draw(const Camera &camera) const {
    for (size_t i = 0; i < meshList.size(); i++) {
        meshList[i]->setColor(color);

        glm::mat3 rotationMatrix = glm::mat3(camera.getViewMatrix());
        float yawAngle = atan2(rotationMatrix[0][2], rotationMatrix[2][2]);
        float pitchAngle = asin(-rotationMatrix[1][2]); // Invert the sign due to OpenGL coordinate system

        meshList[i]->applyTransformations("model", {
            std::make_shared<Translation>(camera.getPosition()),
            std::make_shared<Rotation>(glm::degrees(yawAngle), glm::vec3(0.0, 1.0, 0.0)),
            std::make_shared<Rotation>(glm::degrees(pitchAngle), glm::vec3(1.0, 0.0, 0.0)),

            std::make_shared<Translation>(translation),
            std::make_shared<Rotation>(rotation),
            std::make_shared<Scale>(scale),
        });
        Renderer::draw<DrawMode::TRIANGLES>(*meshList[i]);
    }
}

void Model::applyTransformAndDraw(const Transformations &transformations) const {
    for (size_t i = 0; i < meshList.size(); i++) {
        meshList[i]->setColor(color);
        meshList[i]->applyTransformations("model", transformations);
        Renderer::draw<DrawMode::TRIANGLES>(*meshList[i]);
    }
}

const Dimensions &Model::getDimensions() const {
    return dimensions;
}

const glm::vec3 &Model::getPositions() const {
    return positions;
}

void Model::setColor(const Color &color) {
    this->color = color;
}