#pragma once
#ifndef GAMEOBJECT
#define GAMEOBJECT
#include "ComponentManager.h"

class GameObject {
public:

	GameObject();
	GameObject(const Vector2 & position, const Vector2 & rotation);
	GameObject(const Vector2 & position, const double & rotation);
	GameObject(const Vector2 & position, const Vector2 & rotation, const std::string & name);
	GameObject(const Vector2 & position, const double & rotation, const std::string & name);
	Transform * getTransform();
	Renderer * getRenderer();
	Movement * getMovement();
	~GameObject();
	void addComponent(Component * toAdd);
	template<typename T>
	T * getComponent();
	template<typename T>
	std::list<T*> getComponents();
	template<typename T>
	static T * createComponent();
	virtual void start();
	virtual void update();
	virtual void update(const double & deltaTime);
	virtual void fixedUpdate(const double & fixedDeltaTime);
	virtual void lateUpdate();
	virtual void render();
	friend bool operator < (const GameObject & a, const GameObject & b);
	friend bool operator == (const GameObject & a, const GameObject & b);
	std::string getName();
	void setName(std::string name);
private:
	static int idCount, defaultNameId;
	static int newObjectID();
	int objectID;
	static std::string getNewDefaultName();
	Transform * transform;
	Renderer * renderer;
	Movement * movement;
	void init(const Vector2 & position, const Vector2 & rotation, const std::string & name);
	ComponentManager componentManager;
	std::string name;
};

template<typename T>
T * GameObject::getComponent() {
	return componentManager.getComponent<T>();
}

template<typename T>
std::list<T*> GameObject::getComponents() {
	return componentManager.getComponents<T>();
}

// Try to dynamically cast the a new object of the Type passed to a Component 
// Pointer
// if successful, dynamically cast back to original Type and return
// else, return NULL
template<typename T>
T * GameObject::createComponent() {
	Component * newComponent = dynamic_cast<Component *>(new T());
	if(newComponent) {
		return dynamic_cast<T*>(newComponent);
	}
	return NULL;
}

#endif


