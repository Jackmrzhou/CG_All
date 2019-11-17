#version 330 core

in vec2 TexCoords;
in vec3 Normal, FragPos;
uniform sampler2D texture_diffuse1, texture_diffuse2;
uniform vec3 lightPos, lightColor;
out vec4 FragColor;

void main(){
	FragColor = texture(texture_diffuse1, TexCoords);
}