#version 330 core

in vec2 TexCoords;
in vec3 Normal, FragPos;
uniform sampler2D texture_diffuse1, texture_diffuse2;
uniform vec3 lightPos, lightColor;
out vec4 FragColor;

void main(){
	vec4 objColor = texture(texture_diffuse2, TexCoords);
	vec3 ambient = lightColor * objColor.rgb * 0.01f;
	vec3 norm = normalize(Normal);
	vec3 lightDir = lightPos - FragPos;
	lightDir.y = 0.f;
	lightDir = normalize(lightDir);
	float diff = max(dot(norm, lightDir), 0);
	// diffuse color
	vec3 diffuse = diff * lightColor;
	vec3 result = objColor.rgb * (diffuse + ambient);
	FragColor = vec4(result, 1.0);
}