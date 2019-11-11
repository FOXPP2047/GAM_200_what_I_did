/*******************************************************************************
All content (c)2015, DigiPen (USA) Corporation, all rights reserved.

Primary Author: <yongmin.cho>
Coproducers:
<name> : none

File Description:
Header of Matrix.cpp
*******************************************************************************/
#ifndef MATRIX_H
#define MATRIX_H

const int matSize = 4;

class Mat44
{
public:
	Mat44();
	Mat44(const Mat44& rhs);
	~Mat44();

	void SetValue(float* pValue, int Rows, int Cols);
	float GetValue(int Rows, int Cols);
	Mat44 Transpose();
	Mat44 Inverse();
	float Determinant();

	Mat44 operator+(const Mat44& rhs) const;
	Mat44 operator-(const Mat44& rhs) const;
	Mat44 operator*(const float rhs) const;
	Mat44 operator*(const Mat44& rhs) const;
	Mat44& operator=(const Mat44& rhs);
private:
	int m_Rows;
	int m_Cols;
	float* m_pMat;
};
#endif