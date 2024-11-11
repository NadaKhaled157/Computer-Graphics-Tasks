#include <iostream>
#include <GL/glut.h>
#include <math.h>
using namespace std;

float y1LeftHand = -500;
float y2LeftHand = -500;
float y1RightHand = -500;
float y2RightHand = -500;
int leftHandState = 0;
int rightHandState = 0;
float rightArmAngle = 0.0;
float leftArmAngle = 0.0;
bool isRightArmRotating = false; 
bool isLeftArmRotating = false;

void MyInit(void) {
    glClearColor(1, 1, 1, 0);
    glPointSize(100);
    gluOrtho2D(-1000, 1000, -1000, 500);
}

void head() {
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.0f, 0.0f);
    float pi;
    for (int i = 0;i <= 360;i++) {
        pi = i * 3.14 / 180;
        glVertex2f(160 * cos(pi), 160 * sin(pi));
    }
    glEnd();
}

void body() {
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2i(-25, -150);
    glVertex2i(25, -150);
    glVertex2i(25, -250);
    glVertex2i(25, -650);
    glVertex2i(25 , -800);
    glVertex2i(-25 , -800);
    glVertex2i(-25, -650);
    glVertex2i(-25 , -250);
    glEnd();
}

void handR() {
    glPushMatrix();
    glTranslatef(25, -250, 0);
    glRotatef(rightArmAngle, 0, 0, 1);
    glTranslatef(-(25), 250, 0);
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2i(-25 , -250);
    glVertex2i(25 , -250);
    glVertex2i(285, y1RightHand);
    glVertex2i(235, y2RightHand);
    glEnd();
    glPopMatrix();
}

void handL() {
    glPushMatrix();
    glTranslatef(-25 , -250, 0);
    glRotatef(leftArmAngle, 0.0, 0.0, 1.0);
    glTranslatef(25, 250, 0);

    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2i(-25 , -250);
    glVertex2i(-75 , -250);
    glVertex2i(-285, y1LeftHand);
    glVertex2i(-235, y2LeftHand);
    glEnd();

    glPopMatrix();
}

void legR() {
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2i(-25 , -800);
    glVertex2i(25 , -800);
    glVertex2i(235, -1000);
    glVertex2i(185, -1000);
    glEnd();
}

void legL() {
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2i(25 , -800);
    glVertex2i(-25 , -800);
    glVertex2i(-235, -1000);
    glVertex2i(-185, -1000);
    glEnd();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    head();
    body();
    handR();
    handL();
    legR();
    legL();
    glFlush();
}

void animateRightArm(int value) {
    if (isRightArmRotating) {  // Only update if rotation is active
        rightArmAngle += 5.0;
        if (rightArmAngle >= 360.0) {
            rightArmAngle -= 360.0;
        }
        glutPostRedisplay();  // Request display update
        glutTimerFunc(16, animateRightArm, 0);  // Schedule next animation
    }
}

void animateLeftArm(int value) {
    if (isLeftArmRotating) {  // Only update if rotation is active
        leftArmAngle -= 5.0;
        if (leftArmAngle <= -360.0) {
            leftArmAngle += 360.0;
        }
        glutPostRedisplay();  // Request display update
        glutTimerFunc(16, animateLeftArm, 0);  // Schedule next animation
    }
}

void mouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        isRightArmRotating = !isRightArmRotating;  // Toggle right arm rotation
        if (isRightArmRotating) {
            glutTimerFunc(0, animateRightArm, 0);  // Start right arm animation if not already
        }
    }
}

void keyboard(unsigned char key, int x, int y) {
    if (key == ' ') {  // Space key to toggle left arm rotation
        isLeftArmRotating = !isLeftArmRotating;  // Toggle left arm rotation
        if (isLeftArmRotating) {
            glutTimerFunc(0, animateLeftArm, 0);  // Start left arm animation if not already
        }
    }
}




int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutCreateWindow("360 Degree Arm Rotation");
    glutInitWindowSize(480, 720);
    glutInitWindowPosition(500, 500);
    glutDisplayFunc(display);
    glutMouseFunc(mouseClick);
    glutKeyboardFunc(keyboard);
    MyInit();
    glutMainLoop();
    return 0;
}
