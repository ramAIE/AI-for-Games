#include "SteeringBehaviour.h"
#include "SteeringForce.h"
#include <iostream>

SteeringBehaviour::SteeringBehaviour() {
}


SteeringBehaviour::~SteeringBehaviour() {
}

void SteeringBehaviour::addForce(SteeringForce* force, float weight) {
	WeightedForce wf;
	wf.force = force;
	wf.weight = weight;
	m_forces.push_back(wf);
}

void SteeringBehaviour::setWeight(SteeringForce * force, float weight) {
	for (auto &wf : m_forces) {
		if (wf.force == force) {
			wf.weight = weight;
		}
	}
}

eBehaviourResult SteeringBehaviour::update(Agent * agent, float deltaTime) {
	Vector3 force = Vector3(0, 0, 0);

	Vector3 velocity = Vector3(0,0,0);

	for (auto &f : m_forces) {
		Vector3 temp = f.force->getForce(agent);
		force = force + temp * f.weight;
	}
	agent->AddForce(force * deltaTime);

	return eBehaviourResult::SUCCESS;
}
