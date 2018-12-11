#pragma once
#include <Vector3.h>
class Circle {
public:
	Circle();
	~Circle();

	void SetPosition(Vector3 position) { m_position = position; }
	Vector3 GetPosition() { return m_position; }

	void SetRadius(float radius) { m_radius = radius; }
	float GetRadius() { return m_radius; }

	bool IntersectsLine(Vector3 ahead);

private:
	Vector3 m_position;
	float m_radius;
};

