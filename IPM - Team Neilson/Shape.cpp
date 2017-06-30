#include "Shape.h"
#include <Windows.h>
Shape::Shape() {
}

Shape::Shape(const Vector2 & center, ShapeType type) : Utility(), Renderable() {
	this->center = center; this->type = type;
}

Shape::~Shape() {
}

void Shape::setWireframe(bool wireframe) {
	this->wireframe = wireframe;
	setDrawStyle(GL_LINE_LOOP);
}

void Shape::draw(Vector2 &origin, const double & rotation) {
	if (initialized && enabled) {
		transformed.clear();
		glDisable(GL_TEXTURE_2D);
		if (wireframe) {
			glColor3d(wR, wG, wB); 
		}
		else {
			glColor4d(r, g, b, 1.0);
		}	
		
		glBegin(drawStyle);
		Vector2 position;
		for(int index = 0; index < vertexCount(); index++) {
			position = origin +  (rotation != 0 ? (center + vertices[index]).rotatedInRadians(rotation) : (center + vertices[index]));
			if(shouldDraw)
				glVertex2d (position.x, position.y);
			transformed.push_back(position);
			transformedCenter = origin + (rotation != 0 ? center.rotatedInRadians(rotation) : center);
		}
		if(!transformSet)
			transformSet = true;
		glEnd();
	}
}

void Shape::setColour(const double & r, const double & g, const double & b, const double & a) {
	this->r = r; this->g = g; this->b = b; this->a = a;
}

void Shape::setWireframeColour(const double & r, const double & g, const double & b) {
	wR = r; wG = g; wB = b;
}

void Shape::setDrawStyle(const int & newDrawStyle) {
	if (drawStyle <= GL_POLYGON)
		drawStyle = newDrawStyle;
}

void Shape::setShouldDraw(const bool & shouldDraw) {
	this->shouldDraw = shouldDraw;
}

double Shape::getRadius() {
	return radius;
}

void Shape::calculateRadius() {
	unsigned int noOfVerts = vertices.size();
	double length = 0.0;
	for(unsigned int i = 0; i < noOfVerts; i++) {
		double sqrMagnitude = vertices[i].squareMagnitude();
		if(sqrMagnitude > length)
			length = sqrMagnitude;
	}
	setRadius(sqrt(length));
}

double Shape::getSquaredRadius() {
	return sqrRadius;
}

int Shape::vertexCount() {
	return vertices.size();
}

ShapeType Shape::getShapeType() {
	return type;
}

RenderType Shape::getRenderType() {
	return RENDER_SHAPE;
}

void Shape::setRadius(double radius) {
	this->radius = radius; sqrRadius = radius * radius;
}

std::vector<Vector2> Shape::getTransformed() {
	return transformed;
}

Vector2 Shape::getTransformedPosition() {
	return transformedCenter;
}

bool Shape::isTransformed() {
	return transformSet;
}
