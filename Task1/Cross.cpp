#include <cstdlib>
#include <cmath>
#include <glew.h>
#include <freeglut.h>

struct Scale
{
    Scale(float shiftX, float shiftY, float scaleFactor) : shiftX(shiftX), shiftY(shiftY), scaleFactor(scaleFactor) {}
    float shiftX = 0;
    float shiftY = 0;
    float scaleFactor = 1;
    float X(float x) { return x * scaleFactor + shiftX; }
    float Y(float y) { return y * scaleFactor + shiftY; }
};

void drawX(float x, float y, float size, float thickness, float r, float g, float b) {
    glColor3f(r, g, b); // Set the color for the letter

    // Calculate the coordinates for the two rectangles of the "X"
    float x1 = x - size / 2;
    float x2 = x + size / 2;
    float y1 = y - size / 2;
    float y2 = y + size / 2;

    float halfThickness = thickness / 2.0f;

    // Draw the first diagonal rectangle (bottom-left to top-right)
    glBegin(GL_QUADS);
    glVertex2f(x1 - halfThickness, y1); // Bottom-left
    glVertex2f(x1 + halfThickness, y1); // Bottom-left thickened
    glVertex2f(x2 + halfThickness, y2); // Top-right thickened
    glVertex2f(x2 - halfThickness, y2); // Top-right
    glEnd();

    // Draw the second diagonal rectangle (top-left to bottom-right)
    glBegin(GL_QUADS);
    glVertex2f(x1 - halfThickness, y2); // Top-left
    glVertex2f(x1 + halfThickness, y2); // Top-left thickened
    glVertex2f(x2 + halfThickness, y1); // Bottom-right thickened
    glVertex2f(x2 - halfThickness, y1); // Bottom-right
    glEnd();
}

void drawScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the letter "X" at position (0, 0) with a size of 40, thickness of 5, and color red
    drawX(0.0f, 0.0f, 40.0f, 5.0f, 0.63f, 0.66f, 0.81f); // Red "X" with thickness

    glFlush();
}

void resize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-100.0, 100.0, -100.0, 100.0, -30.0, 30.0);  // Adjusted to larger range
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Initialization routine.
void setup(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
}



// Main routine.
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitContextVersion(4, 3);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("cross.cpp");
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glewExperimental = GL_TRUE;
    glewInit();

    setup();

    glutMainLoop();
}
