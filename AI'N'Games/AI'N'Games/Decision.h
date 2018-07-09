#pragma once
class Agent;
class Decision
{
public:
	Decision() {}
	virtual ~Decision() {}
	virtual void MakeDecision(Agent* agent, float deltaTime) = 0;
	virtual void update(Agent* agent, float deltaTime);
};

