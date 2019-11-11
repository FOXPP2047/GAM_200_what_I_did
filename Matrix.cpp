/*******************************************************************************
All content (c)2015, DigiPen (USA) Corporation, all rights reserved.

Primary Author: <yongmin.cho>
Coproducers:
<name> : none

File Description:
4 x 4 Matrix for graphics
*******************************************************************************/
#include "Main.h"

/*******************************************************************************
Primary Author: <yongmin.cho>

Parameters:
<param> : none

Returns:
<return> : none

Function Description:
Mat44 class defalut constructor
*******************************************************************************/
Mat44::Mat44()
{
	m_Rows = 0;
	m_Cols = 0;
	m_pMat = 0;
}

/*******************************************************************************
Primary Author: <yongmin.cho>

Parameters:
<rhs> : othre Mat44 for assign

Returns:
<return> : none

Function Description:
Mat44 class assign constructor
*******************************************************************************/
Mat44::Mat44(const Mat44& rhs)
{
	m_Rows = rhs.m_Rows;
	m_Cols = rhs.m_Cols;

	m_pMat = new float[m_Rows*m_Cols];

	for (int i = 0; i < m_Rows*m_Cols; i++)
		m_pMat[i] = rhs.m_pMat[i];
}

/*******************************************************************************
Primary Author: <yongmin.cho>

Parameters:
<param> : none

Returns:
<return> : none

Function Description:
Mat44 class destructor
*******************************************************************************/
Mat44::~Mat44()
{
	if (m_pMat)
	{
		delete(m_pMat);
		m_pMat = 0;
	}
}

/*******************************************************************************
Primary Author: <yongmin.cho>

Parameters:
<pValue> : value for assgin
<Rows> : row fo matrix
<Cols> : column of matrix

Returns:
<return> : none

Function Description:
assign value pValue to m_pMat
*******************************************************************************/
void Mat44::SetValue(float* pValue, int Rows, int Cols)
{
	m_Rows = Rows;
	m_Cols = Cols;

	if (m_pMat)
		delete(m_pMat);

	m_pMat = new float[Rows*Cols];

	for (int i = 0; i < Rows*Cols; i++)
		m_pMat[i] = pValue[i];
}

/*******************************************************************************
Primary Author: <yongmin.cho>

Parameters:
<Rows> : row fo matrix
<Cols> : column of matrix

Returns:
<m_pMat> : return value of pMat[Rows][Cols]

Function Description:
return the value of m_pMat[Rows][Cols]
*******************************************************************************/
float Mat44::GetValue(int Rows, int Cols)
{
	return m_pMat[(Rows - 1)*m_Cols + (Cols - 1)];
}

/*******************************************************************************
Primary Author: <yongmin.cho>

Parameters:
<param> : none

Returns:
<transposeMatrix> : return transpose of m_pMat

Function Description:
return the transpose of m_pMat
*******************************************************************************/
Mat44 Mat44::Transpose()
{
	Mat44 transposeMatrix;
	float* pTemp = new float[m_Rows*m_Cols];

	for (int i = 0; i < m_Rows; i++)
	{
		for (int j = 0; j < m_Cols; j++)
			pTemp[i + m_Rows*j] = m_pMat[i*m_Cols + j];
	}
	
	transposeMatrix.SetValue(pTemp, m_Rows, m_Cols);

	delete(pTemp);
	return transposeMatrix;
}

/*******************************************************************************
Primary Author: <yongmin.cho>

Parameters:
<param> : none

Returns:
<determinant> : return determinant of m_pMat

Function Description:
return the determinant of m_pMat
*******************************************************************************/
float Mat44::Determinant()
{
	float determinant;

	determinant = m_pMat[0] * (m_pMat[5] * (m_pMat[10] * m_pMat[15] - m_pMat[11] * m_pMat[14]) - m_pMat[6] * (m_pMat[9] * m_pMat[15] - m_pMat[11] * m_pMat[13]) + m_pMat[7] * (m_pMat[9] * m_pMat[14] - m_pMat[10] * m_pMat[13]))
		- m_pMat[1] * (m_pMat[4] * (m_pMat[10] * m_pMat[15] - m_pMat[11] * m_pMat[14]) - m_pMat[6] * (m_pMat[8] * m_pMat[15] - m_pMat[11] * m_pMat[12]) + m_pMat[7] * (m_pMat[8] * m_pMat[14] - m_pMat[10] * m_pMat[12]))
		+ m_pMat[2] * (m_pMat[4] * (m_pMat[9] * m_pMat[15] - m_pMat[11] * m_pMat[13]) - m_pMat[5] * (m_pMat[8] * m_pMat[15] - m_pMat[11] * m_pMat[12]) + m_pMat[7] * (m_pMat[8] * m_pMat[13] - m_pMat[9] * m_pMat[12]))
		- m_pMat[3] * (m_pMat[4] * (m_pMat[9] * m_pMat[14] - m_pMat[10] * m_pMat[13]) - m_pMat[5] * (m_pMat[8] * m_pMat[14] - m_pMat[10] * m_pMat[12]) + m_pMat[6] * (m_pMat[8] * m_pMat[13] - m_pMat[9] * m_pMat[12]));

	return determinant;
}

