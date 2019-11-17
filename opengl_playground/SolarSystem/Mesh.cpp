#include "Mesh.h"

Mesh::Mesh(vector<Vertex> v, vector<GLuint> i, vector<Texture> t)
{
	vertices = v;
	indices = i;
	textures = t;
	setupMesh();
}

void Mesh::Draw(Shader& shader)
{
	GLuint diffN = 1, SpecN = 1, normN = 1, heightN = 1;
	for (unsigned int i = 0; i < textures.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		string num, name = textures[i].type;
		if (name == "texture_diffuse")
			num = to_string(diffN++);
		else if (name == "texture_specular")
			num = to_string(SpecN++);
		else if (name == "texture_normal")
			num = to_string(normN++);
		else if (name == "texture_height")
			num = to_string(heightN++);
		else {
			cout << "UNKNOW TEXTURE TYPE" << endl;
		}
		shader.setInt(name + num, i);
		glBindTexture(GL_TEXTURE_2D, textures[i].ID);
	}

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glActiveTexture(GL_TEXTURE0);
}

void Mesh::setupMesh()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

	glBindVertexArray(0);
}
