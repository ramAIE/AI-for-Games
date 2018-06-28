#pragma once
#include "Decision.h"
class SeekDecision : public Decision
{
public:
	SeekDecision();
	SeekDecision(Agent* target);
	~SeekDecision();

	virtual void MakeDecision(Agent* agent, float deltaTime);
private:
	Agent * target;
};

