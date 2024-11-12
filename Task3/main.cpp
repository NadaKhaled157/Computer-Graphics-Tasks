// Tutorial activity: a simple animation for a walking man
/////////////////////////////////

#include <iostream>

#include <glew.h>
#include <freeglut.h>
#include "Ball.h"

// angles to rotate the scene
static float Xangle = 1.0, Yangle = 0.0, Zangle = 0.0;

static int animate = 0;
static int forward = 0;

static float legAngle = 0;
static float handangle = 0;
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
Ball ball;
void head() {
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.0f, 0.0f);
    float pi;
    for (int i = 0; i <= 360; i++) {
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
    glVertex2i(25, -800);
    glVertex2i(-25, -800);
    glVertex2i(-25, -650);
    glVertex2i(-25, -250);
    glEnd();
}

void handR() {
    glPushMatrix();
    glTranslatef(25, -250, 0);
    glRotatef(rightArmAngle, 0, 0, 1);
    glTranslatef(-(25), 250, 0);
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2i(-25, -250);
    glVertex2i(25, -250);
    glVertex2i(285, y1RightHand);
    glVertex2i(235, y2RightHand);
    glEnd();
    glPopMatrix();
}

void handL() {
    glPushMatrix();
    glTranslatef(-25, -250, 0);
    glRotatef(leftArmAngle, 0.0, 0.0, 1.0);
    glTranslatef(25, 250, 0);

    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2i(-25, -250);
    glVertex2i(-75, -250);
    glVertex2i(-285, y1LeftHand);
    glVertex2i(-235, y2LeftHand);
    glEnd();

    glPopMatrix();
}

void legR() {
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2i(-25, -800);
    glVertex2i(25, -800);
    glVertex2i(235, -1000);
    glVertex2i(185, -1000);
    glEnd();
}

void legL() {
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2i(25, -800);
    glVertex2i(-25, -800);
    glVertex2i(-235, -1000);
    glVertex2i(-185, -1000);
    glEnd();
}

// Room setup function
void roomSetup(float top_left_x, float top_left_y,
    float top_right_x, float top_right_y,
    float bottom_right_x, float bottom_right_y,
    float bottom_left_x, float bottom_left_y,
    float wall_length, float ceiling_length, float floor_length)
{
	// Back Wall
	glPushMatrix();
	glTranslatef(0.0, 0.0, -10);
    glColor3f(0.2, 0.3, 0.4);
    glBegin(GL_POLYGON);
    glVertex3f(top_left_x, top_left_y, 0.0);
    glVertex3f(top_right_x, top_right_y, 0.0);
    glVertex3f(bottom_right_x, bottom_right_y, 0.0);
    glVertex3f(bottom_left_x, bottom_left_y, 0.0);
    glEnd();
	glPopMatrix();
    // Right Wall
    glPushMatrix();
	glTranslatef(top_right_x, 0.0, 0.0);
	glRotatef(90.0, 0.0, 1.0, 0.0);
    glColor3f(0.3, 0.5, 0.7);
    glBegin(GL_POLYGON);
    glVertex3f(top_left_x, top_left_y, 0.0);
    glVertex3f(top_right_x, top_right_y, 0.0);
    glVertex3f(bottom_right_x, bottom_right_y, 0.0);
    glVertex3f(bottom_left_x, bottom_left_y, 0.0);
    glEnd();
    glPopMatrix();
	// Left Wall
    glPushMatrix();
    glTranslatef(-top_right_x, 0.0, 0.0);
    glRotatef(-90.0, 0.0, 1.0, 0.0);
    glColor3f(0.3, 0.5, 0.7);
    glBegin(GL_POLYGON);
    glVertex3f(top_left_x, top_left_y, 0.0);
    glVertex3f(top_right_x, top_right_y, 0.0);
    glVertex3f(bottom_right_x, bottom_right_y, 0.0);
    glVertex3f(bottom_left_x, bottom_left_y, 0.0);
    glEnd();
    glPopMatrix();
	// Ceiling
	glPushMatrix();
	glTranslatef(0.0, top_left_y, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
    glColor3f(0.8, 0.9, 1.0);
	glBegin(GL_POLYGON);
	glVertex3f(top_left_x, top_left_y, 0.0);
	glVertex3f(top_right_x, top_right_y, 0.0);
	glVertex3f(bottom_right_x, bottom_right_y, 0.0);
	glVertex3f(bottom_left_x, bottom_left_y, 0.0);
	glEnd();
	glPopMatrix();
	// Floor
	glPushMatrix();
	glTranslatef(0.0, -top_left_y, 0.0);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
    glColor3f(0.6, 0.5, 0.4);
	glBegin(GL_POLYGON);
	glVertex3f(top_left_x, top_left_y, 0.0);
	glVertex3f(top_right_x, top_right_y, 0.0);
	glVertex3f(bottom_right_x, bottom_right_y, 0.0);
	glVertex3f(bottom_left_x, bottom_left_y, 0.0);
	glEnd();
	glPopMatrix();

}


void Scene(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -20.0);
    glRotatef(Zangle, 0.0, 0.0, 1.0);
    glRotatef(Yangle, 0.0, 1.0, 0.0);
    glRotatef(Xangle, 1.0, 0.0, 0.0);
	roomSetup(-10, 10, 10, 10, 10, -10, -10, -10, 20, 20, 20);
	glPushMatrix();
    if (not ball.shoot){
        glTranslatef(0.5, -5.5, 0.0);
        glRotatef(-leftArmAngle, 0.0, 0.0, 1.0);
        glTranslatef(-0.5, 5.5, 0.0);
        //glTranslatef(2.0, -6.5, 0.0);
    }
    ball.display();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, -4.0, 0.0);
	//glTranslatef(ball.posX, ball.posY, 0.0);
	glScalef(-0.006, 0.006, 1.0);
	head();
	body();
	handR();
	handL();
	body();
	legL();
    legR();
	glPopMatrix();
    glutSwapBuffers();
}

