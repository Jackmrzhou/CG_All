#include <glad/glad.h>
#include <glut.h>
#include "stb_image.h"
#include <iostream>
#include <vector>
#include <string>
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace std;
unsigned int generateTexture(unsigned char* data, int width, int height, GLenum format);
int TextureFromFile(const string& filename)
{
	int textureID = -1;
	int width, height, nrComponents;
	unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;
		textureID = generateTexture(data, width, height, format);
		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << filename << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}

unsigned int generateTexture(unsigned char* data, int width, int height, GLenum format) {
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	return textureID;
}

class Cube {
public:
	Cube() {
		float vertices[] = {
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  0.0f, -1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, -1.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  0.0f, -1.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  0.0f, -1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, -1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  0.0f, -1.0f,

			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  0.0f,  1.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  0.0f,  1.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f,  1.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f,  1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f,  1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  0.0f,  1.0f,

			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1.0f,  0.0f,  0.0f,
			-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, -1.0f,  0.0f,  0.0f,
			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1.0f,  0.0f,  0.0f,

			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,  0.0f,  0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,  0.0f,  0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, -1.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f, -1.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, -1.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, -1.0f,  0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, -1.0f,  0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, -1.0f,  0.0f,

			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f,  0.0f,	
		};
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(5 * sizeof(GLfloat)));
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		//unbind 
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void draw() {
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
	}
private:
	GLuint VAO, VBO;
};

class Application {
public:
	void Init(int arg, char* argv[]){
		glutInit(&arg, argv);
		
		glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
		glutInitWindowSize(width, height);
		int windowHandle = glutCreateWindow("Simple GLUT App");
		glutDisplayFunc(redraw);
		glutReshapeFunc(reshape);
		glutKeyboardFunc(keyCallback);
		glutIdleFunc(idle);

		if (!gladLoadGL()) {
			cout << "something went wrong!" << endl;
			exit(-1);
		}
		const string imgs[] = { "42_mirror.png", "Crack.bmp", "Spot.bmp" };
		for (auto& img : imgs) {
			int id = TextureFromFile("resources/" + img);
			if (id != -1) {
				textureIDs.push_back(id);
			}
		}
		shader = new Shader("vertex.glsl", "fragment.glsl");
		teapotShader = new Shader("teapotVertex.glsl", "fragment.glsl");
		cube = new Cube();
		glEnable(GL_DEPTH_TEST);
	}

	void run() {
		glutMainLoop();
	}
private:
	static vector<GLuint> textureIDs;
	static Shader* shader, *teapotShader;
	static Cube* cube;
	static int width, height;
	static bool mixTexture;

	static void redraw() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shader->use();
		// cube textures
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, textureIDs[1]);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, textureIDs[2]);
		shader->setInt("diffuse_tex1", 1);
		shader->setInt("diffuse_tex2", 2);
		shader->setInt("mixTexture", mixTexture ? 1 : 0);
		// cube position
		glm::mat4 projection(1.f), view(1.f), model(1.f);
		projection = glm::perspective(45.f, (float)width / (float)height, 0.1f, 100.f);
		view = glm::lookAt(glm::vec3{ 0.f, 0.f, 10.f }, { 0.f,0.f,0.f }, { 0.f, 1.f,0.f });
		model = glm::translate(model, glm::vec3{ -1.5f, -3.f, 1.5f });
		model = glm::scale(model, glm::vec3{ 1.f, 3.f,1.f });
		shader->setMat4("projection", projection);
		shader->setMat4("view", view);
		shader->setMat4("model", model);
		cube->draw();

		model = glm::translate(glm::mat4(1.f), glm::vec3{1.5f, -3.f, 1.5f});
		model = glm::scale(model, glm::vec3{ 1.f, 3.f, 1.f });
		shader->setMat4("model", model);
		cube->draw();

		model = glm::translate(glm::mat4(1.f), glm::vec3{ 1.5f, -3.f, -1.5f });
		model = glm::scale(model, glm::vec3{ 1.f,3.f,1.f });
		shader->setMat4("model", model);
		cube->draw();

		model = glm::translate(glm::mat4(1.f), glm::vec3{ -1.5f, -3.f, -1.5f });
		model = glm::scale(model, glm::vec3{ 1.f, 3.f, 1.f });
		shader->setMat4("model", model);
		cube->draw();
		
		model = glm::translate(glm::mat4(1.f), glm::vec3{0.f, -1.5f, 0.f});
		model = glm::scale(model, glm::vec3{ 5.f, 0.5f, 5.f });
		shader->setMat4("model", model);
		cube->draw();

		teapotShader->use();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureIDs[0]);
		teapotShader->setInt("diffuse_tex1", 0);
		teapotShader->setInt("mixTexture", 0);
		glLoadIdentity();
		gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);
		glutSolidTeapot(1);
		glutSwapBuffers();
	}

	static void reshape(int w, int h) {
		width = w;
		height = h;
		glViewport(0, 0, w, h);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		gluPerspective(45.0, (GLdouble)w / (GLdouble)h, 0.1f, 100.f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}

	static void keyCallback(unsigned char key, int x, int y) {
		if (key == 'm') {
			mixTexture = !mixTexture;
		}
	}

	static void idle() {
		glutPostRedisplay();
	}
};

vector<GLuint> Application::textureIDs = vector<GLuint>();
Shader* Application::shader = nullptr;
Shader* Application::teapotShader = nullptr;
Cube* Application::cube = nullptr;
int Application::width = 480, Application::height = 480;
bool Application::mixTexture = false;

int main(int arg, char *argv[]) {
	Application app;
	app.Init(arg, argv);
	app.run();
}