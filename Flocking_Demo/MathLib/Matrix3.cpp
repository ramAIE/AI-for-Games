#include "Matrix3.h"
#include <math.h>


Matrix3::Matrix3()
{
	m_00 = 1.0f; m_01 = 0.0f; m_02 = 0.0f;
	m_10 = 0.0f; m_11 = 1.0f; m_12 = 0.0f;
	m_20 = 0.0f; m_21 = 0.0f; m_22 = 1.0f;
}
// | m[0] m[3] m[6] |
// | m[1] m[4] m[7] |
// | m[2] m[5] m[8] |
Matrix3::Matrix3(float a_x, float a_y, float a_z, 
					float b_x, float b_y, float b_z, 
					float c_x, float c_y, float c_z)
{
	m_00 = a_x; m_01 = a_y; m_02 = a_z;
	m_10 = b_x; m_11 = b_y; m_12 = b_z;
	m_20 = c_x; m_21 = c_y; m_22 = c_z;

}

Matrix3::Matrix3(const Matrix3 & other)
{
	m[0] = other.m[0];
	m[1] = other.m[1];
	m[2] = other.m[2];
	m[3] = other.m[3];
	m[4] = other.m[4];
	m[5] = other.m[5];
	m[6] = other.m[6];
	m[7] = other.m[7];
	m[8] = other.m[8];
}

Vector3& Matrix3::operator[](int index)
{
	return axis[index];
}

Matrix3::operator float*()
{
	return m;
}

Matrix3 Matrix3::Identity()
{
	return Matrix3(	1.0f, 0.0f, 0.0f,
					0.0f, 1.0f, 0.0f,
					0.0f, 0.0f, 1.0f );
}

Matrix3 Matrix3::Transpose()
{
	return Matrix3(	m_00, m_10, m_20, 
					m_01, m_11, m_21,
					m_02, m_12, m_22 );
}


// =================== Matrix-Matrix Multiplication =================== //
// | m[0] m[1] m[2] |   | a_m[0] a_m[1] a_m[2] | 
// | m[3] m[4] m[5] | * | a_m[3] a_m[4] a_m[5] | 
// | m[6] m[7] m[8] |   | a_m[6] a_m[7] a_m[8] | 

// 	 |(m[0] * a_m[0] + m[1] * a_m[3] + m[2] * a_m[6]) (m[0] * a_m[1] + m[1] * a_m[4] + m[2] * a_m[7]) (m[0] * a_m[2] + m[1] * a_m[5] + m[2] * a_m[8]) |
// = |(m[3] * a_m[0] + m[4] * a_m[3] + m[5] * a_m[6]) (m[3] * a_m[1] + m[4] * a_m[4] + m[5] * a_m[7]) (m[3] * a_m[2] + m[4] * a_m[5] + m[5] * a_m[8]) |
//	 |(m[6] * a_m[0] + m[7] * a_m[3] + m[8] * a_m[6]) (m[6] * a_m[1] + m[7] * a_m[4] + m[8] * a_m[7]) (m[6] * a_m[2] + m[7] * a_m[5] + m[8] * a_m[8]) |

Matrix3 Matrix3::operator*(const Matrix3 & a_mat) const
{
	/*return Matrix3(m[0] * a_mat.m[0] + m[1] * a_mat.m[3] + m[2] * a_mat.m[6], m[0] * a_mat.m[1] + m[0] * a_mat.m[4] + m[0] * a_mat.m[7], m[0] * a_mat.m[0] + m[2] * a_mat.m[5] + m[0] * a_mat.m[8],
					m[3] * a_mat.m[0] + m[3] * a_mat.m[3] + m[5] * a_mat.m[6], m[3] * a_mat.m[1] + m[4] * a_mat.m[4] + m[0] * a_mat.m[7], m[0] * a_mat.m[0] + m[2] * a_mat.m[5] + m[0] * a_mat.m[8],
					m[0] * a_mat.m[0] + m[0] * a_mat.m[3] + m[0] * a_mat.m[6], m[0] * a_mat.m[1] + m[0] * a_mat.m[4] + m[0] * a_mat.m[7], m[0] * a_mat.m[0] + m[2] * a_mat.m[5] + m[0] * a_mat.m[8]);*/

	Matrix3 result;

	for (int r = 0; r < 3; ++r)
	{
		for (int c = 0; c < 3; ++c)
		{
			result.mm[r][c] = mm[0][c] * a_mat.mm[r][0] + mm[1][c] * a_mat.mm[r][1] + mm[2][c] * a_mat.mm[r][2];
		}
	}
	return result;
}
// ==================================================================== //


Vector3 Matrix3::operator*(const Vector3 & a_vec) const
{
	return Vector3(	m_00 * a_vec.m_x + m_10 * a_vec.m_y + m_20 * a_vec.m_z,
					m_01 * a_vec.m_x + m_11 * a_vec.m_y + m_21 * a_vec.m_z,
					m_02 * a_vec.m_x + m_12 * a_vec.m_y + m_22 * a_vec.m_z );
}

Matrix3 Matrix3::createTranslation(float c_x, float c_y, float c_z)
{
	Matrix3 m (	1.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f,
				c_x, c_y, c_z );
	return m;
}

Matrix3 Matrix3::createRotation(float a_rot)
{
	Matrix3 m (	cosf(a_rot), sinf(a_rot), 0.0f,
				-sinf(a_rot), cosf(a_rot), 0.0f,
				0.0f, 0.0f, 1.0f );
	return m;
}

Matrix3 Matrix3::createScale(float xScale, float yScale)
{
	Matrix3 m ( xScale, 0.0f, 0.0f,
				0.0f, yScale, 0.0f,
				0.0f, 0.0f, 1.0f );
	return m;
}


// | m[0] m[1] m[2] |
// | m[3] m[4] m[5] |
// | m[6] m[7] m[8] |
void Matrix3::setRotateX(float radians)
{
	// x axis is unchanged 
	xAxis = { 1, 0 ,0 };
	yAxis = { 0, cosf(radians), sinf(radians) };
	zAxis = { 0, -sinf(radians), cosf(radians) };

}

void Matrix3::setRotateY(float radians)
{
	xAxis = { cosf(radians), 0 ,-sinf(radians) };
	yAxis = { 0, 1, 0 };
	zAxis = { sinf(radians), 0, cosf(radians) };
}

void Matrix3::setRotateZ(float radians)
{
	xAxis = { cosf(radians), sinf(radians), 0 };
	yAxis = { -sinf(radians), cosf(radians), 0 };
	zAxis = { 0, 0, 1 };
}

void Matrix3::translate(float x, float y)
{
	m_20 += x;
	m_21 += y;
}

void Matrix3::rotateX(float radians) {
	Matrix3 m;
	m.setRotateX(radians);
	*this = *this * m;
}

void Matrix3::rotateY(float radians) {
	Matrix3 m;
	m.setRotateY(radians);
	*this = *this * m;
}

void Matrix3::rotateZ(float radians) {
	Matrix3 m;
	m.setRotateZ(radians);
	*this = *this * m;
}

Matrix3::~Matrix3()
{
}
