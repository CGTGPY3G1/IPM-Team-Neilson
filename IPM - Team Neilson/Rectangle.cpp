#include"Rectangle.h"

Rect::Rect() : Shape () {
}

Rect::Rect(const Vector2 & center, const double & width, const double & height) : Shape(center, RECTANGLE_SHAPE) {
	this->width = width; this->height = height;
	this->initialize();
}

Rect::~Rect() {
}

void Rect::initialize() {
	double halfWidth = width / 2, halfHeight = height / 2;
	vertices.push_back(Vector2(-halfWidth, halfHeight));
	vertices.push_back(Vector2(halfWidth, halfHeight));
	vertices.push_back(Vector2(halfWidth, -halfHeight));
	vertices.push_back(Vector2(-halfWidth, -halfHeight));
	calculateRadius();
	initialized = true;
}
