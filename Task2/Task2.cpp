#include<GL/glut.h>

// draw the cube
void drawCube() {
	glBegin(GL_QUADS);

	// front face
	glColor3f(1.0, 0.0, 0.0); //red
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);

	// back face
	glColor3f(0.0, 1.0, 0.0); //green
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, -0.5);

	// left face
	glColor3f(0.0, 0.0, 1.0); //blue
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, -0.5);

	// rigth face
	glColor3f(1, 1, 0); //yellow
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, 0.5, -0.5);


	// top face
	glColor3f(0, 1.0, 1.0); //cyan
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);


	// bottom face
	glColor3f(1, 0, 1); //magenta
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);

	glEnd();

}
/////////////////////////////////////////////////////////////////////////////////////

// First Transformation
//Translation by 6 units in the +ve x direction, 
// followed by reflection about the yz plane and then
//anticlockwise rotation by 90° around the z - axis.

void transformationSet1() {

	glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
	glScalef(-1.0f, 1.0f, 1.0f);
	glTranslatef(6.0f, 0.0f, 0.0f);

	drawCube();

}


////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Second Transformation
//Translation by 3 units in the +ve x direction and 3 units in -ve z direction, 
// followed by clockwise rotation by 180° about the y - axis.


void transformationSet2() {
	
	glRotatef(180.0f, 0.0f, 1.0f, 1.0f);
	glTranslatef(3.0f, 0.0f, -3.0f);
	drawCube();

}

///////////////////////////////////////////////////////////////////////////////////////////////////

//  Third Transformation
//Translation by 3 units in the +ve x direction and 3 units in -ve y direction, 
// followed by scaling around the center of the box by a factor of 3 in x and y directions.

void transformationSet3() {

	glScalef(3.0f, 3.0f, 1.0f);
	glTranslatef(3.0f, -3.0f, 0.0f);
	drawCube();

}


/// /////////////////////////////////////////////////////////////////////

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

	// original cube
	drawCube();

	// first transformation
	glPushMatrix();
	transformationSet1();
	glPopMatrix();

	// second transformation
	glPushMatrix();
	transformationSet2();
	glPopMatrix();

	// third transformation
	glPushMatrix();
	transformationSet3();
	glPopMatrix();

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