/*******************************************************************************
Primary Author: <yongmin.cho>

Parameters:
<param> : none

Returns:
<inverseMatrix> : return inverse matrix of m_pMat

Function Description:
return the inverse matrix of m_pMat
*******************************************************************************/
Mat44 Mat44::Inverse()
{
	Mat44 inverseMatrix;
	float* pTemp = new float[m_Rows*m_Cols];

	float CDet = 1 / Determinant();

	pTemp[0] = CDet * (m_pMat[5]*m_pMat[10]*m_pMat[15] + m_pMat[6]*m_pMat[11]*m_pMat[13] + m_pMat[7]*m_pMat[9]*m_pMat[14] - m_pMat[5]*m_pMat[11]*m_pMat[14] - m_pMat[6]*m_pMat[9]*m_pMat[15] - m_pMat[7]*m_pMat[10]*m_pMat[13]);
	pTemp[1] = CDet * (m_pMat[1]*m_pMat[11]*m_pMat[14] + m_pMat[2]*m_pMat[9]*m_pMat[15] + m_pMat[3]*m_pMat[10]*m_pMat[13] - m_pMat[1]*m_pMat[10]*m_pMat[15] - m_pMat[2]*m_pMat[11]*m_pMat[13] - m_pMat[3]*m_pMat[9]*m_pMat[14]);
	pTemp[2] = CDet * (m_pMat[1] * m_pMat[6] * m_pMat[15] + m_pMat[2] * m_pMat[7] * m_pMat[13] + m_pMat[3] * m_pMat[5] * m_pMat[14] - m_pMat[1] * m_pMat[7] * m_pMat[14] - m_pMat[2] * m_pMat[7] * m_pMat[15] - m_pMat[3] * m_pMat[6] * m_pMat[13]);
	pTemp[3] = CDet * (m_pMat[1] * m_pMat[7] * m_pMat[10] + m_pMat[2] * m_pMat[5] * m_pMat[11] + m_pMat[3] * m_pMat[6] * m_pMat[9] - m_pMat[1] * m_pMat[6] * m_pMat[11] - m_pMat[2] * m_pMat[7] * m_pMat[9] - m_pMat[3] * m_pMat[5] * m_pMat[10]);

	pTemp[4] = CDet * (m_pMat[4] * m_pMat[11] * m_pMat[14] + m_pMat[6] * m_pMat[8] * m_pMat[15] + m_pMat[7] * m_pMat[10] * m_pMat[12] - m_pMat[4] * m_pMat[10] * m_pMat[15] - m_pMat[6] * m_pMat[11] * m_pMat[12] - m_pMat[7] * m_pMat[8] * m_pMat[14]);
	pTemp[5] = CDet * (m_pMat[0] * m_pMat[10] * m_pMat[15] + m_pMat[2] * m_pMat[11] * m_pMat[12] + m_pMat[3] * m_pMat[8] * m_pMat[14] - m_pMat[0] * m_pMat[11] * m_pMat[14] - m_pMat[2] * m_pMat[8] * m_pMat[15] - m_pMat[3] * m_pMat[10] * m_pMat[11]);
	pTemp[6] = CDet * (m_pMat[0] * m_pMat[6] * m_pMat[14] + m_pMat[2] * m_pMat[4] * m_pMat[15] + m_pMat[3] * m_pMat[6] * m_pMat[12] - m_pMat[0] * m_pMat[6] * m_pMat[15] - m_pMat[2] * m_pMat[7] * m_pMat[12] - m_pMat[3] * m_pMat[4] * m_pMat[14]);
	pTemp[7] = CDet * (m_pMat[0] * m_pMat[5] * m_pMat[11] + m_pMat[2] * m_pMat[7] * m_pMat[10] + m_pMat[3] * m_pMat[4] * m_pMat[10] - m_pMat[0] * m_pMat[7] * m_pMat[10] - m_pMat[2] * m_pMat[4] * m_pMat[11] - m_pMat[3] * m_pMat[6] * m_pMat[12]);
	
	pTemp[8] = CDet * (m_pMat[4] * m_pMat[9] * m_pMat[15] + m_pMat[5] * m_pMat[11] * m_pMat[12] + m_pMat[7] * m_pMat[8] * m_pMat[13] - m_pMat[4] * m_pMat[11] * m_pMat[13] - m_pMat[5] * m_pMat[8] * m_pMat[15] - m_pMat[7] * m_pMat[9] * m_pMat[11]);
	pTemp[9] = CDet * (m_pMat[0] * m_pMat[11] * m_pMat[13] + m_pMat[1] * m_pMat[8] * m_pMat[15] + m_pMat[3] * m_pMat[9] * m_pMat[12] - m_pMat[0] * m_pMat[9] * m_pMat[15] - m_pMat[1] * m_pMat[11] * m_pMat[12] - m_pMat[3] * m_pMat[12] * m_pMat[13]);
	pTemp[10] = CDet * (m_pMat[0] * m_pMat[5] * m_pMat[15] + m_pMat[1] * m_pMat[7] * m_pMat[12] + m_pMat[3] * m_pMat[4] * m_pMat[13] - m_pMat[0] * m_pMat[7] * m_pMat[13] - m_pMat[1] * m_pMat[4] * m_pMat[15] - m_pMat[3] * m_pMat[5] * m_pMat[12]);
	pTemp[11] = CDet * (m_pMat[0] * m_pMat[7] * m_pMat[9] + m_pMat[1] * m_pMat[4] * m_pMat[11] + m_pMat[3] * m_pMat[5] * m_pMat[8] - m_pMat[0] * m_pMat[5] * m_pMat[11] - m_pMat[1] * m_pMat[7] * m_pMat[13] - m_pMat[3] * m_pMat[4] * m_pMat[9]);
	
	pTemp[12] = CDet * (m_pMat[4] * m_pMat[10] * m_pMat[13] + m_pMat[5] * m_pMat[8] * m_pMat[14] + m_pMat[6] * m_pMat[9] * m_pMat[12] - m_pMat[4] * m_pMat[9] * m_pMat[14] - m_pMat[5] * m_pMat[10] * m_pMat[12] - m_pMat[6] * m_pMat[8] * m_pMat[13]);
	pTemp[13] = CDet * (m_pMat[0] * m_pMat[9] * m_pMat[14] + m_pMat[1] * m_pMat[10] * m_pMat[12] + m_pMat[2] * m_pMat[8] * m_pMat[13] - m_pMat[0] * m_pMat[10] * m_pMat[13] - m_pMat[1] * m_pMat[8] * m_pMat[14] - m_pMat[2] * m_pMat[9] * m_pMat[12]);
	pTemp[14] = CDet * (m_pMat[0] * m_pMat[6] * m_pMat[13] + m_pMat[1] * m_pMat[4] * m_pMat[14] + m_pMat[2] * m_pMat[5] * m_pMat[12] - m_pMat[0] * m_pMat[5] * m_pMat[14] - m_pMat[1] * m_pMat[6] * m_pMat[12] - m_pMat[2] * m_pMat[4] * m_pMat[13]);
	pTemp[15] = CDet * (m_pMat[0] * m_pMat[5] * m_pMat[10] + m_pMat[1] * m_pMat[6] * m_pMat[8] + m_pMat[2] * m_pMat[4] * m_pMat[9] - m_pMat[0] * m_pMat[6] * m_pMat[9] - m_pMat[1] * m_pMat[4] * m_pMat[10] - m_pMat[2] * m_pMat[5] * m_pMat[8]);

	inverseMatrix.SetValue(pTemp, m_Rows, m_Cols);
	delete(pTemp);

	return inverseMatrix;
}

