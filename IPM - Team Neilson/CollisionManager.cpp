#include "CollisionManager.h"
#include "Shape.h"
#include <cmath>
#include "GameObject.h"
#include "Movement.h"
#include "Transform.h"
#include "Collider.h"
#include "MyMath.h"
#include <iomanip>
CollisionManager::CollisionManager() {
}

CollisionManager::~CollisionManager() {
}

bool CollisionManager::checkCollision(Collider * collider1, Collider * collider2) {
	bool result = false;
	Shape * s1 = collider1->getShape(), *s2 = collider2->getShape();
	if(s1 && s2) {
		Vector2 center1 = collider1->getGameObject()->getTransform()->getPosition(), center2 = collider2->getGameObject()->getTransform()->getPosition();
		result = checkRadii(center1, s1->getRadius(), center2, s2->getRadius());
	}
	return result;
}

// should ignore resting contacts
bool CollisionManager::checkRadii(Vector2 & center1, const double & radius1, Vector2 & center2, const double & radius2) {
	double sqrRadius = radius1 + radius2;
	sqrRadius *= sqrRadius;
	double sqrDistance = (center1 - center2).squareMagnitude();
	if(sqrRadius > sqrDistance)
		return true;
	return false;
}

bool CollisionManager::pointInCircle(Vector2 & center, const double & radius, Vector2 & point) {
	return (center - point).squareMagnitude() < radius * radius;
}

void CollisionManager::resolveCollisions(GameObject & object1, GameObject & object2) {
	Collider *c1 = object1.getComponent<Collider>(), *c2 = object2.getComponent<Collider>();
	if(c1 && c2) { // if both objects have colliders
		if(checkCollision(c1, c2)) { // if colliding
			// get objects Movement and Transform Components
			Movement *movement1 = object1.getMovement(), *movement2 = object2.getMovement();
			Transform *t1 = object1.getTransform(), *t2 = object2.getTransform();
			// get the positions and collision normal
			Vector2 position1 = t1->getPosition(), position2 = t2->getPosition();
			Vector2 normal = (position2 - position1).normalized();
			// get the initial velocities
			Vector2 v1 = movement1->getVelocity(), v2 = movement2->getVelocity();
			// get the mass and radii of the objects
			double m1 = movement1->getMass(), m2 = movement2->getMass();
			double aMass = m1 + m2;
			double rad1 = c1->getShape()->getRadius(), rad2 = c2->getShape()->getRadius();
			double combinedRad = rad1 + rad2;
			// if 1 object is the Large Mass move the 
			// other to just outside of its radius, else
			// move both
			if(strcmp(object1.getName().c_str(), "LargeMass") == 0) {
				t2->setPosition(position1 + (normal*combinedRad));
			}
			else if(strcmp(object2.getName().c_str(), "LargeMass") == 0) {
				t1->setPosition(position2 - (normal*combinedRad));
			}
			else {
				Vector2 pointOfCollision = ((position1*rad2) + (position2*rad1)) / combinedRad;
				t1->setPosition(pointOfCollision - normal * rad1);
				t2->setPosition(pointOfCollision + normal * rad2);
			}
			// get the angle of the normal vector
			double angle = normal.angleInRadians();
			v1 = movement1->getVelocity(), v2 = movement2->getVelocity();
			// rotate the colliding velocities to turn the collision into a 1D problem
			v1.rotateInRadians(-angle); v2.rotateInRadians(-angle);
			// calculate the post-collision velocities using the rotated velocities
			double newX1 = ((v1.x * (m1 - m2)) + (v2.x * 2.0 * m2)) / aMass;
			double newX2 = ((v1.x * 2.0 * m1) + (v2.x * (m2 - m1))) / aMass;
			// set the new x components
			v1.x = newX1; v2.x = newX2;
			v1.rotateInRadians(angle); v2.rotateInRadians(angle);
			// Get the current kinetic energy in the system.
			double ke1 = ((m1 / 2) * movement1->getVelocity().squareMagnitude()), ke2 = ((m2 / 2) * movement2->getVelocity().squareMagnitude());
			double totalKineticEnergy = ke1 + ke2;
			// set the new velovities of the objects
			movement1->setVelocity(v1); movement2->setVelocity(v2);
			// Get the new kinetic energy in the system.
			//double nke1 = ((m1 / 2) * movement1->getVelocity().squareMagnitude()), nke2 = ((m2 / 2) * movement2->getVelocity().squareMagnitude());
			//double newKineticEnergy = nke1 + nke2;
			// Calculate the energy lost
			//double energyLoss = abs(totalKineticEnergy - newKineticEnergy);
			// Prints kinetic energy loss to console with precision of 3 decimal places to account for multiple
			// levels of imprecision during a relatively large number of calculations using large floating point numbers.
			// Given that the masses of the objects are generally in millions up to quintillions of Kilograms and velocities  
			// can be in hundreds or thousands of metres per second, kinetic enery loss of a few Millijoules can be expected.
			//cout << fixed << setprecision(3) << "\n Total" << "\n Before Collision: " << totalKineticEnergy << "\n After Collision: " << newKineticEnergy << "\n Kinetic Energy Lost: "  << energyLoss << "\n";
			//cout << fixed << setprecision(3) << " "<<object1.getName() << "\n Before Collision: " << ke1 << "\n After Collision: " << nke1 << "\n " << object2.getName() << "\n Before Collision : " << ke2 << "\n After Collision : " << nke2 << "\n";
		}
	}
}

