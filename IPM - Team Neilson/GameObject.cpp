#include"GameObject.h"
#include "Transform.h"
#include "Movement.h"
GameObject::GameObject() {
	init(Vector2(0.0, 0.0), Vector2(1.0, 0.0), getNewDefaultName());
}

GameObject::GameObject(const Vector2 & position, const Vector2 & rotation) {
	init(position, rotation, getNewDefaultName());
}

GameObject::GameObject(const Vector2 & position, const double & rotation) {
	init(position, Vector2(1.0, 0.0).rotatedInRadians(rotation), getNewDefaultName());
}

GameObject::GameObject(const Vector2 & position, const Vector2 & rotation, const std::string & name) {
	init(position, rotation, name);
}

GameObject::GameObject(const Vector2 & position, const double & rotation, const std::string & name) {
	init(position, Vector2(1.0, 0.0).rotatedInRadians(rotation), name);
}

Transform * GameObject::getTransform() {
	return transform;
}

Renderer * GameObject::getRenderer() {
	return renderer;
}

Movement * GameObject::getMovement() {
	return movement;
}

GameObject::~GameObject() {
}

void GameObject::addComponent(Component * toAdd) {
	if (toAdd->getComponentID() == RENDERER_COMPONENT) {
		if (!renderer) {
			renderer = (Renderer*)toAdd;
			componentManager.addComponent(toAdd);
		}
	}
	else if(toAdd->getComponentID() == TRANSFORM_COMPONENT) {
		if(!transform) {
			transform = (Transform*)toAdd;
			componentManager.addComponent(toAdd);
		}
	}
	else if(toAdd->getComponentID() == MOVEMENT_COMPONENT) {
		if(!movement) {
			movement = (Movement*)toAdd;
			componentManager.addComponent(toAdd);
		}
	}
	else {
		componentManager.addComponent(toAdd);
	}
	
}

void GameObject::start() {
}

void GameObject::update() {
	componentManager.update();
}

void GameObject::update(const double & deltaTime) {
	componentManager.update();
}

void GameObject::fixedUpdate(const double & fixedDeltaTime) {
	componentManager.fixedUpdate(fixedDeltaTime);
}

void GameObject::lateUpdate() {
	componentManager.lateUpdate();
}

void GameObject::render() {
	if (renderer)
		renderer->draw();
}

std::string GameObject::getName() {
	return name;
}

void GameObject::setName(std::string name) {
	this->name = name;
}

int GameObject::idCount = 0;
int GameObject::newObjectID() {
	return idCount++;
}

int GameObject::defaultNameId = 0;
std::string GameObject::getNewDefaultName() {
	return "GameObject " + (++defaultNameId);
}

void GameObject::init(const Vector2 & position, const Vector2 & rotation, const std::string & name) {
	objectID = newObjectID();
	componentManager = ComponentManager(this);
	addComponent(createComponent<Transform>());
	transform->setPosition(position); transform->setRotation(rotation);
	this->name = name;
}

bool operator<(const GameObject & a, const GameObject & b) {
	if(a.renderer && b.renderer)
		return (a.renderer->getSortLayer() < b.renderer->getSortLayer());
	else if(a.renderer)
		return true;
	return false;
}

bool operator == (const GameObject & a, const GameObject & b) {
	return a.objectID == b.objectID;
}
