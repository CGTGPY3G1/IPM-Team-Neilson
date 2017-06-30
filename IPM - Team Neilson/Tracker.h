#pragma once
#include "Component.h"
#include <list>
struct GraphData {
	Vector2 position, velocity, acceleration;
	double time, distance;
};
class Transform;
class Tracker : public Component {
public:
	Tracker();
	~Tracker();
	void fixedUpdate(const double & fixedDeltaTime) override;
	ComponentID getComponentID() override;
	void initialize() override;
	double getFrequency();
	void setFrequency(const double & frequency);
	double getTimeToTrack();
	void setTimeToTrack(const double & time);
	std::list<GraphData> getGraphData();
	void setTarget(Transform * newTarget);
private:
	void createData();
	double timeToTrack = 10.0, time = 0.0, frequency = 1.0, timeSinceTrack = 0.0;
	std::list<GraphData> data;
	Transform * target;
};