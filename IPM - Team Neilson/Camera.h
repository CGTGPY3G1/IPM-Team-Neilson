#pragma once
#include "Vector2.h"
class Camera {
public:
	Camera(const double & width, const double & height);
	~Camera();
	void move(const double & x, const double & y);
	void move(const Vector2 & amount);
	Vector2 getPosition();
	void setPosition(const double & x, const double & y);
	void setPosition(const Vector2 & newPosition);
	double getX();
	double getY();
private:
	double x = 0, y = 0, z = -1, width, height, halfWidth, halfHeight;
	Vector2 position;
};