// Initialization routine.
void setup(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
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
void mouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        isRightArmRotating = !isRightArmRotating;  // Toggle right arm rotation
        if (isRightArmRotating) {
            glutTimerFunc(0, animateRightArm, 0);  // Start right arm animation if not already
        }
    }
}
void animateLeftArm(int value) {
    if (ball.shoot)
    {
		isLeftArmRotating = false;
		return;
	}
    if (isLeftArmRotating) {  // Only update if rotation is active
        leftArmAngle -= 5.0;
        if (leftArmAngle <= -400.0) {
            ball.dirAngle = 50;
			ball.shoot = true;
			leftArmAngle = 0;
        }
        glutPostRedisplay();  // Request display update
        glutTimerFunc(16, animateLeftArm, 0);  // Schedule next animation
    }
}

void animation(int value)
{
    if (forward)
    {
        legAngle -= 5.0;
    }
    else
    {
        legAngle += 5.0;
    }

    if (legAngle >= 30.0) forward = 1;
    else if (legAngle <= -30.0) forward = 0;

	ball.update();

    glutPostRedisplay();

    if (animate) glutTimerFunc(30, animation, 1);
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        exit(0);
        break;

    case ' ':
        if (animate)
        {
            if (ball.speed == 0.0)
            {
				ball.posX = 2;
				ball.posY = -6.5;
				//ball.dirAngle = 30;
                ball.speed = 0.8;
				ball.shoot = false;
				isLeftArmRotating = true;
            }
            animate = 0;
			ball.isMoving = false;
        }
        else
        {
            animate = 1;
            animation(1);
			ball.isMoving = true;
			ball.update();
        }
        isLeftArmRotating = !isLeftArmRotating;  // Toggle left arm rotation
        if (isLeftArmRotating) {
            glutTimerFunc(0, animateLeftArm, 0);  // Start left arm animation if not already
        }
        break;


    case 'x':
        Xangle += 5.0;
        if (Xangle > 360.0) Xangle -= 360.0;
        glutPostRedisplay();
        break;
    case 'X':
        Xangle -= 5.0;
        if (Xangle < 0.0) Xangle += 360.0;
        glutPostRedisplay();
        break;
    case 'y':
        Yangle += 5.0;
        if (Yangle > 360.0) Yangle -= 360.0;
        glutPostRedisplay();
        break;
    case 'Y':
        Yangle -= 5.0;
        if (Yangle < 0.0) Yangle += 360.0;
        glutPostRedisplay();
        break;
    case 'z':
        Zangle += 5.0;
        if (Zangle > 360.0) Zangle -= 360.0;
        glutPostRedisplay();
        break;
    case 'Z':
        Zangle -= 5.0;
        if (Zangle < 0.0) Zangle += 360.0;
        glutPostRedisplay();
        break;

    default:
        break;
    }
}

// Main routine.
int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitContextVersion(4, 3);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(1000, 700);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("box.cpp");
    glutDisplayFunc(Scene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);

    glewExperimental = GL_TRUE;
    glewInit();

    setup();

    glutMainLoop();
}