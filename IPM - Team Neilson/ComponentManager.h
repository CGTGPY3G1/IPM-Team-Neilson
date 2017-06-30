#pragma once
#ifndef COMPONENT_MANAGER
#define COMPONENT_MANAGER
#include "Component.h"
#include <iostream>
#include <list>
#include "Transform.h"
#include "Renderer.h"
#include "Movement.h"
#include <typeinfo>
class GameObject;

class ComponentManager {
public:
	ComponentManager();
	ComponentManager(GameObject * gameObject);
	~ComponentManager();
	template<typename T>
	T * getComponent();
	template<typename T>
	std::list<T*> getComponents();
	void addComponent(Component * toAdd);
	void start();
	void update();
	void update(double deltaTime);
	void fixedUpdate(double fixedDeltaTime);
	void lateUpdate();
private:
	int ownerID = 0;
	std::list<Component*> components;
	GameObject * gameObject;
};


template<typename T>
T * ComponentManager::getComponent() {
	// try to dynamically cast each component to the requested type 
	for(std::list<Component*>::iterator i = components.begin(); i != components.end(); ++i) {
		T * t = dynamic_cast<T*>(*i);
		if(t)
			return t; // if successful return the component
	}

	return NULL;
}

template<typename T>
std::list<T*> ComponentManager::getComponents() {
	std::list<T*> toReturn;
	// try to dynamically cast each component to the requested type
	for(std::list<Component*>::iterator i = components.begin(); i != components.end(); ++i) {
		T * t = dynamic_cast<T*>(*i);
		if(t)
			toReturn.push_back(t); // if successful add to the list

	}	
	return toReturn;
}

#endif