#include "SteeringBehaviour.h"
#include "SteeringForce.h"
#include <iostream>

SteeringBehaviour::SteeringBehaviour() {
}


SteeringBehaviour::~SteeringBehaviour() {
}

void SteeringBehaviour::addForce(SteeringForce * force) {
	m_forces.push_back(force);
}

eBehaviourResult SteeringBehaviour::update(Agent * agent, float deltaTime) {
	Vector3 force = Vector3(0, 0, 0);

	for (auto f : m_forces) {
		Vector3 temp = f->getForce(agent);
		force = force + temp;
	}

	agent->AddForce(force);

	return eBehaviourResult::SUCCESS;
}
