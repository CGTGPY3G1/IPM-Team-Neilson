#pragma once
#include "Shape.h"
#include "MyMath.h"

class Capsule : public Shape
{
public:
	Capsule();
	Capsule(const Vector2 & center, const double & width, const double & height, const double & radius, const bool & vertical, const int & verts);
	~Capsule();
private:
	void initialize() override;
	double width, height;
	bool vertical;
};

