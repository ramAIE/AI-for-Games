#pragma once
#include "Decision.h"
class BooleanDecision : public Decision
{
public:
	BooleanDecision();
	virtual void MakeDecision(Agent* agent, float deltaTime);
	bool CheckWithinRange(Agent* agent, Agent* target, float range);
	~BooleanDecision();

	Decision* trueDecision;
	Decision* falseDecision;
	bool condition;

};

