#pragma once
#include <vector>
#include "Vector2.h"
#include "Collider.h"
class CollisionManager {
public:
	CollisionManager();
	~CollisionManager();
	static bool checkCollision(Collider * collider1, Collider * collider2);
	static bool checkRadii(Vector2 & center1, const double & radius1, Vector2 & center2, const double & radius2);
	static bool pointInCircle(Vector2 & center, const double & radius, Vector2 & point);
	static void resolveCollisions(GameObject & object1, GameObject & object2);
};