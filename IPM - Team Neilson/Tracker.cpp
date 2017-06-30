#include "Tracker.h"
#include "Transform.h"
#include "Movement.h"
#include "GameObject.h"
#include <iomanip>

Tracker::Tracker() : Component("Tracker") {
}

Tracker::~Tracker() {
}

void Tracker::fixedUpdate(const double & fixedDeltaTime) {
	time += fixedDeltaTime;
	timeSinceTrack += fixedDeltaTime;
	if(timeSinceTrack >= frequency) {
		createData();
		timeSinceTrack -= frequency;
		if(frequency * data.size() > timeToTrack)
			data.pop_front();
	}
}

ComponentID Tracker::getComponentID() {
	return TRACKER_COMPONENT;
}

void Tracker::initialize() {
	createData();
}

double Tracker::getFrequency() {
	return frequency;
}

void Tracker::setFrequency(const double & frequency) {
	this->frequency = frequency;
}

double Tracker::getTimeToTrack() {
	return timeToTrack;
}

void Tracker::setTimeToTrack(const double & time) {
	timeToTrack = time;
}

std::list<GraphData> Tracker::getGraphData() {
	return data;
}

void Tracker::setTarget(Transform * newTarget) {
	target = newTarget;
}

void Tracker::createData() {
	GraphData gd = GraphData();
	Transform * transform = gameObject->getTransform();
	if(transform)
		gd.position = transform->getPosition();
	Movement * movement = gameObject->getMovement();
	if(movement) {
		gd.velocity = movement->getVelocity();
		gd.acceleration = movement->getAcceleration() * 50;// (data.size() > 0) ? (gd.velocity - (data.back()).velocity) : gd.velocity;
	}
	if(target)
		gd.distance = (target->getPosition() - gameObject->getTransform()->getPosition()).magnitude();
	else 
		gd.distance = 0;
	gd.time = time;
	cout << fixed << setprecision(10) << "\nName = " << gameObject->getName() << "\nTime = " << time << "\nPosition = " << gd.position << "\nVelocity = " << gd.velocity << "\nMagnitude = " << gd.velocity.magnitude() << "\nAcceleration = " << gd.acceleration << "\nMagnitude = " << gd.acceleration.magnitude() << "\nDistance = " << gd.distance << "\n";
	data.push_back(gd);
}
