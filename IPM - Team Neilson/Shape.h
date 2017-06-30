#pragma once
#include<gl/glut.h>
#include <cmath>
#include <vector>
#include <iostream>
#include "Renderable.h"
#include "Utility.h"

 enum ShapeType {
	INVALID_SHAPE = -1,
	LINE_SHAPE = 0,
	CIRCLE_SHAPE = 1,
	CAPSULE_SHAPE = 2,
	RECTANGLE_SHAPE = 3,
	POLYGON_SHAPE = 3
};

class Shape : public Renderable, public Utility {
public:
	Shape();
	Shape(const Vector2 & center, ShapeType type);
	~Shape();
	void setWireframe(bool wireframe);
	void draw(Vector2 & origin, const double & rotation) override;
	void setColour(const double & r, const double & g, const double & b, const double & a);
	void setWireframeColour(const double & r, const double & g, const double & b);
	void setDrawStyle(const int & newDrawStyle);
	void setShouldDraw(const bool & shouldDraw);
	double getRadius();
	void calculateRadius();
	double getSquaredRadius();
	int vertexCount();
	ShapeType getShapeType();
	RenderType getRenderType() override;
	std::vector <Vector2> getTransformed();
	Vector2 getTransformedPosition();
	bool isTransformed();
protected:
	virtual void initialize() = 0;
	bool wireframe = false, transformSet = false, shouldDraw = true;
	void setRadius(double radius);
	std::vector <Vector2> vertices;
	std::vector <Vector2> transformed;
	Vector2 transformedCenter;
	double radius = 0, sqrRadius = 0, r = 0, g = 0, b = 0, a = 1, wR = 0.1, wG = 0.8, wB = 0.1;
	int drawStyle = GL_POLYGON;
	ShapeType type = INVALID_SHAPE;
};

