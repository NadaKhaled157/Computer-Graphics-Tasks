

#define _USE_MATH_DEFINES 

#include <cstdlib>
#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>

#include <GL/glew.h>
#include <freeglut.h> 

// Globals.
static float highlightColor[3] = { 0.0, 0.0, 0.0 }; // Emphasize color.
static float lowlightColor[3] = { 0.7, 0.7, 0.7 }; // De-emphasize color.
static float partSelectColor[3] = { 1.0, 0.0, 0.0 }; // Selection indicate color.
static long font = (long)GLUT_BITMAP_8_BY_13; // Font selection.
static int animateMode = 0; // In animation mode?
static int animationPeriod = 1000; // Time interval between frames.
static std::ofstream outFile; // File to write configurations data.
static std::ifstream inFile; // File to read configurations data.

// Camera class.
class Camera
{
public:
	Camera();
	void incrementViewDirection();
	void decrementViewDirection();
	void incrementZoomDistance() { zoomDistance += 1.0; }
	void decrementZoomDistance() { zoomDistance -= 1.0; }

	float getViewDirection() const { return viewDirection; }
	float getZoomDistance() const { return zoomDistance; }

private:
	float viewDirection;
	float zoomDistance;
};

// Global camera.
Camera camera;

// Camera constructor.
Camera::Camera()
{
	viewDirection = 0.0;
	zoomDistance = 30.0;
}

// Function to increment camera viewing angle.
void Camera::incrementViewDirection()
{
	viewDirection += 5.0;
	if (viewDirection > 360.0) viewDirection -= 360.0;
}

// Function to decrement camera viewing angle.
void Camera::decrementViewDirection()
{
	viewDirection -= 5.0;
	if (viewDirection < 0.0) viewDirection += 360.0;
}

// Man class.
class Man
{
public:
	Man();
	void incrementSelectedPart();

	void incrementPartAngle();
	void decrementPartAngle();
	void setPartAngle(float angle) { partAngles[selectedPart] = angle; }

	void incrementUpMove() { upMove += 0.1; }
	void decrementUpMove() { upMove -= 0.1; }
	void setUpMove(float move) { upMove = move; }

	void incrementForwardMove() { forwardMove += 0.1; }
	void decrementForwardMove() { forwardMove -= 0.1; }
	void setForwardMove(float move) { forwardMove = move; }

	void setHighlight(int inputHighlight) { highlight = inputHighlight; }

	void draw();
	void outputData();
	void writeData();

	float getPartAngle(int partIndex) const
	{
		if (partIndex >= 0 && partIndex < 9)
			return partAngles[partIndex];
		return 0.0f; // Return 0.0 for out-of-range indices.
	}

	// Add a setPartAngle method if you don�t already have it
	void setPartAngle(int partIndex, float angle)
	{
		if (partIndex >= 0 && partIndex < 9)
			partAngles[partIndex] = angle;
	}
private:
	// Man configuration values. 
	float partAngles[9]; // Angles from 0 to 360 of 9 body parts - torso, left and right
						 // upper arms, left and right lower arms, left and right upper
						 // legs, left and right lower legs. 
						 // All parts move parallel to the same plane.

	float upMove, forwardMove; // Up and forward translation components - both lie
							   // on the plane parallel to which parts rotate -
							   // therefore all translations and part rotations
							   // are along one fixed plane.

	int selectedPart; // Selected part number - this part can be interactively rotated
					  // in the develop mode.

	int highlight; // If man is currently selected.
};

// Global vector of man configurations.
std::vector<Man> manVector;

// Global iterators to traverse manVector.
std::vector<Man>::iterator manVectorIterator;
std::vector<Man>::iterator manVectorAnimationIterator;

// Man constructor.
Man::Man()
{
	for (int i = 0; i<9; i++) partAngles[i] = 0.0;
	upMove = 0.0;
	forwardMove = 0.0;
	selectedPart = 0;
	highlight = 1;
}

