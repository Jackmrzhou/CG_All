#pragma once

#include <glad\glad.h>
#include <iostream>
#include <string>
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
	
private:
	GLuint programID;
};