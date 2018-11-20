#pragma once

#include "Behaviour.h"

class SteeringForce;
class SteeringBehaviour : public Behaviour {
public:
	SteeringBehaviour();
	~SteeringBehaviour();

	void addForce(SteeringForce* force);
	virtual eBehaviourResult update(Agent* agent, float deltaTime);

protected:
	std::vector<SteeringForce*> m_forces;

};

