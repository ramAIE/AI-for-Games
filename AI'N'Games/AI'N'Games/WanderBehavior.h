#pragma once
#include "IBehavior.h"
#include <Vector2.h>
class Agent;
class WanderBehavior : public IBehavior
{
public:
	WanderBehavior();
	WanderBehavior(float wanderRadius, float wanderDistance, float wanderJitter);
	virtual void update(Agent* agent, float deltaTime);
	~WanderBehavior();
private:
	float m_wanderRadius;
	float m_wanderDistance;
	float m_wanderJitter;
	Vector2 m_wanderTarget;
};

