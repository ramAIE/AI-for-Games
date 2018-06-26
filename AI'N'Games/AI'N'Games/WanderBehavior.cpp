#include "WanderBehavior.h"
#include "Agent.h"
#include <Bits.h>
WanderBehavior::WanderBehavior()
{
}

WanderBehavior::WanderBehavior(float wanderRadius, float wanderDistance, float wanderJitter)
{
	m_wanderRadius = wanderRadius;
	m_wanderDistance = wanderDistance;
	m_wanderJitter = wanderJitter;
	m_wanderTarget = Vector2(0, 0);

}

void WanderBehavior::update(Agent * agent, float deltaTime)
{
	Vector2 circleCenter = agent->velocity;
	circleCenter.normalise();
	circleCenter = circleCenter * m_wanderRadius;
}


WanderBehavior::~WanderBehavior()
{
}
