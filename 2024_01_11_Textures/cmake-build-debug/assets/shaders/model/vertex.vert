#version 330

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 texture;
layout(location = 2) in vec3 norm;

out vec4 vColor;
out vec2 texCoord;
out vec3 normal;
out vec3 fragPos;
out vec2 textCoord;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;
uniform vec4 meshColor;

void main() {
    gl_Position = projection * view * model * vec4(pos, 1.0);
    vColor = meshColor;
    texCoord = texture;
    // nrom is only direction so we move it to the model positon
    // mat3 --> ignore transforms (most transforms take into account last / bottom row / colums)
    // transponse + inverse --> fix non-uniform scale in which case normal may start to move
    normal = mat3(transpose(inverse(model))) * norm;
    fragPos = (model * vec4(pos, 1.0)).xyz;
}