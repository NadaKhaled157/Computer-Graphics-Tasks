#pragma once
class Ball {
public:
	float posX = 300.0; // initial position
	float posY = 170.0;
	float radius = 1.5;
	float dirAngle = 30;
	float speed = 1.5;
	float gravity = 9.8;
	float maxY = 220.0;
	float minY = 120.0;
	float maxX = 350.0;
	float minX = 150.0;
	int refreshRate = 30;
	float Pi = 3.1415926;
	bool isMoving = false;
	void display();
	void update();
};
