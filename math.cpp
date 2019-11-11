/*******************************************************************************
All content (c)2015, DigiPen (USA) Corporation, all rights reserved.

Primary Author: <yongmin.cho>
Coproducers:
<name> : none

File Description:
This is help class like Vector and 2 x 2 Matrix 
*******************************************************************************/
#include "math.h"

/*******************************************************************************
Primary Author: <yongmin.cho>

Parameters:
<param> : none

Returns:
<return> : none

Function Description:
Vector class defalut constructor
*******************************************************************************/
Vector::Vector()
{
	x = 0;
	y = 0;
}

/*******************************************************************************
Primary Author: <yongmin.cho>

Parameters:
<param> : none

Returns:
<return> : none

Function Description:
Vector class for set x and y value
*******************************************************************************/
void Vector::Set(float vX, float vY)
{
	x = vX;
	y = vY;
}

/*******************************************************************************
Primary Author: <yongmin.cho>

Parameters:
<param> : none

Returns:
<return> :  Vector(x + rhs.x, y + rhs.y)

Function Description:
Vector class operator for plus two vector
*******************************************************************************/
Vector Vector::operator+(const Vector& rhs) const
{
	return Vector(x + rhs.x, y + rhs.y);
}

/*******************************************************************************
Primary Author: <yongmin.cho>

Parameters:
<param> : none

Returns:
<return> : Vector(x + s, y + s)

Function Description:
Vector class operator for plus vector to float
*******************************************************************************/
Vector Vector::operator+(float s) const
{
	return Vector(x + s, y + s);
}

/*******************************************************************************
Primary Author: <yongmin.cho>

Parameters:
<param> : none

Returns:
<return> : Vector(x - rhs.x, y - rhs.y)

Function Description:
Vector class operator for minus two vector
*******************************************************************************/
Vector Vector::operator-(const Vector& rhs) const
{
	return Vector(x - rhs.x, y - rhs.y);
}

/*******************************************************************************
Primary Author: <yongmin.cho>

Parameters:
<param> : none

Returns:
<return> : Vector(x - s, y - s)

Function Description:
Vector class operator for minus vector to float
*******************************************************************************/
Vector Vector::operator-(float s) const
{
	return Vector(x - s, y - s);
}

/*******************************************************************************
Primary Author: <yongmin.cho>

Parameters:
<param> : none

Returns:
<return> : Vector(-x, -y)

Function Description:
Vector class operator for make negative number
*******************************************************************************/
Vector Vector::operator-(void) const
{
	return Vector(-x, -y);
}

/*******************************************************************************
Primary Author: <yongmin.cho>

Parameters:
<param> : none

Returns:
<return> : Vector(x * rhs.x, y * rhs.y)

Function Description:
Vector class operator for multiply two vectors
*******************************************************************************/
Vector Vector::operator*(const Vector& rhs) const
{
	return Vector(x * rhs.x, y * rhs.y);
}

/*******************************************************************************
Primary Author: <yongmin.cho>

Parameters:
<param> : none

Returns:
<return> : Vector(x * s, y * s)

Function Description:
Vector class operator for multiply vector to float
*******************************************************************************/
Vector Vector::operator*(float s) const
{
	return Vector(x * s, y * s);
}

/*******************************************************************************
Primary Author: <yongmin.cho>

Parameters:
<param> : none

Returns:
<return> : Vector(x / rhs.x, y / rhs.y)

Function Description:
Vector class operator for divide two vectors
*******************************************************************************/
Vector Vector::operator/(const Vector& rhs) const
{
	return Vector(x / rhs.x, y / rhs.y);
}

/*******************************************************************************
Primary Author: <yongmin.cho>

Parameters:
<param> : none

Returns:
<return> : Vector(x / s, y / s)

Function Description:
Vector class operator for divide vector to float
*******************************************************************************/
Vector Vector::operator/(float s) const
{
	return Vector(x / s, y / s);
}

/*******************************************************************************
Primary Author: <yongmin.cho>

Parameters:
<param> : none

Returns:
<return> : none

Function Description:
Vector class operator for += 
*******************************************************************************/
void Vector::operator+=(const Vector& rhs)
{
	x += rhs.x;
	y += rhs.y;
}

const bool Vector::operator==(const Vector& rhs)
{
	if (x == rhs.x && y == rhs.y)
		return true;
	return false;
}

const bool Vector::operator!=(const Vector& rhs)
{
	if (x == rhs.x && y == rhs.y)
		return false;
	return true;
}

/*******************************************************************************
Primary Author: <yongmin.cho>

Parameters:
<param> : none

Returns:
<return> : none

Function Description:
Vector class operator for -=
*******************************************************************************/
void Vector::operator-=(const Vector& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
}

/*******************************************************************************
Primary Author: <yongmin.cho>

Parameters:
<param> : none

Returns:
<return> : none

Function Description:
Vector class operator for *=
*******************************************************************************/
void Vector::operator*=(const Vector& rhs)
{
	x *= rhs.x;
	y *= rhs.y;
}

/*******************************************************************************
Primary Author: <yongmin.cho>

Parameters:
<param> : none

Returns:
<return> : none

Function Description:
Vector class operator for /=
*******************************************************************************/
void Vector::operator/=(const Vector& rhs)
{
	x /= rhs.x;
	y /= rhs.y;
}

/*******************************************************************************
Primary Author: <yongmin.cho>

Parameters:
<param> : none

Returns:
<return> : (x * x + y * y)

Function Description:
Vector class function to make squared of this vector
*******************************************************************************/
float Vector::LengthSqr(void) const
{
	return (x * x + y * y);
}

