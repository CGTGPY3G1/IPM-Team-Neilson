#pragma once
#include "Component.h"

enum SpaceType {
	WORLD_SPACE = 0,
	LOCAL_SPACE = 1, 
	SAME_SPACE = 2
};
class Movement : public Component {
public:
	Movement();
	~Movement();
	void addForce(const Vector2 & force);
	void setMass(const double & newMass);
	double getMass();
	Vector2 getAcceleration();
	Vector2 getVelocity();
	void setVelocity(const Vector2 & newVelocity);
	double getSpeed();
	void fixedUpdate(const double & FixedDeltaTime) override;
	ComponentID getComponentID() override;
	void initialize() override;
	Vector2 toLocal(Vector2 point);
	Vector2 toWorld(Vector2 point);
private:
	Vector2 velocity, acceleration, combinedForce;
	double mass = 1, invertedMass = 1;
};

