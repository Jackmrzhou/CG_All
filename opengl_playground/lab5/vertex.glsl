#version 330
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;
layout (location = 2) in vec3 aNormal;

uniform mat4 projection, view, model;
out vec2 TexCoord;
void main() {
	gl_Position = projection * view * model * vec4(aPos, 1.0);
	TexCoord = aTexCoords;
}