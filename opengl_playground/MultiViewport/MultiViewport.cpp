#include <glad/glad.h>
#include <glut.h>
#include <iostream>
using namespace std;
int windowWidth = 800, windowHeight = 800;

float near, far, fov;
float cameraPos[3];
float k = windowWidth / windowHeight;
bool Perspective = false;

void init() {
	far = 100.f;
	fov = 45.f;
	near = 0.1f;
	cameraPos[0] = 0;
	cameraPos[1] = 0;
	cameraPos[2] = 4.f;
	glEnable(GL_DEPTH_TEST);
}

void reshape(int width, int height) {
	windowWidth = width;
	windowHeight = height;
	k = windowWidth / windowHeight;
	glutPostRedisplay();
}

void drawViewportBorder() {
	unsigned char* data = new unsigned char[3 * windowWidth * windowHeight];
	glReadPixels(0, 0, windowWidth, windowHeight, GL_RGB, GL_UNSIGNED_BYTE, data);
	int col = windowWidth / 2;
	for (int i = 0; i < windowHeight; i++) {
		data[i * windowWidth * 3 + col * 3] = 255;
	}
	int row = windowHeight / 2;
	for (int j = 0; j < windowWidth; j++) {
		data[col * windowWidth * 3 + j * 3] = 255;
	}
	glDrawPixels(windowWidth, windowHeight, GL_RGB, GL_UNSIGNED_BYTE, data);
	delete[] data;
}

void redraw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0f, 1.0f, 1.0f);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// width/2 * 2.0/width = 1.0
	glTranslatef(1.f, -1.f, 0.f);
	if (Perspective)
		gluPerspective(fov, k, near, far);
	else
		glOrtho(-2, 2, -2, 2, -10, 100);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, windowHeight / 2, windowWidth / 2, windowHeight / 2);
	glLoadIdentity();
	gluLookAt(
		cameraPos[0],
		cameraPos[1],
		cameraPos[2],
		0,
		0,
		0,
		0.0, 1.0, 0.0
	);
	glutWireTeapot(1);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glTranslatef(-1.f, -1.f, 0.f);
	if (Perspective)
		gluPerspective(fov, k, near, far);
	else
		glOrtho(-2, 2, -2, 2, -10, 100);
	glMatrixMode(GL_MODELVIEW);
	glViewport(windowWidth / 2, windowHeight / 2, windowWidth / 2, windowHeight / 2);
	glLoadIdentity();
	gluLookAt(
		cameraPos[0] ,
		cameraPos[1] ,
		cameraPos[2],
		0,
		0,
		0,
		0.0, 1.0, 0.0
	);
	glutWireTeapot(1);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glTranslatef(1.f, 1.f, 0.f);
	if (Perspective)
		gluPerspective(fov, k, near, far);
	else
		glOrtho(-2, 2, -2, 2, -10, 100);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, windowWidth / 2, windowHeight / 2);
	glLoadIdentity();
	gluLookAt(
		cameraPos[0],
		cameraPos[1],
		cameraPos[2],
		0,
		0,
		0,
		0.0, 1.0, 0.0
	);
	glutWireTeapot(1);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glTranslatef(-1.f, 1.f, 0.f);
	if (Perspective)
		gluPerspective(fov, k, near, far);
	else
		glOrtho(-2, 2, -2, 2, -10, 100);
	glMatrixMode(GL_MODELVIEW);
	glViewport(windowWidth / 2, 0, windowWidth / 2, windowHeight / 2);
	glLoadIdentity();
	gluLookAt(
		cameraPos[0],
		cameraPos[1],
		cameraPos[2],
		0,
		0,
		0,
		0.0, 1.0, 0.0
	);
	glutWireTeapot(1);
	
	drawViewportBorder();
	glutSwapBuffers();
}

void idle() {
	glutPostRedisplay();
}

void keyCallback(unsigned char key, int x, int y) {
	if (key == 'p') {
		Perspective = !Perspective;
	}
}

void specialKeyCallback(int key, int x, int y) {
	switch (key)
	{
	case GLUT_KEY_UP:
		cameraPos[1]++;
		break;
	case GLUT_KEY_DOWN:
		cameraPos[1]--;
		break;
	case GLUT_KEY_LEFT:
		cameraPos[0]--;
		break;
	case GLUT_KEY_RIGHT:
		cameraPos[0]++;
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
		= glutCreateWindow("MultiVeiwport");

	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	glutSpecialFunc(specialKeyCallback);
	glutKeyboardFunc(keyCallback);

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