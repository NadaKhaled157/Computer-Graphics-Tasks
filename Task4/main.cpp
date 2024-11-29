///////////////////////////////////////////////////////////////////////////////////
// This program draws a conical spacecraft that can travel and an array of fixed spherical asteroids.
// The view in the left viewport is from a fixed camera; the view in the right viewport is from the spacecraft.
// There is approximate collision detection.
// 
// User-defined constants: 
// ROW is the number of rows of asteroids.
// COLUMN is the number of columns of asteroids.
// FILL_PROBABILITY is the percentage probability that a particular row-column slot
// will be filled with an asteroid.
//
// Interaction:
// Press the left/right arrow keys to turn the craft.
// Press the up/down arrow keys to move the craft.
//
// cr. code: Sumanta Guha.
///////////////////////////////////////////////////////////////////////////////////


// This code simply implements simplified collision detection with a group of objects.
// You can refer to section 4.6.4 in reference: Sumanta Guha - Computer Graphics through OpenGL


#define _USE_MATH_DEFINES

#include <cstdlib>
#include <cmath>
#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h> 

#define ROWS 8  // Number of rows of asteroids.
#define COLUMNS 6 // Number of columns of asteroids.
#define FILL_PROBABILITY 100 // Percentage probability that a particular row-column slot will be 
							 // filled with an asteroid. It should be an integer between 0 and 100.

// Globals.
static long font = (long)GLUT_BITMAP_8_BY_13; // Font selection.
static int width, height; // Size of the OpenGL window.
static float angle = 0.0; // Angle of the spacecraft.
static float xVal = 0, zVal = 0; // Co-ordinates of the spacecraft.
static int isCollision = 0; // Is there collision between the spacecraft and an asteroid?
static unsigned int spacecraft; // Display lists base index.
static int frameCount = 0; // Number of frames

// Routine to draw a bitmap character string.
void writeBitmapString(void* font, const char* string)
{
	const char* c;

	for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}

// Asteroid class.
class Cube
{
public:
	Cube();
	Cube(float x, float y, float z, float size, unsigned char colorR,
		unsigned char colorG, unsigned char colorB);
	float getCenterX() { return centerX; }
	float getCenterY() { return centerY; }
	float getCenterZ() { return centerZ; }
	float getSize() { return size; }
	void draw();

private:
	float centerX, centerY, centerZ, size;
	unsigned char color[3];
};

// Cube default constructor.
Cube::Cube()
{
	centerX = 0.0;
	centerY = 0.0;
	centerZ = 0.0;
	size = 0.0; 
	color[0] = 0;
	color[1] = 0;
	color[2] = 0;
}

// Cube constructor.
Cube::Cube(float x, float y, float z, float s, unsigned char colorR,
	unsigned char colorG, unsigned char colorB)
{
	centerX = x;
	centerY = y;
	centerZ = z;
	size = s;
	color[0] = colorR;
	color[1] = colorG;
	color[2] = colorB;
}

// Function to draw Cube.
void Cube::draw()
{
	if (size > 0.0) // If Cube exists.
	{
		glPushMatrix();
		glTranslatef(centerX, centerY, centerZ);
		glColor3ubv(color);
		glutSolidCube(size);
		glPopMatrix();
	}
}

Cube arrayCubes[ROWS][COLUMNS]; // Global array of Cubes.

// Routine to count the number of frames drawn every second.
void frameCounter(int value)
{
	if (value != 0) // No output the first time frameCounter() is called (from main()).
		std::cout << "FPS = " << frameCount << std::endl;
	frameCount = 0;
	glutTimerFunc(1000, frameCounter, 1);
}

