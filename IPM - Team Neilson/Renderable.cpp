#include"Renderable.h"

int Renderable::rIdCounter = 0;

Renderable::Renderable() {
	enabled = true;
	renderableID = getNewID();
}

Renderable::~Renderable() {
}

Vector2 Renderable::getPosition() {
	return center;
}

void Renderable::setPosition(const Vector2 & newCenter) {
	center = newCenter;
}

int Renderable::getRenderableID() {
	return renderableID;
}

void Renderable::setEnabled(bool & enabled) {
	this->enabled = enabled;
}

void Renderable::setSortOrder(int & sortOrder) {
	this->sortOrder = sortOrder;
}

int Renderable::getSortOrder() {
	return sortOrder;
}

int Renderable::getNewID() {
	return ++rIdCounter;
}

bool operator<(const Renderable & a, const Renderable & b) {
	return (a.sortOrder <= b.sortOrder);
}

bool operator==(const Renderable & a, const Renderable & b) {
	return (a.renderableID == b.renderableID);
}

bool operator!=(const Renderable & a, const Renderable & b) {
	return !(a == b);
}
