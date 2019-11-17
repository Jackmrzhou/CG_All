#pragma once

#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <glad/glad.h>
#include "Shader.h"
using namespace std;

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct Texture
{
	unsigned int ID;
	string type;
	string path;
};

class Mesh {
public:
	vector<Vertex> vertices;
	vector<GLuint> indices;
	vector<Texture> textures;
	Mesh(vector<Vertex> v, vector<GLuint> i, vector<Texture> t);
	void Draw(Shader& shader);
private:
	GLuint VAO, VBO, EBO;
	void setupMesh();
};