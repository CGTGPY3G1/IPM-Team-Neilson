#pragma once
#include"Shape.h"

class Line : public Shape
{
public:
	Line();
	Line(const Vector2 & start, const Vector2 & end);
	~Line();
private:
	void initialize() override;
	Vector2 start, end;
};