// Initialization routine.
void setup(void)
{
	int i, j;

	spacecraft = glGenLists(1);
	glNewList(spacecraft, GL_COMPILE);

	glColor3f(1.0, 1.0, 1.0); //car color
	//main car body
	glPushMatrix();
	glRotatef(180.0, 0.0, 1.0, 0.0); // To make the spacecraft point down the $z$-axis initially.
	glutSolidCube(5.0);
	glPopMatrix();

	//front of car
	glPushMatrix();
	glTranslatef(0.0, 0.0, -3.0);
	glutSolidCube(4.0);
	glPopMatrix();

	//back of car
	glPushMatrix();
	glTranslatef(0.0, 0.0, 3.0);
	glutSolidCube(4.0);
	glPopMatrix();

	glColor3f(0.5, 0.5, 0.5);

	// 2 wheels on the right
	glPushMatrix(); //front wjeel
	glTranslatef(2.0, -3.0, 2.0);
	glutSolidSphere(1.0, 10.0, 10.0);
	glPopMatrix();

	glPushMatrix(); //back wheel
	glTranslatef(2.0, -3.0, -3.0);
	glutSolidSphere(1.0, 10.0, 10.0);
	glPopMatrix();

	// 2 wheels on the left
	glPushMatrix(); //front wheel
	glTranslatef(-2.0, -3.0, 2.0);
	glutSolidSphere(1.0, 10.0, 10.0);
	glPopMatrix();

	glPushMatrix(); //back wheel
	glTranslatef(-2.0, -3.0, -3.0);
	glutSolidSphere(1.0, 10.0, 10.0);
	glPopMatrix();

	glEndList();

	// Initialize global arrayCubes.
	for (j = 0; j < COLUMNS; j++)
		for (i = 0; i < ROWS; i++)
			if (rand() % 100 < FILL_PROBABILITY)
				// If rand()%100 >= FILL_PROBABILITY the default constructor Cube remains in the slot 
				// which indicates that there is no cube there because the default's size is 0.
			{
				// Position the cubes depending on if there is an even or odd number of columns
				// so that the spacecraft faces the middle of the cube field.
				if (COLUMNS % 2) // Odd number of columns.
					arrayCubes[i][j] = Cube(30.0 * (-COLUMNS / 2 + j), 0.0, -40.0 - 30.0 * i, 3.0,
						rand() % 256, rand() % 256, rand() % 256);
				else // Even number of columns.
					arrayCubes[i][j] = Cube(15 + 30.0 * (-COLUMNS / 2 + j), 0.0, -40.0 - 30.0 * i, 3.0,
						rand() % 256, rand() % 256, rand() % 256);
			}

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glutTimerFunc(0, frameCounter, 0); // Initial call of frameCounter().
}

// Function to check if two spheres centered at (x1,y1,z1) and (x2,y2,z2) with
// radius r1 and r2 intersect.
int checkSpheresIntersection(float x1, float y1, float z1, float r1,
	float x2, float y2, float z2, float r2)
{
	return ((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) + (z1 - z2) * (z1 - z2) <= (r1 + r2) * (r1 + r2));
}

// Function to check if the spacecraft collides with an cube when the center of the base
// of the craft is at (x, 0, z) and it is aligned at an angle a to to the -z direction.
// Collision detection is approximate as instead of the spacecraft we use a bounding sphere.
int asteroidCraftCollision(float x, float z, float a)
{
	int i, j;

	// Check for collision with each cube.
	for (j = 0; j < COLUMNS; j++)
		for (i = 0; i < ROWS; i++)
			if (arrayCubes[i][j].getSize() > 0) // If cube exists.
				if (checkSpheresIntersection(x - 5 * sin((M_PI / 180.0) * a), 0.0,
					z - 5 * cos((M_PI / 180.0) * a), 7.072,
					arrayCubes[i][j].getCenterX(), arrayCubes[i][j].getCenterY(),
					arrayCubes[i][j].getCenterZ(), arrayCubes[i][j].getSize()))
					return 1;
	return 0;
}

