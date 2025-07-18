#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoord; // unused here
layout(location = 2) in vec3 aNormal;

uniform mat4 uModel;   // model matrix
uniform mat4 uView;    // view matrix
uniform mat4 uProj;    // projection matrix

out vec3 vNormal;

void main() {
    // Transform position
    gl_Position = uProj * uView * uModel * vec4(aPos, 1.0);
    // Transform normal into world (or view) space and pass along
    vNormal = mat3(transpose(inverse(uModel))) * aNormal;
}