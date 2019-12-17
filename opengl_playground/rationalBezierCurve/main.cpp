#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <glut.h>

using namespace std;

// Begin globals.
static int numVal = 1; // Index of selected control point.
static char theStringBuffer[10]; // String buffer.
static long font = (long)GLUT_BITMAP_8_BY_13; // Font selection.

// Control points on the z=1 plane.
static float controlPoints[4][3] =
{
	{-1.0, 0.0, 1.0}, {-1.0, 2.0, 1.0}, {1.0, 2.0, 1.0}, {1.0, 0.0, 1.0}
};

// Weights
static float weights[4] = { 1.f, 1.f/3, 1.f/3, 1.f };

// Control points in 3D space.
static float controlPointsLifted[4][3];

// Control points in homogeneous co-ordinates.
static float controlPointsHomogeneous[4][4];
// End globals.

// Routine to draw a bitmap character string.
void writeBitmapString(void* font, char* string)
{
	char* c;

	for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}

// Routine to convert floating point to char string.
void floatToString(char* destStr, int precision, float val)
{
	sprintf(destStr, "%f", val);
	destStr[precision] = '\0';
}

// Write data.
void writeData(void)
{
	glColor3f(0.0, 0.0, 0.0);

	floatToString(theStringBuffer, 4, weights[0]);
	glRasterPos3f(-4.0, 4.0, 0.0);
	writeBitmapString((void*)font, const_cast<char*>("weights[0]: "));
	writeBitmapString((void*)font, theStringBuffer);

	floatToString(theStringBuffer, 4, weights[1]);
	glRasterPos3f(-4, 3.5, 0.0);
	writeBitmapString((void*)font, const_cast<char*>("weights[1]: "));
	writeBitmapString((void*)font, theStringBuffer);

	floatToString(theStringBuffer, 4, weights[2]);
	glRasterPos3f(-4, 3, 0.0);
	writeBitmapString((void*)font, const_cast<char*>("weights[2]: "));
	writeBitmapString((void*)font, theStringBuffer);

	floatToString(theStringBuffer, 4, weights[3]);
	glRasterPos3f(-4, 2.5, 0.0);
	writeBitmapString((void*)font, const_cast<char*>("weights[3]: "));
	writeBitmapString((void*)font, theStringBuffer);
}

// Routine to lift 3D control points to projective 3-space by specfying homogeneous co-ordinates.
void computeControlPointsHomogeneous(void)
{
	int i, j;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 3; j++)
		{
			controlPointsHomogeneous[i][j] = controlPoints[i][j] * weights[i];
		}
		controlPointsHomogeneous[i][3] = weights[i];
	}
}

// Routine to restore weights to original values.
void restoreWeights(void)
{
	int i;
	for (i = 0; i < 4; i++)
	{
		weights[i] = 1.5;
	}
	computeControlPointsHomogeneous();
}

// Initialization routine.
void setup(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	computeControlPointsHomogeneous();
}

// Drawing routine.
void drawScene(void)
{
	int i;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw the rational Bezier curve on the plane in red.
	glColor3f(1.0, 0.0, 0.0);
	glMap1f(GL_MAP1_VERTEX_4, 0.0, 1.0, 4, 4, controlPointsHomogeneous[0]);
	glEnable(GL_MAP1_VERTEX_4);
	glMapGrid1f(100, 0.0, 1.0);
	glEvalMesh1(GL_LINE, 0, 100);
	glDisable(GL_MAP1_VERTEX_4);

	// Draw the symetric part
	for (int i = 0; i < 4; i++) {
		controlPointsHomogeneous[i][1] = -controlPointsHomogeneous[i][1];
	}
	glColor3f(0.0, 1.0, 0.0);
	glMap1f(GL_MAP1_VERTEX_4, 0.0, 1.0, 4, 4, controlPointsHomogeneous[0]);
	glEnable(GL_MAP1_VERTEX_4);
	glMapGrid1f(100, 0.0, 1.0);
	glEvalMesh1(GL_LINE, 0, 100);
	glDisable(GL_MAP1_VERTEX_4);
	for (int i = 0; i < 4; i++) {
		controlPointsHomogeneous[i][1] = -controlPointsHomogeneous[i][1];
	}
	// Draw the control points on the plane as red dots.
	glPointSize(5.0);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POINTS);
	for (i = 0; i < 4; i++)
		glVertex3fv(controlPoints[i]);
	glEnd();

	writeData();

	glutSwapBuffers();
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-5, 5, -5, 5, 5, -5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// Main routine.
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("circle");
	setup();
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutMainLoop();

	return 0;
}