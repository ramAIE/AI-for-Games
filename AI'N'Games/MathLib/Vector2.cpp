#include "Vector2.h"
#include <math.h>


Vector2::Vector2()
{
}

Vector2::Vector2(float x, float y) : m_x(x), m_y(y)
{
}

Vector2::Vector2(const Vector2 & other) : m_x(other.m_x), m_y(other.m_y)
{
}

Vector2 Vector2::operator+(Vector2 other)
{
	return { m_x + other.m_x, m_y + other.m_y };
}

Vector2 Vector2::operator-(Vector2 other)
{
	return { m_x - other.m_x, m_y - other.m_y };
}

Vector2 Vector2::operator*(float scalar) const
{
	return { m_x * scalar, m_y * scalar };
}

Vector2 Vector2::operator/(float scalar)
{
	return { m_x / scalar, m_y / scalar };
}

float Vector2::operator[](int index)
{
	return data[index];
}

Vector2::operator float*()
{
	return &m_x;
}

float Vector2::magnitude()
{
	return sqrtf(m_x * m_x + m_y * m_y);
}

void Vector2::normalise()
{
	float m = sqrtf(m_x * m_x + m_y * m_y);
	m_x /= m;
	m_y /= m;
}

float Vector2::dot(const Vector2 & other)
{
	return m_x * other.m_x + m_y * other.m_y;
}


Vector2::~Vector2()
{
}

Vector2 operator*(float scalar, const Vector2 & other)
{
	return Vector2(other.m_x * scalar, other.m_y * scalar);
}
