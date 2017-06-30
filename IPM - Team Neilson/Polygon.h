#pragma once
#include "Shape.h"
#include <cstdarg>
class Poly : public Shape {
public:
	Poly(const Vector2 & center, const std::vector<Vector2> & points);

	Poly(const Vector2 & center, const unsigned int & noOfVerts, const Vector2 points...);
	~Poly();

private:
	void initialize() override;
};

Poly::Poly(const Vector2 & center, const std::vector<Vector2> & points) : Shape(center, POLYGON_SHAPE) {
	if(points.size() > 2) {
		vertices = points;
		initialize();
	}
}

Poly::~Poly() {
}

inline void Poly::initialize() {
	calculateRadius();
	initialized = true;
}


inline Poly::Poly(const Vector2 & center, const unsigned int & noOfVerts, const Vector2 points...) : Shape(center, POLYGON_SHAPE) {
	va_list vectors;
	va_start(vectors, points);
	vertices.push_back(points);
	for(unsigned int i = 0; i < noOfVerts-1; i++) {
		vertices.push_back(va_arg(vectors, Vector2));
	}
	va_end(vectors);
	initialize();
}
