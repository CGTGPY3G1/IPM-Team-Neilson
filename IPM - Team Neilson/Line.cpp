#include"Line.h"

Line::Line() {
}

Line::Line(const Vector2 & start, const Vector2 & end) : Shape(start + ((end - start) / 2), LINE_SHAPE) {
	this->start = start; this->end = end;
	initialize();
}

Line::~Line() {
}

void Line::initialize() {
	vertices.push_back(start - center);
	vertices.push_back(end - center);
	setRadius(vertices[0].magnitude());
	drawStyle = GL_LINES;
	initialized = true;
}


