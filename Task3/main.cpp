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
Ball ball;
// Drawing routine.
void drawScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
    glLoadIdentity();

    glTranslatef(0.0, 0.0, -20.0);
    glRotatef(Zangle, 0.0, 0.0, 1.0);
    glRotatef(Yangle, 0.0, 1.0, 0.0);


    glRotatef(Xangle, 1.0, 0.0, 0.0);

    // torso
    glPushMatrix();
    glScalef(1.0, 2.0, 0.5);
    glutWireCube(5.0);
    glPopMatrix();


    // head
    glPushMatrix();
    glTranslatef(0.0, 6.5, 0.0);
    glutWireSphere(1.5, 10, 10);
    glPopMatrix();

    // left leg
    glPushMatrix();
    glTranslatef(0.0, -5.0, 0.0);
    glRotatef(legAngle, 1.0, 0.0, 0.0);
    glTranslatef(0.0, 5.0, 0.0);

    glTranslatef(-1.0, -10.0, 0.0);
    //glTranslatef(20.0, 0.0, 0.0);
    glScalef(0.2, 2.0, 0.25);
    glutWireCube(5.0);
    glPopMatrix();

    // right leg
    glPushMatrix();
    glTranslatef(0.0, -5.0, 0.0);
    glRotatef(-legAngle, 1.0, 0.0, 0.0);
    glTranslatef(0.0, 5.0, 0.0);

    glTranslatef(1.0, -10.0, 0.0);
    glScalef(0.2, 2.0, 0.25);
    glutWireCube(5.0);
    glPopMatrix();


    // left hand
    glPushMatrix();
    glTranslatef(3, 5, 0.0);
    glRotatef(legAngle+180, 1.0, 0.0, 0.0);
    glTranslatef(0.0, 5.0, 0.0);

    glTranslatef(0.0, 0.0, 0.0);
    glScalef(0.2, 2.0, 0.25);
    glutWireCube(5.0);
    glPopMatrix();

    // right hand
    glPushMatrix();
    glTranslatef(-3.0, 5, 0.0);
    glRotatef(-legAngle+180, 1.0, 0.0, 0.0);
    glTranslatef(0.0, 5.0, 0.0);

    glTranslatef(0.0, 0.0, 0.0);
    glScalef(0.2, 2.0, 0.25);
    glutWireCube(5.0);
    glPopMatrix();
    glutSwapBuffers();

}

void Scene(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -20.0);
    glRotatef(Zangle, 0.0, 0.0, 1.0);
    glRotatef(Yangle, 0.0, 1.0, 0.0);
    glRotatef(Xangle, 1.0, 0.0, 0.0);
    ball.display();
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


void animation(int value)
{
    //if (forward)
    //{
    //    legAngle -= 5.0;
    //}
    //else
    //{
    //    legAngle += 5.0;
    //}

    //if (legAngle >= 30.0) forward = 1;
    //else if (legAngle <= -30.0) forward = 0;
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
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("box.cpp");
    glutDisplayFunc(Scene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);

    glewExperimental = GL_TRUE;
    glewInit();

    setup();

    glutMainLoop();
}

