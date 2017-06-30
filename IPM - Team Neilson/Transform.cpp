#include "Transform.h"
#include "Vector2.h"

Transform::Transform() : Component("Transform") {

}

Transform::~Transform() {

}

Vector2 Transform::getPosition() {
	return position;
}

void Transform::setPosition(const Vector2 & newPosition) {
	Vector2 toMove = newPosition - position;
	position = newPosition;
	for(unsigned int i = 0; i < children.size(); i++) {
		children[i]->setPosition(children[i]->getPosition() + toMove);
	}
}

Vector2 Transform::getRotation() {
	return forward;
}

void Transform::setRotation(const double & newRotation) {
	forward = Vector2(1, 0).rotatedInRadians(newRotation);
}

void Transform::setRotation(const Vector2 & newRotation) {
	forward = newRotation;
}

Vector2 Transform::getScale() {
	return scale;
}

void Transform::setScale(const Vector2 & newScale) {
	scale = newScale;
}

Vector2 Transform::getForward() {
	return forward;
}

Vector2 Transform::getRight() {
	return forward.copy().flip90(true);
}

void Transform::move(const Vector2 & toMove) {
	position += toMove;
	for(unsigned int i = 0; i < children.size(); i++) {
		children[i]->move(toMove);
	}
}

int Transform::getChildCount() {
	return children.size();
}

Transform* Transform::getChild(const unsigned int & index) {
	return index < children.size() ? children[index] : NULL;
}

void Transform::addChild(Transform * child) {
	children.push_back(child);
}

Transform* Transform::getParent() {
	return parent;
}

void Transform::setParent(Transform * newParent) {
	parent = newParent;
	parent->addChild(this);
}

void Transform::rotateInRadians(const double & angle) {
	forward.rotateInRadians(angle);
	for(auto i = children.begin(); i < children.end(); i++) {
		Transform * child = (*i);
		child->setPosition(position + (child->getPosition() - position).rotateInRadians(angle));
		child->rotateInRadians(angle);
	}
}

ComponentID Transform::getComponentID() {
	return TRANSFORM_COMPONENT;
}

void Transform::initialize() {
	position = Vector2(); forward = Vector2(1, 0); scale = Vector2::One;
}
