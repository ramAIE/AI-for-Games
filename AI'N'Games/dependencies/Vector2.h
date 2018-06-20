#ifndef VECTOR2_H_
#define VECTOR2_H_

class Vector2
{
public:

	union
	{
		struct
		{
			float m_x;
			float m_y;
		};
		float data[2];
	};

	Vector2();
	Vector2(float x, float y);
	Vector2(const Vector2& other);

	Vector2 operator + (Vector2 other);
	Vector2 operator - (Vector2 other);
	Vector2 operator * (float scalar) const;
	Vector2 operator / (float scalar);
	float operator [] (int index);
	explicit operator float* ();
	friend Vector2 operator * (float scalar, const Vector2& other);


	float magnitude();
	void normalise();
	float dot(const Vector2& other);

	~Vector2();
};
#endif // !VECTOR2_H_
