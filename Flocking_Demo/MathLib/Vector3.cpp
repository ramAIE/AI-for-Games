#include "Vector3.h"
#include <math.h>


Vector3::Vector3(): m_x(0.0f), m_y(0.0f),m_z(0.0f)
{
}

Vector3::Vector3(float x, float y, float z) : m_x(x), m_y(y),m_z(z)
{
}
Vector3::Vector3(const Vector3 & other) : m_x (other.m_x), m_y(other.m_y), m_z(other.m_z)
{
}
// Addition
Vector3 Vector3::operator+(const Vector3& other) const
{
	return { m_x + other.m_x, m_y + other.m_y, m_z + other.m_z };
}
// Subtraction
Vector3 Vector3::operator-(Vector3 other)
{
	return { m_x - other.m_x, m_y - other.m_y, m_z - other.m_z };
}
// multiplication
Vector3 Vector3::operator*(float scalar)
{
	return { m_x * scalar, m_y * scalar, m_z * scalar};
}

Vector3 Vector3::operator/(float scalar)
{
	return { m_x / scalar, m_y / scalar, m_z / scalar };
}

bool Vector3::operator==(Vector3 other) {
	return (m_x == other.m_x, m_y == other.m_y, m_z == other.m_z);
}

Vector3::operator float*()
{
	return data;
}

float Vector3::magnitude() 
{
	return sqrtf(m_x * m_x + m_y * m_y + m_z * m_z);
}

void Vector3::normalise()
{
	float m = sqrtf(m_x * m_x + m_y * m_y + m_z * m_z);
	m_x /= m;
	m_y /= m;
	m_z /= m;
}

Vector3 Vector3::cross(Vector3 other)
{
	// y*other.z - z*other.y
	// z*other.x - x*other.z
	// x*other.y - y*other.x
	return { m_y * other.m_z - m_z * other.m_y, 
		m_z * other.m_x - m_x * other.m_z, 
		m_x * other.m_y - m_y*other.m_x};
}

float Vector3::dot(const Vector3& other)
{
	// ax * bx + ay * by + az * bz
	return m_x * other.m_x + m_y * other.m_y + m_z * other.m_z;
}

int Vector3::Sign(Vector3 & other)
{
	if (m_y * other.m_x > m_x * other.m_y)
		return -1;
	else
		return 1;
}


Vector3::~Vector3()
{
}

Vector3 operator*(float scalar, const Vector3 & other)
{
	return Vector3(other.m_x * scalar, other.m_y * scalar, other.m_z * scalar);
}
