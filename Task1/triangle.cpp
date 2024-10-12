#include <GL/glew.h>
#include <GL/freeglut.h>
#include <cmath>

struct Scale {
    Scale(float shiftX, float shiftY, float scaleFactor)
        : shiftX(shiftX), shiftY(shiftY), scaleFactor(scaleFactor) {}

    float shiftX = 0;
    float shiftY = 0;
    float scaleFactor = 1;

    float X(float x) { return x * scaleFactor + shiftX; }
    float Y(float y) { return y * scaleFactor + shiftY; }
};

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

void draw_triangle() {
    // glClear(GL_COLOR_BUFFER_BIT);

    //WHEN SHIFTING, SHIFT Xs AND Ys OF BOTH TRIANGLES EQUALLY TO PRESERVE SHAPE & KEEP SCALE DIFFERENCE BET. THEM

    // Outer Triangle
    float outerShiftX = -0.5f;
    float outerShiftY = 0.0f;
    float outerScaleFactor = 0.6f;
    drawEquilateralTriangle(Scale(outerShiftX, outerShiftY, outerScaleFactor), 41, 174, 147);

    // Inner Triangle
    float innerShiftX = -0.5f;
    float innerShiftY = 0.0f;
    float innerScaleFactor = 0.47f;
    drawEquilateralTriangle(Scale(innerShiftX, innerShiftY, innerScaleFactor), 0, 0, 0); // Color of background
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(1200, 700);
    glutInitWindowPosition(70, 50);
    glutCreateWindow("PlayStation Logo");
    glutDisplayFunc(draw_triangle);
    glutMainLoop();
    return 0;
}
