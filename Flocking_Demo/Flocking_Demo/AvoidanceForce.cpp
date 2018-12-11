#include "AvoidanceForce.h"



AvoidanceForce::AvoidanceForce() {
}


AvoidanceForce::~AvoidanceForce() {
}

Vector3 AvoidanceForce::getForce(Agent * agent) {
	Vector3 force = Vector3(0, 0, 0);
	
	// get agent's current velocity
	Vector3 ahead = agent->GetLocalTransform()[2] + agent->GetVelocity();
	float distance = ahead.magnitude();

	// if the agent is moving
	if (distance > 0) {
		// iterate through all the obstacles
		for (auto o : m_circles) {
			// check if velocity of the agent intersects with obstacle
			if (o.IntersectsLine(ahead)) {
				force = force + (ahead - o.GetPosition());
			}
		}
	}

	return force * agent->GetSpeed();
}
