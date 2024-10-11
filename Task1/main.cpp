//cr. code: Sumanta Guha.
////////////////////////

//importing the header files
#include <glew.h>
#include <freeglut.h>
#include <math.h>

struct Scale
{
	Scale(float shiftX, float shiftY, float scaleFactor) : shiftX(shiftX), shiftY(shiftY), scaleFactor(scaleFactor) {}
	float shiftX = 0;
	float shiftY = 0;
	float scaleFactor = 1;
	float X(float x) { return x * scaleFactor + shiftX; }
	float Y(float y) { return y * scaleFactor + shiftY; }
};

void Square(Scale scale)
{
	glBegin(GL_POLYGON);
	glColor3b(0, 0, 0);
	glVertex2f(scale.X(20), scale.Y(20));
	glVertex2f(scale.X(80), scale.Y(20));
	glVertex2f(scale.X(80), scale.Y(80));
	glVertex2f(scale.X(20), scale.Y(80));
	glEnd();
}
// Drawing routine.
void drawScene()
{
	float shiftX = 10;
	float shiftY = 10;
	float scaleFactor = 0.5;

    glClear(GL_COLOR_BUFFER_BIT);
	Square(Scale(shiftX,shiftY,scaleFactor));
    glFlush();
}

// Initialization routine.
void setup(void)
{
	//the clearing color of the opengl window (background)
	glClearColor(1, 1, 1, 1);
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
	// drawing the entire window
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//glOrtho(left, right, bottom, top, near, far)
	//Sets up a viewing box span along the x-axis is from left to right, along the y-axis from bottom to top, 
	// and along the z-axis from ?far to ?near.
	glOrtho(0.0, 100.0, 0.0, 100.0, -1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// Keyboard input processing routine. x & y are location of the mouse
void keyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
		// ascii of escape key
	case 'q':
		exit(0);
		break;
	default:
		break;
	}
}

// Main routine.
int main(int argc, char** argv)
{

	glutInit(&argc, argv);	// initializes the FreeGLUT library.

	// create context, set its version and set backward compatibility. 
	// context is the interface between an instance of OpenGL and the rest of the system
	glutInitContextVersion(3, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	// wanting an OpenGL context to support a single-buffered frame, each pixel having red, green, blue and alpha values.
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);

	// set the initial size of the OpenGL window and the location of its top left corner on the computer screen
	glutInitWindowSize(1000, 700);
	glutInitWindowPosition(0, 0);

	// creates the OpenGL context and its associated window with the specified string parameter as title.
	glutCreateWindow("square.cpp");

	// callback routines – when the OpenGL window is to be drawn, when it is resized, 
	// and when keyboard input is received, respectively
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);

	// initializes GLEW (the OpenGL Extension Wrangler Library) which handles the loading of OpenGL extensions, 
	// with the switch set so that extensions implemented even in pre-release drivers are exposed.
	glewExperimental = GL_TRUE;
	glewInit();

	setup();

	// begins the event-processing loop, calling registered callback routines as needed
	glutMainLoop();

}