// Function to incremented selected part..
void Man::incrementSelectedPart()
{
	if (selectedPart < 8) selectedPart++;
	else selectedPart = 0;
}

// Function to draw man.
void Man::draw()
{
	if (highlight || animateMode) glColor3fv(highlightColor);
	else glColor3fv(lowlightColor);

	glPushMatrix();

	// Up and forward translations.
	glTranslatef(0.0, upMove, forwardMove);

	// Torso begin.
	if (highlight && !animateMode) if (selectedPart == 0) glColor3fv(partSelectColor);

	glRotatef(partAngles[0], 1.0, 0.0, 0.0);

	glPushMatrix();
	glScalef(4.0, 16.0, 4.0);
	glutWireCube(1.0);
	glPopMatrix();
	if (highlight && !animateMode) glColor3fv(highlightColor);
	// Torso end.

	// Head begin.
	glPushMatrix();

	glTranslatef(0.0, 11.5, 0.0);
	glPushMatrix();
	glScalef(2.0, 3.0, 2.0);
	glutWireSphere(1.0, 10, 8);
	glPopMatrix();

	glPopMatrix();
	// Head end.

	// Left upper and lower arm begin.
	glPushMatrix();

	// Left upper arm begin.
	if (highlight && !animateMode) if (selectedPart == 1) glColor3fv(partSelectColor);
	glTranslatef(3.0, 8.0, 0.0);
	glRotatef(180.0 + partAngles[1], 1.0, 0.0, 0.0);
	glTranslatef(0.0, 4.0, 0.0);
	glPushMatrix();
	glScalef(2.0, 8.0, 2.0);
	glutWireCube(1.0);
	glPopMatrix();
	if (highlight && !animateMode) glColor3fv(highlightColor);
	// Left upper arm end.

	// Left lower arm begin.
	if (highlight && !animateMode) if (selectedPart == 2) glColor3fv(partSelectColor);
	glTranslatef(0.0, 4.0, 0.0);
	glRotatef(partAngles[2], 1.0, 0.0, 0.0);
	glTranslatef(0.0, 4.0, 0.0);
	glPushMatrix();
	glScalef(2.0, 8.0, 2.0);
	glutWireCube(1.0);
	glPopMatrix();
	if (highlight && !animateMode) glColor3fv(highlightColor);
	// Left lower arm end.

	glPopMatrix();
	// Left upper and lower arm end.

	// Right upper and lower arm begin.
	glPushMatrix();

	// Right upper arm begin.
	if (highlight && !animateMode) if (selectedPart == 3) glColor3fv(partSelectColor);
	glTranslatef(-3.0, 8.0, 0.0);
	glRotatef(180.0 + partAngles[3], 1.0, 0.0, 0.0);
	glTranslatef(0.0, 4.0, 0.0);
	glPushMatrix();
	glScalef(2.0, 8.0, 2.0);
	glutWireCube(1.0);
	glPopMatrix();
	if (highlight && !animateMode) glColor3fv(highlightColor);
	// Right upper arm end.

	// Right lower arm begin.
	if (highlight && !animateMode) if (selectedPart == 4) glColor3fv(partSelectColor);
	glTranslatef(0.0, 4.0, 0.0);
	glRotatef(partAngles[4], 1.0, 0.0, 0.0);
	glTranslatef(0.0, 4.0, 0.0);
	glPushMatrix();
	glScalef(2.0, 8.0, 2.0);
	glutWireCube(1.0);
	glPopMatrix();
	if (highlight && !animateMode) glColor3fv(highlightColor);
	// Right lower arm end.

	glPopMatrix();
	// Right upper and lower arm end.

	// Left upper and lower leg with foot begin.
	glPushMatrix();

	// Left upper leg begin.
	if (highlight && !animateMode) if (selectedPart == 5) glColor3fv(partSelectColor);
	glTranslatef(1.5, -8.0, 0.0);
	glRotatef(partAngles[5], 1.0, 0.0, 0.0);
	glTranslatef(0.0, -4.0, 0.0);
	glPushMatrix();
	glScalef(2.0, 8.0, 2.0);
	glutWireCube(1.0);
	glPopMatrix();
	if (highlight && !animateMode) glColor3fv(highlightColor);
	// Left upper leg end.

	// Left lower leg with foot begin.
	if (highlight && !animateMode) if (selectedPart == 6) glColor3fv(partSelectColor);
	glTranslatef(0.0, -4.0, 0.0);
	glRotatef(partAngles[6], 1.0, 0.0, 0.0);
	glTranslatef(0.0, -4.0, 0.0);

	// Lower leg.
	glPushMatrix();
	glScalef(2.0, 8.0, 2.0);
	glutWireCube(1.0);
	glPopMatrix();

	// Foot.
	glTranslatef(0.0, -5.0, 0.5);
	glPushMatrix();
	glScalef(2.0, 1.0, 3.0);
	glutWireCube(1.0);
	glPopMatrix();

	if (highlight && !animateMode) glColor3fv(highlightColor);
	// Left lower leg with foot end.

	glPopMatrix();
	// Left upper and lower leg with foot end.

	// Right upper and lower leg with foot begin.
	glPushMatrix();

	// Right upper leg begin.
	if (highlight && !animateMode) if (selectedPart == 7) glColor3fv(partSelectColor);
	glTranslatef(-1.5, -8.0, 0.0);
	glRotatef(partAngles[7], 1.0, 0.0, 0.0);
	glTranslatef(0.0, -4.0, 0.0);
	glPushMatrix();
	glScalef(2.0, 8.0, 2.0);
	glutWireCube(1.0);
	glPopMatrix();
	if (highlight && !animateMode) glColor3fv(highlightColor);
	// Right upper leg end.

	// Right lower leg with foot begin.
	if (highlight && !animateMode) if (selectedPart == 8) glColor3fv(partSelectColor);
	glTranslatef(0.0, -4.0, 0.0);
	glRotatef(partAngles[8], 1.0, 0.0, 0.0);
	glTranslatef(0.0, -4.0, 0.0);

	// Lower leg.
	glPushMatrix();
	glScalef(2.0, 8.0, 2.0);
	glutWireCube(1.0);
	glPopMatrix();

	// Foot.
	glTranslatef(0.0, -5.0, 0.5);
	glPushMatrix();
	glScalef(2.0, 1.0, 3.0);
	glutWireCube(1.0);
	glPopMatrix();

	if (highlight && !animateMode) glColor3fv(highlightColor);
	// Right lower leg with foot end.

	glPopMatrix();
	// Right upper and lower leg with foot end.

	glPopMatrix();
}

