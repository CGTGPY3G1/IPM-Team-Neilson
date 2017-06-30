#pragma once
#ifndef COMPONENT
#define COMPONENT
#include"Vector2.h"
#include "IUpdatableObject.h"
#include <string>
enum ComponentID
{
	INVALID_COMPONENT = -1,
	TRANSFORM_COMPONENT = 0,
	RENDERER_COMPONENT = 1,
	MOVEMENT_COMPONENT = 2,
	WHEEL_COMPONENT = 3,
	ENGINE_COMPONENT = 4,
	CAR_COMPONENT = 5,
	AUDI_COMPONENT = 6,
	COLLIDER_COMPONENT = 7,
	TRACKER_COMPONENT = 8
};


class GameObject;
class Component : public IUpdatableObject {
public:
	Component();
	Component(const bool & enabled);
	Component(const bool & enabled, const std::string & name);
	Component(const std::string & name);
	Component(GameObject * gameObject, const bool & enabled);
	Component(GameObject * gameObject, const bool & enabled, const std::string & name);
	Component(GameObject * gameObject, const std::string & name);
	virtual ~Component();
	virtual ComponentID getComponentID() = 0;
	void setEnabled(const bool &enabled);
	bool getEnabled();
	template<class T>
	bool operator == (T &other);
	void setOwner(GameObject * gameObject);
	int getCompID();
	std::string getName();
	void setName(std::string name);
	GameObject * getGameObject();
	virtual void start();
	virtual void update();
	virtual void update(const double & deltaTime);
	virtual void fixedUpdate(const double & FixedDeltaTime);
	virtual void lateUpdate();
	virtual void initialize() = 0;
protected:
	bool enabled = false;
	std::string name;
	int ownerID, compID;
	void init(const bool & enabled, const std::string & name);
	GameObject * gameObject;
};

#endif
