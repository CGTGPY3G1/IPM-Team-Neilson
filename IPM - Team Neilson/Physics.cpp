#include "Physics.h"
#include "GameObject.h"
#include "Movement.h"

const double Physics::G = 6.67408 * pow(10.0, -11.0);

Physics::~Physics() {
}

void Physics::gravitateTowards(GameObject & object1, GameObject & object2) {
	Movement *movement1 = object1.getMovement(), *movement2 = object2.getMovement();
	if(movement1 && movement2) {
		// get the gravitational constant (6.67408 * 10.0^-11.0)
		double G = Physics::getGravitationalConstant();
		// get the objects positions
		Vector2 position1 = object1.getTransform()->getPosition(), position2 = object2.getTransform()->getPosition();
		// get the displacement and squared distance between the objects
		Vector2 displacement = (position2 - position1);
		double sqrDistance = displacement.squareMagnitude();
		// get the masses of the objects
		double m1 = movement1->getMass(), m2 = movement2->getMass();
		// calculate the amount of force to apply to the objects
		double force = G * ((m1 * m2) / sqrDistance);
		// create a vector for the force to apply from the normalized displacement vector
		// then scale it by the result of the force calculation 
		Vector2 forceToApply = displacement.normalized() * force;
		// apply the force to the objects Movement component in the relevant direction
		movement1->addForce(forceToApply);
		// apply the negative of that force to the other objects Movement
		movement2->addForce(-forceToApply);
	}
}