// Drawing routine.
void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	// Place camera.
	gluLookAt(camera.getZoomDistance() * sin(camera.getViewDirection()*M_PI / 180.0), 0.0,
		camera.getZoomDistance() * cos(camera.getViewDirection()*M_PI / 180.0), 0.0,
		0.0, 0.0, 0.0, 1.0, 0.0);

	// Move man right 10 units because of data text on left of screen.
	glTranslatef(10.0, 0.0, 0.0);
	manVectorAnimationIterator->draw();

	// Other (fixed) objects in scene are drawn below starting here.

	// Black floor.
	glColor3f(0.0, 0.0, 0.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	for (float z = -25.0; z<100.0; z += 5.0)
	{
		glBegin(GL_TRIANGLE_STRIP);
		for (float x = -50.0; x<50.0; x += 5.0)
		{
			glVertex3f(x, -25.0, z);
			glVertex3f(x, -25.0, z + 5.0);
		}
		glEnd();
	}

	// Green sphere.
	glColor3f(0.0, 1.0, 0.0);
	glTranslatef(0.0, -20.0, 10.0);
	glPushMatrix();
	glScalef(5.0, 5.0, 5.0);
	//glutWireSphere(1.0, 10, 8);
	glPopMatrix();

	glutSwapBuffers();
}

