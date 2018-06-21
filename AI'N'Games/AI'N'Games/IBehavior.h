#pragma once
class Agent;
class IBehavior
{
public:
	virtual void update(Agent* agent, float deltaTime) = 0;
};