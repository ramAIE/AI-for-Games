#include "Matrix2.h"
#include <math.h>

Matrix2::Matrix2() : m_00(0), m_01(0), m_10(0), m_11(0)
{

}

Matrix2::Matrix2(float m1, float m2, float m3, float m4) : m_00(m1), m_01(m3), m_10(m2), m_11(m4)
{

}

Matrix2::Matrix2(const Matrix2 & other)
{
	m_00 = other.m_00;
	m_01 = other.m_01;
	m_10 = other.m_10;
	m_11 = other.m_11;
}

Matrix2::operator float*()
{
	return m;
}

Matrix2 Matrix2::Identity()
{
	return Matrix2(1.0f, 0.0f,
					0.0f, 1.0f);
}

Matrix2 Matrix2::Transpose()
{
	return Matrix2(m_00, m_10, m_01, m_11);
}

Matrix2 Matrix2::operator*(const Matrix2 & a_rhs)
{
	Matrix2 result;
	for (int r = 0; r < 2; ++r)
	{
		for (int c = 0; c < 2; ++c)
		{
			result.mm[r][c] = mm[r][0] * a_rhs.mm[0][c] + mm[r][1] * a_rhs.mm[1][c];
		}
	}
	return result;
}

Matrix2 Matrix2::operator+(const Matrix2 & a_rhs)
{
	return Matrix2(m_00 + a_rhs.m_00, m_01 + a_rhs.m_01, m_10 + a_rhs.m_10, m_11 + a_rhs.m_11);
}

Vector2 Matrix2::operator*(const Vector2 & a_vec)
{
	return Vector2(m_00 * a_vec.m_x + m_01 * a_vec.m_y, m_10 * a_vec.m_x + m_11 * a_vec.m_y);
}

Vector2& Matrix2::operator[](int index)
{
	return axis[index];
}

void Matrix2::setRotate(float a_scalar)
{
	m_00 = cosf(a_scalar); m_01 = -sinf(a_scalar);
	m_10 = sinf(a_scalar); m_11 = cosf(a_scalar);
}

Matrix2::~Matrix2()
{
}
