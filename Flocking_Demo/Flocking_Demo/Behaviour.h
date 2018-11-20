#pragma once

#include "Agent.h"

enum eBehaviourResult {
	SUCCESS,
	FAILURE,
	RUNNING
};

class Behaviour {
public:
	Behaviour() {}
	virtual ~Behaviour() {}

	virtual eBehaviourResult update(Agent* agent, float deltaTime) = 0;
};

