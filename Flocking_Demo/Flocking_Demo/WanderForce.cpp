#include "WanderForce.h"

WanderForce::WanderForce() {
	m_wanderDistance = 0.0f;
	m_wanderRadius = 0.0f;
	m_wanderAngle = 0.0f;
}


WanderForce::~WanderForce() {
}

Vector3 WanderForce::getForce(Agent * agent) {
	Vector3 force = Vector3(0, 0, 0);
	if (agent->GetVelocity().m_x != 0 || agent->GetVelocity().m_y != 0) {
		// Calculating Circle's center
		Vector3 circleCenter = Vector3(0, 0, 0);
		// circle center is the clone of the agent's velocity vector
		// means, the circle will be in the same direction
		circleCenter = agent->GetVelocity();
		// normalized and scaled by distance value
		circleCenter.normalise();
		circleCenter = circleCenter * m_wanderDistance;

		// calculating displacement force
		Vector3 displacement = Vector3(0, -1, 0);
		displacement = displacement * m_wanderRadius;

		// Randomly change the vector direction by making it change it's current angle
		float length = displacement.magnitude();
		displacement.m_x = cosf(m_wanderAngle) * length;
		displacement.m_y = sinf(m_wanderAngle) * length;

		m_wanderAngle += rand() * 3.14f - 3.14f *  0.5f;

		// calculate the wander force
		force = circleCenter + displacement;
	}
	return force * 50.0f;
}
