#include <glad/glad.h>
#include <glut.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "Model.h"
using namespace std;
glm::vec3 cameraPos(0.f, 0.f, 150.f), cameraFront(0.f, 0.f, -1.f), cameraUp(0.f, 1.f, 0.f);
constexpr int windowWidth = 1280, windowHeight = 1024;
Shader* myShader, *lampShader;
Model* earth, *sun, *moon;
float fov=45.f;
glm::vec3 earthPos(-60.f, 0.f, 0.f), moonPos(-50.f, 0.f, 0.f), sunPos(0.f, 0.f, 0.f);
void init() {
	glEnable(GL_DEPTH_TEST);
	myShader = new Shader("shaders/vertex.glsl", "shaders/fragment.glsl");
	lampShader = new Shader("shaders/vertex.glsl", "shaders/lampFragment.glsl");
	earth = new Model("resource/earth/Earth.glb");
	sun = new Model("resource/sun/The Sun.glb");
	moon = new Model("resource/moon/Moon.glb");
}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glutPostRedisplay();
}

void redraw() {
	static float time = 0.f;
	time += 0.2f;

	glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	myShader->use();
	myShader->setVec3("lightColor", 1.f, 1.f, 1.f);
	myShader->setVec3("lightPos",sunPos);
	glm::mat4 projection = glm::perspective(glm::radians(fov), (float)windowWidth / (float)windowHeight, 0.1f, 300.0f);
	glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	myShader->setMat4("projection", projection);
	myShader->setMat4("view", view);
	lampShader->use();
	lampShader->setMat4("projection", projection);
	lampShader->setMat4("view", view);

	//lampShader->use();
	glm::mat4 model = glm::mat4(1.0f);
	// sun
	model = glm::mat4(1.f);
	model = glm::translate(model, sunPos);
	model = glm::rotate(model, glm::radians(time), glm::vec3(0.f, 1.f, 0.f));
	model = glm::scale(model, glm::vec3(2.f, 2.f, 2.f));
	lampShader->setMat4("model", model);
	sun->Draw(*lampShader);

	myShader->use();
	//earth
	model = glm::mat4(1.f);
	model = glm::rotate(model, glm::radians(time), glm::vec3(0.f, 1.f, 0.f));
	model = glm::translate(model, earthPos);
	model = glm::rotate(model, glm::radians(time*4), glm::vec3(0.f, 1.f, 0.f));
	model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));	// it's a bit too big for our scene, so scale it down
	myShader->setMat4("model", model);
	earth->Draw(*myShader);

	// moon
	model = glm::mat4(1.f);
	model = glm::rotate(model, glm::radians(time), glm::vec3(0.f, 1.f, 0.f));
	model = glm::translate(model, earthPos);
	model = glm::rotate(model, glm::radians(time), glm::vec3(0.f, 1.f, 0.f));
	model = glm::translate(model, glm::vec3(-10.f, 0.f, 0.f));
	model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
	myShader->setMat4("model", model);
	moon->Draw(*myShader);
	glutSwapBuffers();
}

void idle() {
	glutPostRedisplay();
}
void keyboardCallback(unsigned char key, int x, int y) {
	static float speed = 5.f;
	switch (key)
	{
	case 'w': {
		cameraPos += speed * cameraFront;
	} break;
	case 's': {
		cameraPos -= speed * cameraFront;
	} break;
	case 'a': {
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * speed;
	} break;
	case 'd': {
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * speed;
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

void mouseCallback(int button, int state, int x, int y) {
	switch (button)
	{
	case 3:
		cout << "up" << endl;
		fov -= 1.f;
		if (fov < 1.f)
			fov = 1.f;
		break;
	case 4:
		fov += 1.f;
		if (fov > 45.f)
			fov = 45.f;
		break;
	default:
		break;
	}
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
	glutMouseFunc(mouseCallback);

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