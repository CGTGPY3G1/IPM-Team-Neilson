#pragma once
#ifndef TRANSFORM
#define TRANSFORM
#include<vector>
#include "Component.h"

class Transform : public Component {
public:
	Transform();
	~Transform();
	Vector2 getPosition();
	void setPosition(const Vector2 & newPosition);
	Vector2 getRotation();
	void setRotation(const double & newRotation);
	void setRotation(const Vector2 & newRotation);
	Vector2 getScale();
	void setScale(const Vector2 & newScale);
	Vector2 getForward();
	Vector2 getRight();
	void move(const Vector2 & toMove);
	int getChildCount();
	Transform *getChild(const unsigned int & index);
	void addChild(Transform * child);
	Transform* getParent();
	void setParent(Transform * newParent);
	void rotateInRadians(const double & angle);
	ComponentID getComponentID() override;
	void initialize() override;
private:
	Vector2 position, forward, scale;
	Transform * parent;
	std::vector<Transform*> children;
};

#endif