// Drawing routine.
void drawScene(void)
{
	frameCount++; // Increment number of frames every redraw.

	int i, j;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Begin left viewport.
	glViewport(0, 0, width / 2.0, height);
	glLoadIdentity();

	// Write text in isolated (i.e., before gluLookAt) translate block.
	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
	glRasterPos3f(-28.0, 25.0, -30.0);
	if (isCollision) writeBitmapString((void*)font, "Cannot - will crash!");
	glPopMatrix();

	// Fixed camera.
	gluLookAt(0.0, 10.0, 20.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	// Draw all the cube in arrayCubes.
	for (j = 0; j < COLUMNS; j++)
		for (i = 0; i < ROWS; i++)
			arrayCubes[i][j].draw();

	// Draw spacecraft.
	glPushMatrix();
	glTranslatef(xVal, 0.0, zVal);
	glRotatef(angle, 0.0, 1.0, 0.0);
	glCallList(spacecraft);
	glPopMatrix();
	// End left viewport.

	// Begin right viewport.
	glViewport(width / 2.0, 0, width / 2.0, height);
	glLoadIdentity();

	// Write text in isolated (i.e., before gluLookAt) translate block.
	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
	glRasterPos3f(-28.0, 25.0, -30.0);
	if (isCollision) writeBitmapString((void*)font, "Cannot - will crash!");
	glPopMatrix();

	// Draw a vertical line on the left of the viewport to separate the two viewports
	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(2.0);
	glBegin(GL_LINES);
	glVertex3f(-5.0, -5.0, -5.0);
	glVertex3f(-5.0, 5.0, -5.0);
	glEnd();
	glLineWidth(1.0);

	// Locate the camera at the tip of the cone and pointing in the direction of the cone.
	gluLookAt(xVal - 10 * sin((M_PI / 180.0) * angle),
		0.0,
		zVal - 10 * cos((M_PI / 180.0) * angle),
		xVal - 11 * sin((M_PI / 180.0) * angle),
		0.0,
		zVal - 11 * cos((M_PI / 180.0) * angle),
		0.0,
		1.0,
		0.0);



	// Draw all the cubes in arrayCubes.
	for (j = 0; j < COLUMNS; j++)
		for (i = 0; i < ROWS; i++)
			arrayCubes[i][j].draw();
	// End right viewport.

	glutSwapBuffers();
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 250.0);
	glMatrixMode(GL_MODELVIEW);

	// Pass the size of the OpenGL window.
	width = w;
	height = h;
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit(0);
		break;
	default:
		break;
	}
}

// Callback routine for non-ASCII key entry.
void specialKeyInput(int key, int x, int y)
{
	float tempxVal = xVal, tempzVal = zVal, tempAngle = angle;

	// Compute next position.
	if (key == GLUT_KEY_LEFT) tempAngle = angle + 5.0;
	if (key == GLUT_KEY_RIGHT) tempAngle = angle - 5.0;
	if (key == GLUT_KEY_UP)
	{
		tempxVal = xVal - sin(angle * M_PI / 180.0);
		tempzVal = zVal - cos(angle * M_PI / 180.0);
	}
	if (key == GLUT_KEY_DOWN)
	{
		tempxVal = xVal + sin(angle * M_PI / 180.0);
		tempzVal = zVal + cos(angle * M_PI / 180.0);
	}

	// Angle correction.
	if (tempAngle > 360.0) tempAngle -= 360.0;
	if (tempAngle < 0.0) tempAngle += 360.0;

	// Move spacecraft to next position only if there will not be collision with an cube.
	if (!asteroidCraftCollision(tempxVal, tempzVal, tempAngle))
	{
		isCollision = 0;
		xVal = tempxVal;
		zVal = tempzVal;
		angle = tempAngle;
	}
	else isCollision = 1;

	glutPostRedisplay();
}

// Routine to output interaction instructions to the C++ window.
void printInteraction(void)
{
	std::cout << "Interaction:" << std::endl;
	std::cout << "Press the left/right arrow keys to turn the craft." << std::endl
		<< "Press the up/down arrow keys to move the craft." << std::endl;
}

// Main routine.
int main(int argc, char** argv)
{
	printInteraction();
	glutInit(&argc, argv);

	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(800, 400);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("movingCar.cpp");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);
	glutSpecialFunc(specialKeyInput);

	glewExperimental = GL_TRUE;
	glewInit();

	setup();

	glutMainLoop();
}

