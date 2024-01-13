#version 330

out vec4 color;
in vec4 vColor;
in vec2 texCoord;
in vec3 normal;
in vec3 fragPos;

struct DirectionalLight {
    vec3 color;
    float ambientIntensity;

    vec3 position;
    float diffuseIntensity;
};

struct Material {
    float specularIntensity;
    float shininess;
};

uniform sampler2D textureData; // contected thgrouh the texture unit (GL_TEXTURE0, ...)
uniform DirectionalLight directionalLight; // Like a sun without a point of origin
uniform Material material;
uniform vec3 eyePosition;

void main() {
    vec4 ambientColor = vec4(directionalLight.color, 1.0) * directionalLight.ambientIntensity;
    vec3 norm = normalize(normal);
    vec3 posNorm = normalize(-directionalLight.position);
    // diffues factor ---> result of the angle under which the light is hitting the surface
    // max --> if diffuesFactor is bellow 0 (we are bellow the object) dont light up the object
    float diffuseFactor = max(dot(norm, posNorm), 0.0);
    vec4 diffuesColor = vec4(directionalLight.color *  directionalLight.diffuseIntensity * diffuseFactor, 1.0);
    vec4 specularColor = vec4(0, 0, 0, 0);

    if (diffuseFactor > 0.0) {
        vec3 fragToEye = normalize(eyePosition - posNorm);
        vec3 reflectDir = reflect(-directionalLight.position, norm);
        vec3 halfwayDir = normalize(posNorm + fragToEye);

        float specularFactor = pow(max(dot(norm, halfwayDir), 0.0), material.shininess);
        if (specularFactor > 0.0) {
            specularColor = vec4(directionalLight.color, 1.0) * material.specularIntensity * specularFactor;
        }
    }
    color = texture(textureData, texCoord) * (ambientColor + diffuesColor + specularColor) * vColor;
}