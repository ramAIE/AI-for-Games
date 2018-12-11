#pragma once
#include "SteeringForce.h"
#include "Circle.h"
class AvoidanceForce : public SteeringForce {
public:
	AvoidanceForce();
	~AvoidanceForce();

	void AddCircleObstacle(Circle circle){
		m_circles.push_back(circle);
	}

	virtual Vector3 getForce(Agent* agent);
private:
	std::vector<Circle> m_circles;
};

