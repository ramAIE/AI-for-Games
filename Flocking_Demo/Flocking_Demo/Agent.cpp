#include "Agent.h"
#include <Renderer2D.h>
#include <Texture.h>
#include "Behaviour.h"

Agent::Agent() {
	m_texture = nullptr;
	m_local = m_local.Identity();
	m_global = m_local;
	m_acceleration = Vector3(0, 0, 0);
	m_velocity = Vector3(0, 0, 0);
	m_maxVelocity = 300.0f;
}

Agent::Agent(aie::Texture * texture, Vector3 pos) {
	m_texture = texture;
	m_local = Matrix3::createTranslation(pos.m_x, pos.m_y, pos.m_z);
	m_global = m_local;
	m_acceleration = Vector3(0, 0, 0);
	m_velocity = Vector3(0, 0, 0);
	m_maxVelocity = 100.0f;
}

void Agent::update(float deltaTime) {
	AddForce(m_velocity * -0.15f);
	m_velocity = m_velocity + m_acceleration * deltaTime;

	// cap the speed
	if (m_velocity.magnitude() > m_maxVelocity) {
		m_velocity.normalise();
		m_velocity = m_velocity * m_maxVelocity;
	}
	float angle = atanf(m_velocity.m_y / m_velocity.m_x);
	if (angle > 0)
		rotate(angle);

	translate(m_velocity * deltaTime);
	m_acceleration = Vector3(0, 0, 0);

	UpdateGlobalTransform();

	for (auto behaviour : m_behaviours) {
		behaviour->update(this, deltaTime);
	}
}

void Agent::draw(aie::Renderer2D * renderer) {
	renderer->drawSpriteTransformed3x3(m_texture, (float*)m_global);
}

Matrix3 Agent::GetLocalTransform() {
	return m_local;
}

Matrix3 Agent::GetGlobalTransform() {
	return m_global;
}

void Agent::UpdateGlobalTransform() {
	m_global = m_local;
}

void Agent::SetPosition(Vector3 position) {
	m_local[2] = { position.m_x, position.m_y, 1 };
}

void Agent::SetRotate(float radians) {
	m_local.setRotateZ(radians);
}

void Agent::translate(Vector3 position) {
	m_local.translate(position.m_x, position.m_y);
}

void Agent::rotate(float radians) {
	m_local.rotateZ(radians);
}

void Agent::addBehaviour(Behaviour * behaviour) {
	m_behaviours.push_back(behaviour);
}

void Agent::AddForce(Vector3 force) {
	m_acceleration = m_acceleration + force;
}

bool Agent::RotateHeadingtoFacePosition(Vector3 target) {
	Vector3 toTarget = target - m_local[2];
	toTarget.normalise();

	auto heading = m_local[1];
	heading.normalise();

	// determine the angle between the heading vector and the target
	float angle = acosf(heading.dot(toTarget));

	// return true if the player is facing the target
	if (angle < 0.00001) return true;

	return false;
}


Agent::~Agent() {
	delete m_texture;
}
