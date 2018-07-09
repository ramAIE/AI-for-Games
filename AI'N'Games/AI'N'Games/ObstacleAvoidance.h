#pragma once
#include "Decision.h"
class ObstacleAvoidance : public Decision
{
public:
	ObstacleAvoidance();
	ObstacleAvoidance(Agent * obstacle, float maxSeeAhead);
	virtual void MakeDecision(Agent* agent, float deltaTime);
	~ObstacleAvoidance();

private:
	float maxSeeAhead;
	Agent* obstacle;
	bool isColliding;
};

