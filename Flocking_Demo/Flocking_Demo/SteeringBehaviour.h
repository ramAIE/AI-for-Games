#pragma once

#include "Behaviour.h"
#include "SteeringForce.h"

class SteeringBehaviour : public Behaviour {
public:
	SteeringBehaviour();
	~SteeringBehaviour();

	void addForce(SteeringForce* force, float weight = 1.0f);
	void setWeight(SteeringForce* force, float weight);
	virtual eBehaviourResult update(Agent* agent, float deltaTime);

protected:
	std::vector<WeightedForce> m_forces;

};

