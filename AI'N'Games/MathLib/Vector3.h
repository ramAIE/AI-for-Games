#pragma once
class Vector3
{
public:

	union
	{
		struct
		{
			float m_x;
			float m_y;
			float m_z;
		};
		float data[3];
	};

	Vector3();
	Vector3(float x, float y, float z);
	Vector3(const Vector3& other);

	Vector3 operator + (const Vector3& other) const;
	Vector3 operator - (Vector3 other);
	Vector3 operator * (float scalar);
	Vector3 operator / (float scalar);
	explicit operator float*();
	friend Vector3 operator * (float scalar, const Vector3 & other);

	float magnitude();
	void normalise();
	Vector3 cross(Vector3 other);
	float dot(const Vector3& other);


	~Vector3();
};

