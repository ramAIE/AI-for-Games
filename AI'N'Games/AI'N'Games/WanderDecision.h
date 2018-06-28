#pragma once
#include "Decision.h"
class WanderDecision : public Decision
{
public:
	WanderDecision();
	virtual void MakeDecision(Agent* agent, float deltaTime);
	~WanderDecision();
};

