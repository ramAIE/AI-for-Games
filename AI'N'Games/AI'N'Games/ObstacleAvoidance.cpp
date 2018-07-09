#include "ObstacleAvoidance.h"
#include "Agent.h"
#include <math.h>

ObstacleAvoidance::ObstacleAvoidance()
{
	obstacle = nullptr;
	isColliding = false;
}

ObstacleAvoidance::ObstacleAvoidance(Agent * obstacle, float maxSeeAhead)
{
	this->obstacle = obstacle;
	this->maxSeeAhead = maxSeeAhead;
	isColliding = false;
}


ObstacleAvoidance::~ObstacleAvoidance()
{
}

void ObstacleAvoidance::MakeDecision(Agent * agent, float deltaTime)
{
	Vector2 ahead = agent->position + agent->velocity.normalised() * maxSeeAhead;
	float distance = sqrtf((ahead.m_x - obstacle->GetCirclePos().m_x) * (ahead.m_x - obstacle->GetCirclePos().m_x) + 
								(ahead.m_y - obstacle->GetCirclePos().m_y) * (ahead.m_y - obstacle->GetCirclePos().m_y));
	Vector2 avoidanceForce = ahead - obstacle->GetCirclePos();
	avoidanceForce = avoidanceForce.normalised() * 10.0f;
	if (distance <= obstacle->GetCircleRadius())
	{
		isColliding = true;
	}
	if (isColliding)
		agent->AddForce(avoidanceForce);

}
