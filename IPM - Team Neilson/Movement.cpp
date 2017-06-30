#include "Movement.h"
#include"Transform.h"
#include "GameObject.h"
#include"Vector2.h"

Movement::Movement() : Component("Movement") {
	
}

Movement::~Movement() {
}

void Movement::addForce(const Vector2 & force) {
	combinedForce += force;
}

// set the mass and its inverse, this to replace division with multiplication in the 
// subsequent equations
void Movement::setMass(const double & newMass) {
	mass = newMass;
	invertedMass = newMass <= 0 ? 0.0 : 1.0 / newMass;
}

double Movement::getMass() {
	return mass;
}

Vector2 Movement::getAcceleration() {
	return acceleration;
}

Vector2 Movement::getVelocity() {
	return velocity;
}

void Movement::setVelocity(const Vector2 & newVelocity) {
	velocity = newVelocity;
}

double Movement::getSpeed() {
	return velocity.magnitude();
}

void Movement::fixedUpdate(const double & fixedDeltaTime) {
	// calculate the acceleration vector from the combined force vector 
	acceleration = combinedForce*invertedMass;
	// calculates the new velocity 
	Vector2 newVelocity = velocity + acceleration * fixedDeltaTime;
	// set the new velocity to the average if it and the new one
	newVelocity = (velocity + newVelocity) / 2;
	acceleration = newVelocity - velocity;
	velocity = newVelocity;
	// move the object using the new velocity 
	Transform* transform = gameObject->getTransform();
	transform->move(velocity * fixedDeltaTime);
	// reset the combinedForce variable
	combinedForce.set(0.0, 0.0);
}

ComponentID Movement::getComponentID() {
	return MOVEMENT_COMPONENT;
}

void Movement::initialize() {
	mass = 1.0; invertedMass = 1.0;
	velocity = Vector2(); combinedForce = Vector2();
}

Vector2 Movement::toLocal(Vector2 point) {
	return point - gameObject->getTransform()->getPosition();
}

Vector2 Movement::toWorld(Vector2 point) {
	return point + gameObject->getTransform()->getPosition();
}
