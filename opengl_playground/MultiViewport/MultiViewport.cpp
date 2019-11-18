#include <glad/glad.h>
#include <glut.h>
#include <iostream>
using namespace std;
int windowWidth = 800, windowHeight = 800;

float dis, fov;
float subFov;
float cameraPos[3];
float PI() { return std::atan(1) * 4; }
float radians(float degree) {
	return degree * PI() / 180.f;
}
float degree(float rad) {
	return rad * 180.f / PI();
}
float k = windowWidth / windowHeight;

void init() {
	dis = 100.f;
	fov = 45.f;
	subFov = asin(1 / sqrt(4.f / pow(tan(radians(fov / 2)), 2) - 1.f / pow(k, 2)));
	cout << subFov << endl;
	subFov = degree(subFov)*2;
	cout << subFov << endl;
	cameraPos[0] = 0;
	cameraPos[1] = 0;
	cameraPos[2] = 4.f;
}

void reshape(int width, int height) {
	windowWidth = width;
	windowHeight = height;
	k = windowWidth / windowHeight;
	glutPostRedisplay();
}

void redraw() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 1.0f, 1.0f);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(subFov, k, 0.1f, dis);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, windowWidth / 2, windowHeight / 2);
	glLoadIdentity();
	gluLookAt(cameraPos[0], cameraPos[1], cameraPos[2], -dis / 2.0 * sin(radians(fov / 2)), -dis / 2.0 * sin(radians(fov / 2)), (double)-dis * cos(radians(fov / 2)) + cameraPos[2], 0.0, 1.0, 0.0);
	glutWireTeapot(1);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(subFov, k, 0.1f, dis);
	glMatrixMode(GL_MODELVIEW);
	glViewport(windowWidth / 2, 0, windowWidth / 2, windowWidth / 2);
	glLoadIdentity();
	gluLookAt(cameraPos[0], cameraPos[1], cameraPos[2], dis / 2.0 * sin(radians(fov / 2)), -dis / 2.0 * sin(radians(fov / 2)), (double)-dis * cos(radians(fov / 2)) + cameraPos[2], 0.0, 1.0, 0.0);
	glutWireTeapot(1);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(subFov, k, 0.1f, dis);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, windowHeight / 2, windowWidth / 2, windowHeight / 2);
	glLoadIdentity();
	gluLookAt(cameraPos[0], cameraPos[1], cameraPos[2], -dis / 2.0 * sin(radians(fov / 2)), dis / 2.0 * sin(radians(fov / 2)), (double)-dis * cos(radians(fov / 2)) + cameraPos[2], 0.0, 1.0, 0.0);
	glutWireTeapot(1);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(subFov, k, 0.1f, dis);
	glMatrixMode(GL_MODELVIEW);
	glViewport(windowWidth / 2, windowHeight / 2, windowWidth / 2, windowHeight / 2);
	glLoadIdentity();
	gluLookAt(cameraPos[0], cameraPos[1], cameraPos[2], dis / 2.0 * sin(radians(fov / 2)), dis / 2.0 * sin(radians(fov / 2)), (double)-dis * cos(radians(fov / 2)) + cameraPos[2], 0.0, 1.0, 0.0);
	glutWireTeapot(1);

	glutSwapBuffers();
}

void idle() {
	glutPostRedisplay();
}

void keyboardCallback(unsigned char key, int x, int y) {

}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(windowWidth, windowHeight);
	int windowHandle
		= glutCreateWindow("MultiVeiwport");

	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboardCallback);

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