#include "ComponentManager.h"
#include "Component.h"
ComponentManager::ComponentManager() {
}

ComponentManager::ComponentManager(GameObject * gameObject) {
	this->gameObject = gameObject;
}

ComponentManager::~ComponentManager() {

}

void ComponentManager::addComponent(Component * toAdd) {
	toAdd->setOwner(gameObject);
	toAdd->initialize();
	components.push_back(toAdd);
}

void ComponentManager::start() {
}

void ComponentManager::update() {
	for(list<Component*>::iterator i = components.begin(); i != components.end(); ++i) {
		if((*i)->getEnabled()) {
			(*i)->update();
		}
	}
}

void ComponentManager::update(double deltaTime) {
	for(list<Component*>::iterator i = components.begin(); i != components.end(); ++i) {
		if((*i)->getEnabled()) {
			(*i)->update(deltaTime);
		}
	}
}

void ComponentManager::fixedUpdate(double fixedDeltaTime) {
	for (list<Component*>::iterator i = components.begin(); i != components.end(); ++i) {
		if((*i)->getEnabled()) {
			(*i)->fixedUpdate(fixedDeltaTime);
		}
	}
}

void ComponentManager::lateUpdate() {
	for(list<Component*>::iterator i = components.begin(); i != components.end(); ++i) {
		if((*i)->getEnabled()) {
			(*i)->lateUpdate();
		}
	}
}