// Timer function.
void animate(int value)
{
	if (animateMode)
	{
		// Rotate upper and lower left and right arms.
		manVectorAnimationIterator->setPartAngle((int)(manVectorAnimationIterator->getPartAngle(1) + 10) % 360);
		manVectorAnimationIterator->incrementSelectedPart();

		manVectorAnimationIterator->setPartAngle((int)(manVectorAnimationIterator->getPartAngle(2) + 10) % 360);
		manVectorAnimationIterator->incrementSelectedPart();

		manVectorAnimationIterator->setPartAngle((int)(manVectorAnimationIterator->getPartAngle(3) + 10) % 360);
		manVectorAnimationIterator->incrementSelectedPart();

		manVectorAnimationIterator->setPartAngle((int)(manVectorAnimationIterator->getPartAngle(4) + 10) % 360);

		manVectorAnimationIterator++;
		if (manVectorAnimationIterator == manVector.end())
			manVectorAnimationIterator = manVector.begin();

		glutPostRedisplay();
		glutTimerFunc(animationPeriod, animate, 1);
	}
}

// Function to read configurations from file.
void inputConfigurations(void)
{
	float readValue;
	int i;
	Man newMan;

	inFile.open("animateManDataIn.txt");

	while (!inFile.eof())
	{
		newMan = Man();
		for (i = 0; i < 9; i++)
		{
			inFile >> readValue;
			newMan.setPartAngle(readValue);
			newMan.incrementSelectedPart();
		}
		inFile >> readValue;
		newMan.setUpMove(readValue);
		inFile >> readValue;
		newMan.setForwardMove(readValue);
		manVector.push_back(Man(newMan));
	}
	manVector.pop_back(); // Remove configuration at the back because the routine
						  // read eol after the last configuration and before eof and
						  // creates a fake configuration.
}

// Initialization routine.
void setup(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);

	inputConfigurations(); // Read configurations from file.

	// Initialize global iterators for manVector.
	manVectorIterator = manVector.begin();
	manVectorAnimationIterator = manVector.begin();

	// Initialize camera.
	camera = Camera();
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 100.0);

	glMatrixMode(GL_MODELVIEW);
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit(0);
		break;
	case 'a': // Toggle between animate mode on and off..
		if (animateMode == 0)
		{
			manVectorAnimationIterator = manVector.begin();
			animateMode = 1;
			animate(1);
		}
		else animateMode = 0;
		glutPostRedisplay();
		break;
	case 'r': // Rotate camera.
		camera.incrementViewDirection();
		glutPostRedisplay();
		break;
	case 'R': // Rotate camera.
		camera.decrementViewDirection();
		glutPostRedisplay();
		break;
	case 'z': // Zoom in.
		camera.decrementZoomDistance();
		glutPostRedisplay();
		break;
	case 'Z': // Zoom out.
		camera.incrementZoomDistance();
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

// Callback routine for non-ASCII key entry.
void specialKeyInput(int key, int x, int y)
{
	if (key == GLUT_KEY_DOWN) animationPeriod += 10;
	if (key == GLUT_KEY_UP) if (animationPeriod > 10) animationPeriod -= 10;
	glutPostRedisplay();
}

// Routine to output interaction instructions to the C++ window.
void printInteraction(void)
{
	std::cout << "Interaction:" << std::endl;
	std::cout << "Press a to toggle between animation on/off." << std::endl
		<< "Press the up/down arrow keys to speed up/slow down animation." << std::endl
		<< "Press r/R to rotate the viewpoint." << std::endl
		<< "Press z/Z to zoom in/out." << std::endl;
}

// Main routine.
int main(int argc, char **argv)
{
	printInteraction();
	glutInit(&argc, argv);

	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("animateMan2.cpp");

	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);
	glutSpecialFunc(specialKeyInput);

	glewExperimental = GL_TRUE;
	glewInit();

	setup();

	glutMainLoop();
}

