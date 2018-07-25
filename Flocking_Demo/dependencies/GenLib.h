#pragma once
#define PI 3.1415926535897932384626433832795f
float DegtoRad(float degrees)
{
	float radians = (degrees * PI) / 180.0f;
	return radians;
}
float RadtoDeg(float radians)
{
	float degrees = (radians * 180.0f) / PI;
	return degrees;
}