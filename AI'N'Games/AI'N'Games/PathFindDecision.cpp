#include "PathFindDecision.h"



PathFindDecision::PathFindDecision()
{
}

PathFindDecision::PathFindDecision(std::list<Node*> target)
{
}

void PathFindDecision::MakeDecision(Agent * agent, float deltaTime)
{
	// find the distance (targetDist) between agent's position and the target node position

	// normalize the distance (targetDist) and apply some speed

	// difference between the agent's velocity and the distance (targetDist)

	// Apply the force to the agent's position

	// Check if the player has reached the target node
		// switch to the next node
}


PathFindDecision::~PathFindDecision()
{
}
