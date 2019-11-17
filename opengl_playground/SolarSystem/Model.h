#pragma once

#include <string>
#include <vector>
#include "Mesh.h"
#include "Shader.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <map>
using namespace std;
class Model {
public:
	Model(const string& path);
	void Draw(Shader& shader);

private:
	vector<Mesh> meshes;
	map<string, Texture> texture_loaded;
	string directory;
	void loadModel(const string& path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTexture** tex, aiTextureType type,
		string typeName);
	unsigned int loadEmbeddedTextures(aiTexture* texture);
};

unsigned int TextureFromFile(const char* path, const string& directory);
unsigned int generateTexture(unsigned char* data, int width, int height, GLenum format);