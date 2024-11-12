#pragma once
class Ball {
public:
	float posX = 2;
	float posY = -6.5;
	float radius = 0.01;
	float dirAngle = 30;
	float speed = 0.8;
	float gravity = 9.8;
	float maxY = 10, minY = -10, maxX = 10, minX = -10;
	int refreshRate = 30;
	float Pi = 3.1415926;
	bool isMoving = false;
	bool shoot = false;
	void display();
	void update();
};