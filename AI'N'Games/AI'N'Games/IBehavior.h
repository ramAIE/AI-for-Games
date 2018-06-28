#pragma once
class Agent;
class IBehavior
{
public:
	IBehavior() {}
	virtual ~IBehavior() {}
	virtual void update(Agent* agent, float deltaTime) = 0;
};