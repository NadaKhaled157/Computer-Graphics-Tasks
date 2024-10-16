//cr. code: Sumanta Guha.
////////////////////////

//importing the header files
#include <glew.h>
#include <freeglut.h>
#include <math.h>

#include <iostream>

struct Scale
{
    Scale(float shiftX, float shiftY, float scaleFactor) : shiftX(shiftX), shiftY(shiftY), scaleFactor(scaleFactor) {}
    float shiftX = 0;
    float shiftY = 0;
    float scaleFactor = 1;
    float X(float x) { return x * scaleFactor + shiftX; }
    float Y(float y) { return y * scaleFactor + shiftY; }
};

using namespace std;
float pi = 3.14159265359;
void ph(Scale scale)
{
    Scale ps = Scale(scale.shiftX + 5 * scale.scaleFactor, scale.shiftY, scale.scaleFactor * 1.1);
    glBegin(GL_POLYGON);
    float thikness = 2;
    float blackR = 0;
    float blackG = 0;
    float blackB = 0;
    float whiteR = 0.0;
    float whiteG = 0.53;
    float whiteB = 0.83;
    glColor3f(whiteR, whiteG, whiteB);
    glVertex2f(ps.X(0), ps.Y(0));
    glVertex2f(ps.X(thikness), ps.Y(0));
    glVertex2f(ps.X(thikness), ps.Y(30));
    glVertex2f(ps.X(0), ps.Y(30));
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(whiteR, whiteG, whiteB);
    for (int i = 90; i < 270; i++)
    {
        float r = 7;
        float pointx = -r * cos(i * pi / 180) + thikness - 1;
        float pointy = r * sin(i * pi / 180) + 30 - r;
        glVertex2f(ps.X(pointx), ps.Y(pointy));
    }
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(blackR, blackG, blackB);
    for (int i = 90; i < 270; i++)
    {
        float r = 4;
        float pointx = -r * cos(i * pi / 180) + thikness;
        float pointy = r * 1.2 * sin(i * pi / 180) + 26 - r;
        glVertex2f(ps.X(pointx), ps.Y(pointy));
    }
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
    float shiftX = 20;
    float shiftY = 20;
    glColor3f(whiteR, whiteG, whiteB);
    glVertex2f(scale.X(shiftX), scale.Y(shiftY));
    for (int i = 0; i <= 360; i++)
    {
        float r = 5;
        float pointx = r * cos(i * pi / 180) + shiftX;
        float pointy = r * 1.5 * sin(i * pi / 180) + shiftY;
        glVertex2f(scale.X(pointx), scale.Y(pointy));
    }
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(blackR, blackG, blackB);
    shiftX = 21;
    shiftY = 20;
    glVertex2f(scale.X(shiftX), scale.Y(shiftY));
    for (int i = 0; i <= 360; i++)
    {
        float r = 4.4;
        float pointx = r * cos(i * pi / 180) + shiftX;
        float pointy = r * 1.5 * sin(i * pi / 180) + shiftY;
        glVertex2f(scale.X(pointx), scale.Y(pointy));
    }
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
    shiftX = 18;
    shiftY = 6.5;
    glColor3f(whiteR, whiteG, whiteB);
    glVertex2f(scale.X(shiftX), scale.Y(shiftY));
    for (int i = 0; i <= 360; i++)
    {
        float r = 5;
        float pointx = r * cos(i * pi / 180) + shiftX;
        float pointy = r * 1.5 * sin(i * pi / 180) + shiftY;
        glVertex2f(scale.X(pointx), scale.Y(pointy));
    }
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(blackR, blackG, blackB);
    shiftX = 17;
    shiftY = 6.5;
    glVertex2f(scale.X(shiftX), scale.Y(shiftY));
    for (int i = 0; i <= 360; i++)
    {
        float r = 4.4;
        float pointx = r * cos(i * pi / 180) + shiftX;
        float pointy = r * 1.5 * sin(i * pi / 180) + shiftY;
        glVertex2f(scale.X(pointx), scale.Y(pointy));
    }
    glEnd();
    Scale erase = Scale(scale.shiftX + 10.5 * scale.scaleFactor, scale.shiftY + 10.5 * scale.scaleFactor, scale.scaleFactor);
    glBegin(GL_POLYGON);
    glColor3f(blackR, blackG, blackB);
    glVertex2f(erase.X(12), erase.Y(0));
    glVertex2f(erase.X(15), erase.Y(5));
    glVertex2f(erase.X(8), erase.Y(4));
    glVertex2f(erase.X(12), erase.Y(8));
    glEnd();
    Scale erase2 = Scale(scale.shiftX + 6 * scale.scaleFactor, scale.shiftY + 9 * scale.scaleFactor, scale.scaleFactor);
    glBegin(GL_POLYGON);
    glColor3f(blackR, blackG, blackB);
    glVertex2f(erase2.X(14), erase2.Y(2));
    glVertex2f(erase2.X(10), erase2.Y(6));
    glVertex2f(erase2.X(7), erase2.Y(1));
    glEnd();
}
void drawEquilateralTriangle(Scale scale, int r, int g, int b) {
	glBegin(GL_TRIANGLES);
	glColor3ub(r, g, b);

	// We pass the x and the y and it will scale and shift according to
	// the parameters we gave the Scale when creating the triangle
	//Use sqrt( (x2 - x1)^2 + (y2 - y1)^2) ) to check equivalence of sides
	glVertex2f(scale.X(0.0f), scale.Y(scale.scaleFactor)); // Top (0, scaleFactor)
	glVertex2f(scale.X(-scale.scaleFactor * 0.5f), scale.Y(-scale.scaleFactor * 0.5f)); // Bottom left (-scaleFactor*0.5, -scaleFactor*0.5)
	glVertex2f(scale.X(scale.scaleFactor * 0.5f), scale.Y(-scale.scaleFactor * 0.5f)); // Bottom right (scaleFactor*0.5, -scaleFactor*0.5)
	glEnd();
}
void drawCircle(Scale scale, int r, int g, int b) {
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(r, g, b);
    float radius = scale.scaleFactor;
    int numSegments = 150;
    float aspectRatio = 700.0f / 500.0f; // Calculate the aspect ratio of the screen
    glVertex2f(scale.X(0), scale.Y(0)); // Scale the y-coordinate by the aspect ratio
    for (int i = 0; i <= numSegments; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(numSegments);
        float x = radius * cosf(theta);
        float y = radius * sinf(theta) * aspectRatio; // Scale the y-coordinate by the aspect ratio
        glVertex2f(scale.X(x), scale.Y(y));
    }
    glEnd();
}

// Drawing routine.
void drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT);
	float scaleps = 0.8;
	ph(Scale(40,60,scaleps));
	float scaleCircle = 3.1;
	drawCircle(Scale(35, 34, scaleCircle), 255, 69, 0); // Outer Circle (Orange)
	drawCircle(Scale(35, 34, scaleCircle * 0.89), 0, 0, 0); // Inner Circle (Black)

	float scaleTriangle = 4;
	drawEquilateralTriangle(Scale(15, 30, scaleTriangle), 41, 174, 147);
	drawEquilateralTriangle(Scale(15, 30, scaleTriangle * 0.8), 0, 0, 0); // Color of background
    glFlush();
}

// Initialization routine.
void setup(void)
{
	//the clearing color of the opengl window (background)
	glClearColor(0, 0, 0, 1);
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
	glutInitWindowSize(800, 500);
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
