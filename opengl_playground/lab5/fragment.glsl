#version 330
out vec4 fragColor;
in vec2 TexCoord;

uniform sampler2D diffuse_tex1, diffuse_tex2;
uniform int mixTexture;
void main(){
	if (mixTexture == 1)
		fragColor = texture(diffuse_tex1, TexCoord)* texture(diffuse_tex2, TexCoord);
	else 
		fragColor = texture(diffuse_tex1, TexCoord);
}