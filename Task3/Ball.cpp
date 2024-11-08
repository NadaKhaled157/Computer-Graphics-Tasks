#include "Ball.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <math.h>

void Ball::display()
{
    // head
	glColor3f(1.0, 0.6, 0.0);
    glPushMatrix();
	glTranslatef(posX, posY, 0.0);
    glutWireSphere(5.0, 20, 20);
    glPopMatrix();
	// bound wall
	glPushMatrix();
	glBegin(GL_LINE_LOOP);
	glVertex3f(minX, minY,0.0);
	glVertex3f(minX, maxY,0.0);
	glVertex3f(maxX, maxY,0.0);
	glVertex3f(maxX, minY,0.0);
	glEnd();
	glPopMatrix();

}

void Ball::update(void)
{
	float gravity = 0.08f;
	while (dirAngle < 0)
		dirAngle += 360;
	while (dirAngle >= 360)
		dirAngle -= 360;

	float c = cos(dirAngle * Pi / 180);
	float s = sin(dirAngle * Pi / 180);
	float speedX = speed * c;
	float speedY = speed * s - gravity;
	if (posX+speedX >= maxX || posX+speedX <= minX)
	{
		posX = posX - speedX;
		dirAngle += 180 - 2 * dirAngle;
		speed -= 0.5;
	}
	if (posY+speedY >= maxY || posY+speedY <= minY)
	{
		posY = posY - speedY;
		dirAngle = -dirAngle;
		speed -= 0.5;

	}
	c = cos(dirAngle * Pi / 180);
	s = sin(dirAngle * Pi / 180);
	speedX = speed * c;
    speedY = speed * s - gravity;
	posX += speedX;
	posY += speedY;
	posY = fmaxf(minY, fminf(maxY, posY));
	if (minY - posY < 1 && speed < 0.1)
	{
		speed = 0;
	}
	dirAngle = atan2(speedY, speedX) * 180 / Pi;
}