/*******************************************************************************
Primary Author: <yongmin.cho>

Parameters:
<param> : none

Returns:
<*this> : return assign theirself matrix

Function Description:
assign operator to make same
*******************************************************************************/
Mat44& Mat44::operator=(const Mat44& rhs)
{
	if (m_pMat)
		delete(m_pMat);

	m_Rows = rhs.m_Rows;
	m_Cols = rhs.m_Cols;
	m_pMat = new float[m_Rows*m_Cols];

	for (int i = 0; i < m_Rows*m_Cols; i++)
		m_pMat[i] = rhs.m_pMat[i];

	return (*this);
}

/*******************************************************************************
Primary Author: <yongmin.cho>

Parameters:
<rhs> : other matix to add

Returns:
<matrixSum> : return caculated theirself matrix

Function Description:
return caculated theirself matrixs
*******************************************************************************/
Mat44 Mat44::operator+(const Mat44& rhs) const
{
	Mat44 matrixSum;
	float* pTemp = new float[m_Rows*m_Cols];

	/*if (m_Rows != rhs.m_Rows || m_Cols != rhs.m_Cols)
		return matrixSum;*/

	for (int i = 0; i < m_Rows*m_Cols; i++)
		pTemp[i] = m_pMat[i] + rhs.m_pMat[i];

	matrixSum.m_Rows = m_Rows;
	matrixSum.m_Cols = m_Cols;
	matrixSum.SetValue(pTemp, m_Rows, m_Cols);

	delete(pTemp);

	return matrixSum;
}

