#pragma once

#include <glad\glad.h>
#include <iostream>
#include <string>
#include <glm/glm.hpp>
using namespace std;

class Shader
{
public:
	Shader(const string& vertexPath, const string& fragmentPath);
	~Shader();
	GLuint GetID();
	void use();
	void setInt(const string& name, int val);
	void setFloat(const string& name, int val);
	void setMat4(const string& name, const glm::mat4& val);
	
private:
	GLuint programID;
};