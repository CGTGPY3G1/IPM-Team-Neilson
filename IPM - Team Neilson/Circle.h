#pragma once
#include "Shape.h"
#include "MyMath.h"
class Circle : public Shape
{
public:
	Circle();
	Circle(const Vector2 & center, const double & radius);
	~Circle();
private:
	void initialize() override;
};
