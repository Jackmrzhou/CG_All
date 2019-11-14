#version 330 core
out vec4 FragColor;  
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform vec3 lightPos, lightColor, viewPos;
uniform sampler2D texture1, texture2;

void main()
{
    vec4 objColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
	// ambient color
	vec3 ambient = lightColor * objColor.rgb * 0.2f;
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0);
	// diffuse color
	vec3 diffuse = diff * lightColor;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64);
	// specular color
	vec3 specular = spec * lightColor;
	vec3 result = objColor.rgb * (diffuse + ambient + specular);
	FragColor = vec4(result, 1.0);
}