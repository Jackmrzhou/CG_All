#include "glut.h"
#include <iostream>
using namespace std;

float fTranslate;
float fRotate;
float fScale = 1.0f;								// set inital scale value to 1.0f

void Draw_Triangle()									// This function draws a triangle with RGB colors
{
	glBegin(GL_TRIANGLES);
	// ���ö�����ɫ
	glColor3f(1.0f, 0.0f, 0.0f);
	// ���ö�������
	glVertex3f(-1.0f, 1.0f, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f, 1.0f, 0.0f);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);

	glEnd();
}

void reshape(int width, int height)
{
	if (height == 0)										// Prevent A Divide By Zero By
	{
		height = 1;										// Making Height Equal One
	}

	glViewport(0, 0, width, height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

														// Calculate The Aspect Ratio Of The Window
														// Perspective view
														//gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
														// Ortho view
	glOrtho(-4, 4, -4, 4, 0, 100);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}

void idle()
{
	glutPostRedisplay();
}

void draw_sep() {
	glPushMatrix();
	glScalef(.25f, 1.f, 1.f);
	Draw_Triangle();
	glPopMatrix();
}

void draw_und() {
	glPushMatrix();
	glScalef(1.f, .25f, 1.f);
	Draw_Triangle();
	glPopMatrix();
}

void draw_four() {
	// |_|
	//   |
	glPushMatrix();
	draw_sep();
	glTranslatef(0.75f, -1.25f, 0.f);
	draw_und();
	glTranslatef(0.75f, 1.25f, 0.f);
	draw_sep();
	glTranslatef(0.f, -2.f, 0.f);
	draw_sep();
	glPopMatrix();
}

void draw_two() {
	// _
	// _|
	//|_
	glPushMatrix();
	draw_und();
	glTranslatef(0.75f, -.75f, 0.f);
	draw_sep();
	glTranslatef(-0.75f, -.75f, 0.f);
	draw_und();
	glTranslatef(-0.75f, -.75f, 0.f);
	draw_sep();
	glTranslatef(0.75f, -0.75f, 0.f);
	draw_und();
	glPopMatrix();
}

void redraw()
{
	// �����ʹ���߿�ģʽ
	//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();									// ���ñ任���󣨻ص���������ϵ��

	glPushMatrix(); // ����һ���µ�����ϵ
	glTranslatef(-3.0f, 0.f, 0.f);				// ����ƽ��
												//Draw_Triangle();
	draw_four();
	glPopMatrix(); // �ص�ǰһ������ϵ

	glPushMatrix();
	glTranslatef(-0.5f, 0.f, 0.f);
	draw_four();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2.75f, 0.75f, 0.f);
	draw_two();
	glPopMatrix();

	glutSwapBuffers();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(640, 480);
	int windowHandle
		= glutCreateWindow("Simple GLUT App");

	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);

	const GLubyte* version = glGetString(GL_VERSION);
	cout << version << endl;

	glutMainLoop();

	return 0;
}


