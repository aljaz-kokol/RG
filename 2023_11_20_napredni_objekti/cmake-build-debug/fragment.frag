#version 330

out vec4 color;
in vec4 vColor;
in vec2 texCoord;
in vec3 normal;
in vec3 fragPos;

struct DirectionalLight {
    vec3 color;
    float ambientIntensity;

    vec3 direction;
    float diffuseIntensity;
};

struct Material {
    float specularIntensity;
    float shininess;
};

uniform DirectionalLight directionalLight; // Like a sun without a point of origin
uniform Material material;
uniform vec3 eyePosition;

void main() {
    vec4 ambientColor = vec4(directionalLight.color, 1.0) * directionalLight.ambientIntensity;
    // diffues factor ---> result of the angle under which the light is hitting the surface
    // max --> if diffuesFactor is bellow 0 (we are bellow the object) dont light up the object
    float diffuesFactor = max(dot(normalize(normal), normalize(directionalLight.direction)), 0.0);
    vec4 diffuesColor = vec4(directionalLight.color *  directionalLight.diffuseIntensity * diffuesFactor, 1.0);

    vec4 specularColor = vec4(0, 0, 0, 0);

    if (diffuesFactor > 0.0f) { // specular color must be accompanied by diffuseColor
        vec3 fragToEye = normalize(eyePosition - fragPos); // normalize --> we only want to know the direction
        vec3 reflectedVertex = normalize(reflect(directionalLight.direction, normalize(normal))); // reflect (what we want to reflect, around what we want to reflect)
        float specularFactor = dot(fragToEye, reflectedVertex);
        if (specularFactor > 0) {
            specularFactor = pow(specularFactor, material.shininess);
            specularColor = vec4(directionalLight.color, 1.0) * material.specularIntensity * specularFactor;
        }
    }

    color = (ambientColor + diffuesColor + specularColor) * vColor;
}