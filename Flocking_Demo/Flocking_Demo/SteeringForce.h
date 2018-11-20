#pragma once
#include "Agent.h"
class SteeringForce {

public:
	SteeringForce() {}
	virtual ~SteeringForce() {}

	virtual Vector3 getForce(Agent* agent) = 0;
};