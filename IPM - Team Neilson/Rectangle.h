#pragma once
#include "Shape.h"

class Rect : public Shape
{
public:
	Rect();
	Rect(const Vector2 & center, const double & width, const double & height);
	~Rect();
private:
	void initialize() override;
	double width, height, halfWidth, halfHeight;
	bool vertical;
};