/*******************************************************************************
Primary Author: <yongmin.cho>

Parameters:
<rhs> : other matix to minus

Returns:
<matrixSum> : return caculated theirself matrix

Function Description:
return caculated theirself matrixs
*******************************************************************************/
Mat44 Mat44::operator-(const Mat44& rhs) const
{
	Mat44 matrixSum;
	float* pTemp = new float[m_Rows*m_Cols];

	/*if (m_Rows != rhs.m_Rows || m_Cols != rhs.m_Cols)
		return matrixSum;*/

	for (int i = 0; i < m_Rows*m_Cols; i++)
		pTemp[i] = m_pMat[i] - rhs.m_pMat[i];

	matrixSum.m_Rows = m_Rows;
	matrixSum.m_Cols = m_Cols;
	matrixSum.SetValue(pTemp, m_Rows, m_Cols);

	delete(pTemp);

	return matrixSum;
}

/*******************************************************************************
Primary Author: <yongmin.cho>

Parameters:
<rhs> : other matix to multiply

Returns:
<matrixSum> : return caculated theirself matrix

Function Description:
return caculated theirself matrixs
*******************************************************************************/
Mat44 Mat44::operator*(const float rhs) const
{
	Mat44 matrixSum;
	float* pTemp = new float[m_Rows*m_Cols];

	for (int i = 0; i < m_Rows*m_Cols; i++)
		pTemp[i] = rhs * m_pMat[i];

	matrixSum.m_Rows = m_Rows;
	matrixSum.m_Cols = m_Cols;
	matrixSum.SetValue(pTemp, m_Rows, m_Cols);

	delete(pTemp);

	return matrixSum;
}

/*******************************************************************************
Primary Author: <yongmin.cho>

Parameters:
<rhs> : other matix to divide

Returns:
<matrixSum> : return caculated theirself matrix

Function Description:
return caculated theirself matrixs
*******************************************************************************/
Mat44 Mat44::operator*(const Mat44& rhs) const
{
	Mat44 matrixSum;
	float* pTemp = new float[m_Rows*m_Cols];

	/*if (m_Cols != rhs.m_Rows)
		return matrixSum;*/

	for (int i = 0; i < m_Rows*rhs.m_Cols; i++)
		pTemp[i] = 0;

	for (int i = 0; i < m_Rows; i++)
	{
		for (int j = 0; j < rhs.m_Cols; j++)
		{
			for (int k = 0; k < m_Cols; k++)
				pTemp[i*rhs.m_Cols + j] += m_pMat[i*m_Cols + k] * rhs.m_pMat[j + k*rhs.m_Cols];
		}
	}
	matrixSum.SetValue(pTemp, m_Rows, rhs.m_Cols);

	delete(pTemp);

	return matrixSum;
}