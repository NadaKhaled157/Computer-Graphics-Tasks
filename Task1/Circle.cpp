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


void drawCircle(Scale scale, int r, int g, int b) {
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(r, g, b);
    float radius = scale.scaleFactor;
    int numSegments = 150;
    glVertex2f(scale.X(0), scale.Y(0)); 
    for (int i = 0; i <= numSegments; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(numSegments);
        float x = radius * cosf(theta);
        float y = radius * sinf(theta);
        glVertex2f(scale.X(x), scale.Y(y));
    }
    glEnd();
}

void drawHollowCircle() {
    float shiftY = 0.05f; // Adjust this value to move the circles up
    drawCircle(Scale(-0.1f, shiftY, 0.455f), 255, 69, 0); // Outer Circle (Orange)
    drawCircle(Scale(-0.1f, shiftY, 0.4f), 0, 0, 0); // Inner Circle (Black)
}

void drawShapes() {
    drawHollowCircle(); 
    glFlush();
}

void resize(int width, int height) {
    // Set the viewport to the new window dimensions
    glViewport(0, 0, width, height);

    // Reset the projection matrix for circle rendering
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Calculate the aspect ratio for the circle only
    float aspectRatio = (float)width / (float)height;
    if (width >= height) {
        glOrtho(-1.0f * aspectRatio, 1.0f * aspectRatio, -1.0f, 1.0f, -1.0f, 1.0f);
    }
    else {
        glOrtho(-1.0f, 1.0f, -1.0f / aspectRatio, 1.0f / aspectRatio, -1.0f, 1.0f);
    }

    glMatrixMode(GL_MODELVIEW); // Switch back to the model view matrix
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1200, 700);
    glutInitWindowPosition(50, 70);
    glutCreateWindow("PlayStation Logo");
    glutDisplayFunc(drawShapes);
    glutReshapeFunc(resize); // Register the resize function
    glutMainLoop();
    return 0;
}
