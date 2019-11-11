/*******************************************************************************
All content (c)2015, DigiPen (USA) Corporation, all rights reserved.

Primary Author: <yongmin.cho>
Coproducers:
<name> : <Sukjun Park>

File Description:
Header of math.cpp
*******************************************************************************/
#ifndef MATH_H
#define MATH_H
#include <cmath>
#include <type_traits>
#include <cstdlib>

const float SPRING = 75.f;
const float EDGE_SPRING = 1500;
namespace
{
	const float EPSILON = 0.0001f;
	const float PI = 3.14159265359f;
}

class Vector
{
public:

	float x;
	float y;

	Vector();
	
	template <typename T>
	Vector(T v)
	{
		static_assert(std::is_arithmetic<T>::value, "Template Type must be arithmentic type");

		x = static_cast<float>(v);
		y = static_cast<float>(v);
	}

	template <typename T, typename U>
	Vector(T vX, U vY)
	{
		static_assert(std::is_arithmetic<T>::value, "Template Type must be arithmentic type");
		static_assert(std::is_arithmetic<U>::value, "Template Type must be arithmentic type");

		x = static_cast<float>(vX);
		y = static_cast<float>(vY);
	}

	void Set(float vX, float vY);

	Vector operator+(const Vector& rhs) const;

	Vector operator+(float s) const;

	Vector operator-(const Vector& rhs) const;

	Vector operator-(float s) const;

	Vector operator-(void) const;

	Vector operator*(const Vector& rhs) const;

	Vector operator*(float s) const;

	Vector operator/(const Vector& rhs) const;

	Vector operator/(float s) const;

	void operator+=(const Vector& rhs);

	const bool operator==(const Vector& rhs);

	const bool operator!=(const Vector& rhs);

	void operator-=(const Vector& rhs);

	void operator*=(const Vector& rhs);

	void operator/=(const Vector& rhs);

	float LengthSqr(void) const;

	float Length(void) const;

	void Rotate(float radians);

	void Normalize(void);
};

const Vector gravity(0, -100.f);

class Mat2
{
public:
	float m00, m01;
	float m10, m11;
	float m[2][2];

	Mat2();// : m00(0), m01(0), m10(0), m11(0) { }
	Mat2(float radians);

	Mat2(float a, float b, float c, float d);

	void Set(float radians);

	Mat2 Abs(void) const;

	Vector AxisX(void) const;

	Vector AxisY(void) const;

	Mat2 Transpose(void) const;

	const Vector operator*(const Vector& rhs) const;

	const Mat2 operator*(const Mat2& rhs) const;
};

inline float Dot(const Vector& a, const Vector& b)
{
	return (a.x * b.x + a.y * b.y);
}

inline float DistanceSquared(const Vector& a, const Vector& b)
{
	Vector c = a - b;
	return Dot(c, c);
}

inline Vector Cross(const Vector& v, float a)
{
	return Vector(a * v.y, -a * v.x);
}

inline Vector Cross(float a, const Vector& v)
{
	return Vector(-a * v.y, a * v.x);
}

inline float Cross(const Vector& a, const Vector& b)
{
	return a.x * b.y - a.y * b.x;
}

// Comparison with tolerance of EPSILON
inline bool Equal(float a, float b)
{
	// <= instead of < for NaN comparison safety
	return std::abs(a - b) <= EPSILON;
}

inline float Squared(float a)
{
	return a * a;
}

inline float ABS(float X)
{
	if (X < 0)
		return -X;
	return X;
}
inline int PowerOf2(int x)
{
	return ((x > 0) && !(x & (x - 1)));
}

inline float RandMinMax(const float Min, const float Max)
{
	if (Min == Max) return Min;

	return Min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (Max - Min)));
}

inline int RandMinMax(const int Min, const int Max)
{
	if (Min == Max) return Min;

	return Min + rand() / (RAND_MAX / (Max - Min));
}

inline float Degree2Rad(const float degree)
{
	//degree * PI / 180;
	return degree * 0.01745329251f;
}

inline float Rad2Degree(const float rad)
{
	//rad * 180 / PI;
	return rad * 57.2957795131f;
}

#endif