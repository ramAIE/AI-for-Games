#include "BooleanDecision.h"
#include "Agent.h"


BooleanDecision::BooleanDecision()
{
}

void BooleanDecision::MakeDecision(Agent * agent, float deltaTime)
{
	if (condition)
	{
		trueDecision->MakeDecision(agent, deltaTime);
	}
	else
	{
		falseDecision->MakeDecision(agent, deltaTime);
	}
}

bool BooleanDecision::CheckWithinRange(Agent * agent, Agent * target, float range)
{
	// find the distance between agent and target
	Vector2 distance = target->position - agent->position;
	float length = distance.magnitude();
	// if the distance is less than the range the condition is true
	if (length < range)
		condition = true;
	// else the condition is false
	else
		condition = false;

	return condition;
}


BooleanDecision::~BooleanDecision()
{
	delete trueDecision;
	delete falseDecision;
}
