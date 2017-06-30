#pragma once
class IUpdatableObject {
public:
	virtual ~IUpdatableObject() {}
	virtual void start() = 0;
	virtual void update(const double & deltaTime) = 0;
	virtual void fixedUpdate(const double & fixedDeltaTime) = 0;
};