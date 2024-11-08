#pragma once
class Ball {
public:
	float posX =0.0;
	float posY =0.0;
	float radius= 1.5;
	float dirAngle = 30;
	float speed = 1.5;
	float gravity = 9.8;
	float maxY =20, minY=-20, maxX =20, minX =-20;
	int refreshRate = 30;
	float Pi = 3.1415926;
	bool isMoving = false;
	void display();
	void update();
};