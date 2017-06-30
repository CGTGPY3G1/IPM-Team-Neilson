#pragma once
#include "Component.h"
enum ColliderType{
	COLLIDER_TYPE_NOT_SET = 0,
	CIRCLE_COLLIDER = 1,
	POLYGON_COLLIDER = 2
};
class Shape;
class Collider : public Component {
public:
	Collider();
	~Collider();
	Collider * setShape(Shape * shape);
	Shape * getShape();
	void update() override;
	ComponentID getComponentID() override;
	void initialize() override;
	void addToRenderer();
	Collider * shouldRender(bool render);
	Collider * setRestitution(double restitution);
	double getRestitution();
private:
	Shape * shape;
	bool addedToRenderer = false, shouldBeRendered = true;
	double restitution = 1;
};