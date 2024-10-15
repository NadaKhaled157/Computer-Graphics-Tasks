#pragma once

struct Scale
{
	Scale(float shiftX, float shiftY, float scaleFactor) : shiftX(shiftX), shiftY(shiftY), scaleFactor(scaleFactor) {}
	float shiftX = 0;
	float shiftY = 0;
	float scaleFactor = 1;
	float X(float x) { return x * scaleFactor + shiftX ; }
	float Y(float y) { return y * scaleFactor + shiftY ; }
};

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