#include <glad/glad.h>
#include <glut.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "Model.h"
using namespace std;
glm::vec3 cameraPos(0.f, 0.f, 3.f), cameraFront(0.f, 0.f, -1.f), cameraUp(0.f, 1.f, 0.f);
constexpr int windowWidth = 1280, windowHeight = 1024;
Shader* myShader;
Model* myModel;
void init() {
	glEnable(GL_DEPTH_TEST);
	myShader = new Shader("shaders/vertex.glsl", "shaders/fragment.glsl");
	myModel = new Model("resource/nanosuit/nanosuit.obj");
}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glutPostRedisplay();
}

void redraw() {
	glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	myShader->use();
	glm::mat4 projection = glm::perspective(glm::radians(45.f), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);
	glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	myShader->setMat4("projection", projection);
	myShader->setMat4("view", view);

	// render the loaded model
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
	model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down
	myShader->setMat4("model", model);
	myModel->Draw(*myShader);

	glutSwapBuffers();
}

void idle() {
	glutPostRedisplay();
}
void keyboardCallback(unsigned char key, int x, int y) {
	static float speed = 0.05f;
	switch (key)
	{
	case 'w': {
		cameraPos.z -= speed;
	} break;
	case 's': {
		cameraPos.z += speed;
	} break;
	case 'a': {
		cameraPos.x -= speed;
	} break;
	case 'd': {
		cameraPos.x += speed;
	} break;
	default:
		break;
	}
}

void motionCallback(int x, int y) {
	static int lastX = -1, lastY = -1;
	if (lastX == -1 && lastY == -1) {
		lastX = x;
		lastY = y;
	}
	float xOff = x - lastX, yOff = y - lastY, sensitivity = 0.1f;
	lastX = x;
	lastY = y;
	xOff *= sensitivity;
	yOff *= sensitivity;

	static float yaw = -90.f, pitch = 0;
	yaw += xOff;
	pitch -= yOff;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);
}
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(windowWidth, windowHeight);
	int windowHandle
		= glutCreateWindow("Simple GLUT App");

	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboardCallback);
	glutPassiveMotionFunc(motionCallback);

	if (!gladLoadGL()) {
		cout << "something went wrong!" << endl;
		exit(-1);
	}
	const GLubyte* version = glGetString(GL_VERSION);
	cout << version << endl;
	init();
	glutMainLoop();

	return 0;
}