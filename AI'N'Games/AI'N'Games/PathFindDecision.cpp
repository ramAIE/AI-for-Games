#include "PathFindDecision.h"
#include "Node.h"
#include "Agent.h"

PathFindDecision::PathFindDecision()
{
}

PathFindDecision::PathFindDecision(std::vector<Node*> target)
{
	// get the path
	m_target = target;
}

void PathFindDecision::MakeDecision(Agent * agent, float deltaTime)
{
	if (!m_target.empty()) {
		// grab the last node of the path
		m_nextNode = m_target.back();
		// find the distance (targetDist) between agent's position and the target node position
		Vector2 targetDist = m_nextNode->GetPosition() - agent->position;

		// find the length
		float length = targetDist.magnitude();

		// normalize the distance (targetDist) and apply some speed
		targetDist.normalise();
		targetDist = targetDist * 200.0f;

		// difference between the agent's velocity and the distance (targetDist)
		Vector2 steeringForce = targetDist - agent->velocity;

		// Apply the force to the agent's position
		agent->AddForce(steeringForce);

		// Check if the player has reached the target node
		if (length < 20.0f) {
			// remove the last node when the agent is close to the node
			m_target.pop_back();
		}
	}
}


PathFindDecision::~PathFindDecision()
{
}
