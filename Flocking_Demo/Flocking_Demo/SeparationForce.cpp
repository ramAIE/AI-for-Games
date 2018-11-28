#include "SeparationForce.h"



SeparationForce::SeparationForce() {
	m_radius = 0.0f;
}


SeparationForce::~SeparationForce() {
}

Vector3 SeparationForce::getForce(Agent * agent) {
	// agent's current position 
	Vector3 currentPosition = agent->GetLocalTransform()[2];

	Vector3 force = Vector3(0, 0, 0);
	int neighbours = 0;

	for (auto b : m_boids) {
		if (b == agent) continue;

		Vector3 boidPos = b->GetLocalTransform()[2];

		Vector3 distance = currentPosition - boidPos;
		float length = distance.magnitude();

		if (length > 0 && length < m_radius) {
			distance.normalise();
			neighbours++;

			force = force + distance;
		}
	}

	if (neighbours > 0) {
		force = force / neighbours;
	}

	return force * 500.0f;
}
