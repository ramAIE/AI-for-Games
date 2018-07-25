#ifndef MATRIX2_H_
#define MATRIX2_H_

#include "Vector2.h"

class Matrix2
{
public:
	union {
		struct
		{
			float m[4];
		};
		struct
		{
			float m_00, m_01, m_10, m_11;
		};
		Vector2 axis[2];
		float mm[2][2];
	};
	Matrix2();
	Matrix2(float m1, float m2, float m3, float m4);
	Matrix2(const Matrix2& other);
	explicit operator float*();
	Matrix2 Identity();
	Matrix2 Transpose();
	Matrix2 operator *(const Matrix2& a_rhs); // Matrix - Matrix mul
	Vector2 operator *(const Vector2& a_vec); // Matrix - Vector mul
	Matrix2 operator +(const Matrix2& a_rhs);
	Vector2& operator [] (int index);
	void setRotate(float a_scalar);

	~Matrix2();
};
#endif // !MATRIX2_H_

