#include <GL/glut.h>

// Draw the coordinate axes
void drawAxes() {
	glBegin(GL_LINES);

	// X axis - Red
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(-10.0, 0.0, 0.0);
	glVertex3f(10.0, 0.0, 0.0);

	// Y axis - Green
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, -10.0, 0.0);
	glVertex3f(0.0, 10.0, 0.0);

	// Z axis - Blue
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, -10.0);
	glVertex3f(0.0, 0.0, 10.0);

	glEnd();
}



// draw the cube
void drawCube() {
	glBegin(GL_QUADS);

	// front face
	glColor3f(1.0, 0.0, 0.0); // red
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);

	// back face
	glColor3f(0.0, 1.0, 0.0); // green
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, -0.5);

	// left face
	glColor3f(0.0, 0.0, 1.0); // blue
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, -0.5);

	// right face
	glColor3f(1, 1, 0); // yellow
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, 0.5, -0.5);

	// top face
	glColor3f(0, 1.0, 1.0); // cyan
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);

	// bottom face
	glColor3f(1, 0, 1); // magenta
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);

	glEnd();
}

//// Draw a small cube to represent the center point
//void drawCenterMarker(float x, float y, float z) {
//	glPushMatrix();
//	glTranslatef(x, y, z);
//	glScalef(0.1f, 0.1f, 0.1f);
//	drawCube();
//	glPopMatrix();
//}

void transformationSet1() {

	glPushMatrix();
	glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
	glScalef(-1.0f, 1.0f, 1.0f);
	glTranslatef(6.0f, 0.0f, 0.0f);
	drawCube();
	glPopMatrix();
}

void transformationSet2() {
	glPushMatrix();
	glRotatef(-180.0f, 0.0f, 1.0f, 0.0f);
	glTranslatef(3.0f, 0.0f, -3.0f);
	drawCube();
	glPopMatrix();
}

void transformationSet3() {
	glPushMatrix();
	glTranslatef(3.0f, -3.0f, 0.0f);
	glScalef(3.0f, 3.0f, 1.0f);
	drawCube();
	glPopMatrix();
}

void setup() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50.0f, 1.0f, 1.0f, 50.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(10.0, 15.0, 20.0,  // Camera position
		0.0, 0.0, 0.0,   // Look-at point
		0.0, 1.0, 0.0);  // Up direction

	// Draw coordinate axes
	drawAxes();

	// Original cube
	drawCube();

	// First transformation
	transformationSet1();

	// Second transformation
	transformationSet2();

	// Third transformation
	transformationSet3();

	glutSwapBuffers();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RED | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Cube Transformations");
	glEnable(GL_DEPTH_TEST);

	setup();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
