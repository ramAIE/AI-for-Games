#include "AlignmentForce.h"



AlignmentForce::AlignmentForce() : m_radius(0.0f) {
}


AlignmentForce::~AlignmentForce() {
}

Vector3 AlignmentForce::getForce(Agent * agent) {
	// agent's current position
	Vector3 currentPosition = agent->GetLocalTransform()[2];

	Vector3 force = Vector3(0, 0, 0);
	int neighbours = 0;

	for (auto b : m_boids) {
		if (b == agent) continue;

		Vector3 boidPos = b->GetLocalTransform()[2];

		Vector3 distance = currentPosition - boidPos;
		float length = distance.magnitude();

		// is this boid within the radius?
		if (length > 0 && length < m_radius) {
			Vector3 v = agent->GetVelocity();
			float distance = v.magnitude();
			if (distance > 0) {
				force = force + v;
				neighbours++;
			}
		}
	}

	if (neighbours > 0) {
		force.m_x = force.m_x / (neighbours) - agent->GetVelocity().m_x;
		force.m_y = force.m_y / (neighbours) - agent->GetVelocity().m_y;
		float d = force.magnitude();
		if (d > 0)
			force.normalise();
	}

	return force * agent->GetSpeed();
}
