#include "Decision.h"
#include "Agent.h"

void Decision::update(Agent * agent, float deltaTime)
{
	MakeDecision(agent, deltaTime);
}
