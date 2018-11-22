#include "CohesionForce.h"
#include <iostream>


CohesionForce::CohesionForce() {
	m_radius = 0.0f;
}


CohesionForce::~CohesionForce() {
}

Vector3 CohesionForce::getForce(Agent * agent) {
	// agent's current position
	Vector3 currentPosition = agent->GetLocalTransform()[2];

	Vector3 force = Vector3(0, 0, 0);
	int neighbours = 0;

	for (auto b : m_boids) {
		if (agent == b) continue;

		Vector3 boidPos = b->GetLocalTransform()[2];

		Vector3 distance = currentPosition - boidPos;
		float length = distance.magnitude();

		if (length > 0 && length < m_radius) {
			neighbours++;
			force = force + boidPos;
		}
	}

	if (neighbours > 0) {
		force = force / neighbours - currentPosition;
		force.normalise();
	}

	return force;
}
