#include "SeekDecision.h"
#include "Agent.h"


SeekDecision::SeekDecision()
{
	target = nullptr;
}

SeekDecision::SeekDecision(Agent * target)
{
	this->target = target;
}


SeekDecision::~SeekDecision()
{
	//delete target;
}

void SeekDecision::MakeDecision(Agent * agent, float deltaTime)
{
	Vector2 desiredVel = target->position - agent->position;
	desiredVel.normalise();
	desiredVel = desiredVel * 50.0f;
	Vector2 force = desiredVel - agent->velocity;
	agent->AddForce(force);
}
