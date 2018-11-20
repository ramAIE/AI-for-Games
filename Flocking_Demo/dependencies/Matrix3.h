#pragma once
#include "Vector3.h"

class Matrix3
{
public:
	union 
	{
		struct { float m[9]; };
		struct { float mm[3][3]; };
		struct 
		{
			float m_00, m_01, m_02,
				m_10, m_11, m_12,
				m_20, m_21, m_22; 
		};
		struct {
			Vector3 xAxis;
			Vector3 yAxis;
			Vector3 zAxis;
		};
		struct { Vector3 axis[3]; };
	};
	Matrix3();
	Matrix3(float a_x, float a_y, float a_z,
			float b_x, float b_y, float b_z,
			float c_x, float c_y, float c_z);
	Matrix3(const Matrix3 & other);

	Vector3& operator [] (int index);
	explicit operator float* ();

	Matrix3 Identity();
	Matrix3 Transpose();
	Matrix3 operator *(const Matrix3& a_mat) const;
	Vector3 operator *(const Vector3& a_vec) const;

	static Matrix3 createTranslation(float c_x, float c_y, float c_z);
	static Matrix3 createRotation(float a_rot);
	static Matrix3 createScale(float xScale, float yScale);


	void setRotateX(float radians);
	void setRotateY(float radians);
	void setRotateZ(float radians);

	void translate(float x, float y);

	void rotateX(float radians);
	void rotateY(float radians);
	void rotateZ(float radians);

	~Matrix3();
};

