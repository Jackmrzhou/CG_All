#include "glut.h"

float fTranslate;
float fRotate;
float fScale = 1.0f;								// set inital scale value to 1.0f

void Draw_Triangle()									// This function draws a triangle with RGB colors
{
	glBegin(GL_TRIANGLES);
	// 设置顶点颜色
	glColor3f(1.0f, 0.0f, 0.0f);
	// 设置顶点坐标
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
	//glOrtho(-4, 4, -4, 4, 0, 100);
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
	glTranslatef(0, 0, -10);

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
	glutWireCube(2.0);
	glPopMatrix();
}

void draw_und() {
	glPushMatrix();
	glScalef(1.f, .25f, 1.f);
	glutWireCube(2.0);
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
	// 如果想使用线框模式
	//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();									// 重置变换矩阵（回到世界坐标系）

	glPushMatrix(); // 设置一个新的坐标系
	glTranslatef(-3.0f, 0.f, 0.f);				// 向左平移
	//Draw_Triangle();
	draw_four();
	glPopMatrix(); // 回到前一个坐标系

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

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(640, 480);
	int windowHandle
		= glutCreateWindow("Simple GLUT App");

	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);

	glutMainLoop();

	return 0;
}


