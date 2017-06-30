#include "Collider.h"
#include "Shape.h"
#include "GameObject.h"

Collider::Collider() {
}

Collider::~Collider() {

}

Collider * Collider::setShape(Shape * shape) {
	this->shape = shape;
	this->shape->setWireframe(true);
	int sOrder = 100;
	this->shape->setSortOrder(sOrder);
	return this;
}

Shape * Collider::getShape() {
	return shape;
}

void Collider::update() {
	if(!addedToRenderer)
		addToRenderer();
}

ComponentID Collider::getComponentID() {
	return COLLIDER_COMPONENT;
}

void Collider::initialize() {
	if(!addedToRenderer) 
		addToRenderer();
}

void Collider::addToRenderer() {
	Renderer * r = gameObject->getRenderer();
	if(r && shape && !addedToRenderer) {
		r->addRenderable(shape);
		addedToRenderer = true;
	}
}

Collider * Collider::shouldRender(bool render) {
	shouldBeRendered = render;
	if(shape)
		shape->setShouldDraw(render);
	return this;
}

Collider * Collider::setRestitution(double restitution) {
	this->restitution = restitution;
	return this;
}

double Collider::getRestitution() {
	return restitution;
}
