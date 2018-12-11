#include "Agent.h"
#include <Renderer2D.h>
#include <Texture.h>
#include "Behaviour.h"
#include <GenLib.h>
#include <iostream>

Agent::Agent() {
	m_texture = nullptr;
	m_local = m_local.Identity();
	m_global = m_local;
	m_acceleration = Vector3(0, 0, 0);
	m_velocity = Vector3(0, 0, 0);
	m_maxVelocity = 300.0f;
	m_speed = 100.f;
}

Agent::Agent(aie::Texture * texture, Vector3 pos) {
	m_texture = texture;
	m_local = Matrix3::createTranslation(pos.m_x, pos.m_y, pos.m_z);
	m_global = m_local;
	m_acceleration = Vector3(0, 0, 0);
	m_velocity = Vector3(0, 0, 0);
	m_maxVelocity = 100.0f;
	m_heading = m_local[2] + m_local[1];
	m_speed = 100.0f;
}

void Agent::update(float deltaTime) {
	// agent goes out of bounds
	if (m_local[2].m_x < 0)
		m_local[2].m_x = 1280;
	else if (m_local[2].m_x > 1280)
		m_local[2].m_x = 0;

	if (m_local[2].m_y < 0)
		m_local[2].m_y = 720;
	else if (m_local[2].m_y > 720)
		m_local[2].m_y = 0;

	// direction the agent is facing
	m_heading = m_local[1] + m_local[2];

	// perpendicular vector
	m_side = m_local[0] + m_local[2];
	m_side.normalise();

	// friction to the motion
	AddForce(m_velocity * -0.15f);
	m_velocity = m_velocity + m_acceleration * deltaTime;

	// cap the speed
	if (m_velocity.magnitude() > m_maxVelocity) {
		m_velocity.normalise();
		m_velocity = m_velocity * m_maxVelocity;
	}

	// velocity vector from player's position
	Vector3 velocityVector = m_velocity + m_local[2];

	// if the agent has rotated to face the velocity vector, move the player towards the direction.
	if (RotateHeadingtoFacePosition(velocityVector, deltaTime)) {
		translate(m_velocity * deltaTime);
	}

	// reset the acceleration to zero if not moving
	m_acceleration = Vector3(0, 0, 0);

	// update the globalTransform
	UpdateGlobalTransform();

	if (!m_behaviours.empty()) {
		// iterate through all the behaviours of the agent
		for (auto behaviour : m_behaviours) {
			behaviour->update(this, deltaTime);
		}
	}
}

void Agent::draw(aie::Renderer2D * renderer) {
	renderer->drawSpriteTransformed3x3(m_texture, (float*)&m_global);

	// draw an orange line to represent velocity
	renderer->setRenderColour(0.8f, 0.5f, 0.2f);
	Vector3 velocityPoint = m_global[2] + m_velocity;
	renderer->drawLine(m_global[2].m_x, m_global[2].m_y, velocityPoint.m_x, velocityPoint.m_y);
	// uncomment the following code to show the x-axis, y-axis and velocity lines for the agent in local space
	/* 
	// draw a green line to represent y-axis
	renderer->setRenderColour(0.0f, 1.0f, 0.0f, 1.0f);
	Vector3 headingPoint = m_global[2] + m_global[1] * 50.0f;
	renderer->drawLine(m_global[2].m_x, m_global[2].m_y, headingPoint.m_x, headingPoint.m_y);
	// draw a red line to represent x-axis
	renderer->setRenderColour(1.0f, 0.0f, 0.0f);
	Vector3 sidePoint = m_global[2] + m_global[0] * 50.0f;
	renderer->drawLine(m_global[2].m_x, m_global[2].m_y, sidePoint.m_x, sidePoint.m_y);
	*/

	renderer->setRenderColour(1.0f, 1.0f, 1.0f);
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

// return true if the player is facing the target
bool Agent::RotateHeadingtoFacePosition(Vector3 target, float deltaTime) {
	float angle = 0.0f;

	Vector3 toTarget = target - m_local[2];
	toTarget.normalise();

	Vector3 current = m_heading - m_local[2];
	current.normalise();

	// determine the angle between the heading vector and the target
	angle = acosf(current.dot(toTarget));

	// converting angle to radians
	angle = DegtoRad(angle);

	// need to fix the rotation.
	// rotates quite faster before it chooses the direction of the velocity.
	if (angle > 0.001f) {
		Matrix3 rotationMatrix = Matrix3::createRotation(angle * current.Sign(toTarget));
		m_local = m_local * rotationMatrix;
		return false;
	}

	return true;
}


Agent::~Agent() {
	delete m_texture;
}
