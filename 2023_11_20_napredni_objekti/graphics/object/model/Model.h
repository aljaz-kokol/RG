#ifndef INC_03_TEXTURES_MODEL_H
#define INC_03_TEXTURES_MODEL_H

#include <vector>
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "../texture-mesh/TextureMesh.h"
#include "../../texture/Texture.h"
#include "../transformation/translation/Translation.h"
#include "../transformation/scale/Scale.h"
#include "../transformation/rotation/Rotation.h"
#include "../../utils/Direction.h"

class Model {
private:
    std::vector<glm::vec3> meshCenters;
    const ShaderProgram& program;
    std::vector<std::shared_ptr<TextureMesh>> meshList;
    std::vector<std::shared_ptr<Transformation>> transformations;
    glm::vec3 positions;
    Dimensions dimensions;

    Translation translation;
    Scale scale;
    Rotation rotation;
    Color color;

    void loadNodes(aiNode* node, const aiScene* scene);
    void loadMesh(aiMesh* mesh, const aiScene* scene);
public:
    Model(const ShaderProgram& program);
    Model(const ShaderProgram &program, const Camera& camera);

    void load(std::string_view fileName);
    void draw() const;
    void applyTransformAndDraw(const Transformations &transformations) const;
    void draw(const Camera& camera) const;
    void setColor(const Color& color);

    void move(Direction direction, float value, GLfloat delta);
    [[nodiscard]] const Dimensions& getDimensions() const;
    [[nodiscard]] const glm::vec3& getPositions() const;
};

#endif