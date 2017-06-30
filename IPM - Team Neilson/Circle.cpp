#include "Circle.h"

Circle::Circle() {
}

Circle::Circle(const Vector2 & center, const double & radius) : Shape(center, CIRCLE_SHAPE) {
	setRadius(radius);
	this->initialize();
}

Circle::~Circle() {
}

void Circle::initialize() {
	int noOfVertices = 30;
	double tau = MyMath::tau(), increment = tau / noOfVertices;
	int index = 0;
	for (double angle = 0.0; angle < tau; angle += increment, index++) {
		vertices.push_back(Vector2(cos(angle)*radius, sin(angle)*radius));
	}
	initialized = true;
}