/*******************************************************************************
Primary Author: <yongmin.cho>

Parameters:
<param> : none

Returns:
<return> : sqrtf(x * x + y * y)

Function Description:
Vector class function to return length of this vector
*******************************************************************************/
float Vector::Length(void) const
{
	return sqrtf(x * x + y * y);
}

/*******************************************************************************
Primary Author: <yongmin.cho>

Parameters:
<param> : none

Returns:
<return> : none

Function Description:
Vector class function to rotate this vector
*******************************************************************************/
void Vector::Rotate(float radians)
{
	float c = std::cos(radians);
	float s = std::sin(radians);

	float xp = x * c - y * s;
	float yp = x * s + y * c;

	x = xp;
	y = yp;
}

/*******************************************************************************
Primary Author: <yongmin.cho>

Parameters:
<param> : none

Returns:
<return> : none

Function Description:
Vector class function to Normalize of this vector
*******************************************************************************/
void Vector::Normalize(void)
{
	float len = Length();

	if (len > EPSILON)
	{
		float invLen = 1.0f / len;
		x *= invLen;
		y *= invLen;
	}
}

/*******************************************************************************
Primary Author: <yongmin.cho>

Parameters:
<param> : none

Returns:
<return> : none

Function Description:
Mat2 class defalut constructor
*******************************************************************************/
Mat2::Mat2()
{
	m00 = 0;
	m01 = 0;
	m10 = 0;
	m11 = 0;
}

/*******************************************************************************
Primary Author: <yongmin.cho>

Parameters:
<param> : none

Returns:
<return> : none

Function Description:
Mat2 class constructor
*******************************************************************************/
Mat2::Mat2(float radians)
{
	float c = std::cos(radians);
	float s = std::sin(radians);

	m00 = c; m01 = -s;
	m10 = s; m11 = c;
}

/*******************************************************************************
Primary Author: <yongmin.cho>

Parameters:
<param> : none

Returns:
<return> : none

Function Description:
Mat2 class assign constructor
*******************************************************************************/
Mat2::Mat2(float a, float b, float c, float d)
{
	m00 = a;
	m01 = b;
	m10 = c;
	m11 = d;
}

/*******************************************************************************
Primary Author: <yongmin.cho>

Parameters:
<param> : none

Returns:
<return> : none

Function Description:
Mat2 class fot set rotate 2 x2 Matrix
*******************************************************************************/
void Mat2::Set(float radians)
{
	float c = std::cos(radians);
	float s = std::sin(radians);

	m00 = c; m01 = -s;
	m10 = s; m11 = c;
}

/*******************************************************************************
Primary Author: <yongmin.cho>

Parameters:
<param> : none

Returns:
<return> : Mat2(std::abs(m00), std::abs(m01), std::abs(m10), std::abs(m11))

Function Description:
Mat2 class to make aboulte all components
*******************************************************************************/
Mat2 Mat2::Abs(void) const
{
	return Mat2(std::abs(m00), std::abs(m01), std::abs(m10), std::abs(m11));
}

/*******************************************************************************
Primary Author: <yongmin.cho>

Parameters:
<param> : none

Returns:
<return> : Vector(m00, m10)

Function Description:
Mat2 class to return x axis
*******************************************************************************/
Vector Mat2::AxisX(void) const
{
	return Vector(m00, m10);
}

/*******************************************************************************
Primary Author: <yongmin.cho>

Parameters:
<param> : none

Returns:
<return> : Vector(m01, m11)

Function Description:
Mat2 class to return y axis
*******************************************************************************/
Vector Mat2::AxisY(void) const
{
	return Vector(m01, m11);
}

/*******************************************************************************
Primary Author: <yongmin.cho>

Parameters:
<param> : none

Returns:
<return> : Mat2(m00, m10, m01, m11)

Function Description:
Mat2 class to transpose
*******************************************************************************/
Mat2 Mat2::Transpose(void) const
{
	return Mat2(m00, m10, m01, m11);
}

/*******************************************************************************
Primary Author: <yongmin.cho>

Parameters:
<param> : none

Returns:
<return> : Vector(m00 * rhs.x + m01 * rhs.y, m10 * rhs.x + m11 * rhs.y)

Function Description:
Mat2 class operator to multiply mat2 and vector
*******************************************************************************/
const Vector Mat2::operator*(const Vector& rhs) const
{
	return Vector(m00 * rhs.x + m01 * rhs.y, m10 * rhs.x + m11 * rhs.y);
}

/*******************************************************************************
Primary Author: <yongmin.cho>

Parameters:
<param> : none

Returns:
<return> : 	return Mat2(
		m[0][0] * rhs.m[0][0] + m[0][1] * rhs.m[1][0],
		m[0][0] * rhs.m[0][1] + m[0][1] * rhs.m[1][1],
		m[1][0] * rhs.m[0][0] + m[1][1] * rhs.m[1][0],
		m[1][0] * rhs.m[0][1] + m[1][1] * rhs.m[1][1]
		);

Function Description:
Mat2 class operator to multiply with two Mat2s
*******************************************************************************/
const Mat2 Mat2::operator*(const Mat2& rhs) const
{
		// [00 01]  [00 01]
		// [10 11]  [10 11]

	return Mat2(
		m[0][0] * rhs.m[0][0] + m[0][1] * rhs.m[1][0],
		m[0][0] * rhs.m[0][1] + m[0][1] * rhs.m[1][1],
		m[1][0] * rhs.m[0][0] + m[1][1] * rhs.m[1][0],
		m[1][0] * rhs.m[0][1] + m[1][1] * rhs.m[1][1]
		);
}