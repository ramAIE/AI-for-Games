#include "Circle.h"
//#include <math.h>

Circle::Circle() {
	m_position = Vector3(0, 0, 0);
	m_radius = 0;
}


Circle::~Circle() {
}

bool Circle::IntersectsLine(Vector3 ahead) {
	// check if a line intersects the circle
	float distanceSqr = ((m_position.m_x - ahead.m_x) * (m_position.m_x - ahead.m_x) + (m_position.m_y - ahead.m_y) * (m_position.m_y - ahead.m_y));

	if (distanceSqr <= ((m_radius + 10) * (m_radius + 10)))
		return true;

	return false;
}
