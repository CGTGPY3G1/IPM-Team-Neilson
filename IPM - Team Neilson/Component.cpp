#include "Component.h"
#include "GameObject.h"
#include "IDManager.h"

Component::Component() {
	init(true, "Generic GameObject");
}

Component::Component(const bool & enabled) {
	init(enabled, "Generic GameObject");
}

Component::Component(const bool & enabled, const std::string & name) {
	init(enabled, name);
}

Component::Component(const std::string & name) {
	init(true, name);
}

Component::Component(GameObject * gameObject, const bool & enabled) {
	this->gameObject = gameObject;
	init(enabled, "Generic GameObject");
}

Component::Component(GameObject * gameObject, const bool & enabled, const std::string & name) {
	this->gameObject = gameObject;
	init(enabled, name);
}

Component::Component(GameObject * gameObject, const std::string & name) {
	this->gameObject = gameObject;
	init(true, name);
}

Component::~Component() {
}

void Component::setEnabled(const bool & enabled) {
	if (this->enabled != enabled) {
		this->enabled = enabled;
	}
}

bool Component::getEnabled() {
	return enabled;
}

void Component::setOwner(GameObject * gameObject) {
	this->gameObject = gameObject;
}

int Component::getCompID() {
	return compID;
}

std::string Component::getName() {
	return name;
}

void Component::setName(std::string name) {
	this->name = name;
}

GameObject * Component::getGameObject() {
	return gameObject;
}

void Component::start() {
}

void Component::update() {
}

void Component::update(const double & deltaTime) {
}

void Component::fixedUpdate(const double & fixedDeltaTime) {
}

void Component::lateUpdate() {
}

void Component::init(const bool & enabled, const std::string & name) {
	this->gameObject = gameObject; this->name = name;
	setEnabled(enabled);
	compID = IDManager::getNewCompID();
}

template<class T>
bool Component::operator==(T &other) {
	if (typeid(this) == typeid(other)) {
		if (((Component)other).compID == compID)
			return true;
	}
	return false;
}
