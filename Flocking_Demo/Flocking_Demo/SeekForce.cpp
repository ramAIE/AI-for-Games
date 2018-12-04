#include "SeekForce.h"
#include <Input.h>


SeekForce::SeekForce() {
}


SeekForce::~SeekForce() {
}

Vector3 SeekForce::getForce(Agent * agent) {
	// agent's current position
	Vector3 currentPosition = agent->GetLocalTransform()[2];

	Vector3 force = Vector3(0, 0, 0);

	// get the mouse position
	if (m_input->isMouseButtonDown(aie::INPUT_MOUSE_BUTTON_LEFT)) {
		int targetX = 0, targetY = 0;
		m_input->getMouseXY(&targetX, &targetY);
		m_target.m_x = targetX;
		m_target.m_y = targetY;
		m_target.m_z = 1;
	}

	// calculate the distance between the current mouse position and the agent position
	Vector3 desiredVelocity = m_target - currentPosition;
	// normalize the desired velocity
	desiredVelocity.normalise();
	// apply some speed
	desiredVelocity = desiredVelocity * 100.0f;
	// calculate the steering force
	force = desiredVelocity - agent->GetVelocity();

	return force * 10.0f;
}
