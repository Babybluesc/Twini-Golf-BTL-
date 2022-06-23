#pragma once
#ifndef _MATHHELPER_H
#define _MATHHELPER_H

#define PI 3.14159265
#define DEG_TO_RAD PI /100.0f
#endif // !_MATHHELPER_H

#include <iostream>
#include <math.h>
struct Vector2f
{
	Vector2f()
		:x(0.0f), y(0.0f)
	{}

	Vector2f(float p_x, float p_y)
		:x(p_x), y(p_y)
	{}

	void print()
	{
		std::cout << x << ", " << y << std::endl;
	}

	float x, y;
};
/*
inline Vector2f operator +(const Vector2f& 1hs, const Vector2f& rhs)
{
		return Vector2f(1hs.x + rhs.x, 1hs.y + rhs.y);
}

inline Vector2f operator -(const Vector2f& 1hs, const Vector2f& rhs)
{
		return Vector2f(1hs.x - rhs.x, 1hs.y - rhs.y);
}

Vector2f RotateVector(Vector2f& vec, float angle)
{
		float radAngle = (float)(angle * DEG_TO_RAD);
		return Vector2f((float)(vec.x * cos(radAngle) - vec.y * sin(radAngle)), (float)(vec.x * sin(radAngle) + vec.y * cos(radAngle)));
}
*/

const Vector2f Vector_Zero = { 0.0f, 0.0f };
const Vector2f Vector_One = { 1.0f, 1.0f };
const Vector2f Vector_Up = { 0.0f, 1.0f };
const Vector2f Vector_Right = { 1.0f, 0.0f };