#version 330 core
layout (location = 0) in vec3 aPos;   // the position variable has attribute position 0
layout (location = 1) in vec2 aTexCoord; // texture coordinate
layout (location = 2) in vec3 aNormal;

out vec2 TexCoord; 
out vec3 Normal;
out vec3 FragPos;

uniform mat4 model, view, projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
	FragPos = vec3(model * vec4(aPos, 1.0));
	TexCoord = aTexCoord;
	Normal = mat3(transpose(inverse(model))) * aNormal;
}   