#version 110
out vec2 TexCoord;
void main(){
	TexCoord = gl_MultiTexCoord0.xy;
	gl_Position = ftransform();
}