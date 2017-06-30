#include "Capsule.h"
int xverts = 0;
Capsule::Capsule() {
}

Capsule::Capsule(const Vector2 & center, const double & width, const double & height, const double & radius, const bool & vertical, const int & verts) : Shape(center, CAPSULE_SHAPE) {
	this->width = width; this->height = height; this->radius = radius; this->vertical = vertical; xverts = verts;
	this->initialize();
}

Capsule::~Capsule() {
}

void Capsule::initialize() {
	double pi = MyMath::pi(), tau = MyMath::tau(), increment = tau / xverts;
	double halfWidth = width / 2, halfHeight = height / 2;
	int index = 0;
	double x = 0.0, y = 0.0;
	double rad = 0;
	if (vertical) {
		y -= halfHeight;
		for(double angle = pi; angle < tau; angle += increment) {
			vertices.push_back(Vector2(x + cos(angle) * halfWidth, y + sin(angle) * radius));
		}
		
		y += height;
		for(double angle = 0.0; angle < pi; angle += increment) {
			vertices.push_back(Vector2(x + cos(angle) * halfWidth, y + sin(angle) * radius));
		}
		rad = halfHeight;
	}
	else {
		x -= halfWidth;
		for (double angle = pi / 2; angle < pi+ (pi / 2); angle += increment) {
			vertices.push_back(Vector2(x + cos(angle) * radius, y + sin(angle) * halfHeight));
		}
		x += width;
		for (double angle = (pi / 2) + pi; angle < tau + (pi / 2); angle += increment) {
			vertices.push_back(Vector2(x + cos(angle) * radius, y + sin(angle) * halfHeight));
		}
		rad = halfWidth;
	}
	setRadius(radius + rad);
	initialized = true;
}