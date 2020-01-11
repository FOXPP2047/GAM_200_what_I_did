/*******************************************************************************
All content (c)2015, DigiPen (USA) Corporation, all rights reserved.

Primary Author: <yongmin.cho>
Coproducers:
<name> : none

File Description:
Header of Shape.cpp
*******************************************************************************/
#ifndef SHAPE_H
#define SHAPE_H

class RigidBody;

#define MaxVertex 4

enum ShapeType
{
	eNone,
	eCircle,
	ePoly,
	eTexture,
	eFont
};

class Shape
{
public:
	Shape() : radius(0), extent(0), mat22(0) {}
	virtual Shape *Copy(void) const = 0;
	virtual void Initialize(void) = 0;
	virtual void ComputeMass(void) = 0;
	virtual void SetOrient(float radians) = 0;
	virtual ShapeType GetType(void) const = 0;

	RigidBody* pBody;
	float radius;
	Vector extent;
	Mat2 mat22;
};

class Circle : public Shape
{
public:
	Circle() {}
	Circle(float r) { radius = r; }

	Shape *Copy(void) const { return new Circle(radius); }

	void Initialize(void) { /*ComputeMass();*/ }

	void ComputeMass(void);

	void SetOrient(float radians){ radians; }

	ShapeType GetType(void) const { return eCircle; }
};

class PolygonShape : public Shape
{
public:
	PolygonShape() {}
	int m_vertexCount;
	Vector m_vertices[MaxVertex];
	Vector m_normals[MaxVertex];

	void Initialize(void) { /*ComputeMass();*/ }

	Shape *Copy(void) const
	{
		PolygonShape *pPoly = new PolygonShape();
		pPoly->mat22 = mat22;
		for (int i = 0; i < m_vertexCount; ++i)
		{
			pPoly->m_vertices[i] = m_vertices[i];
			pPoly->m_normals[i] = m_normals[i];
		}
		pPoly->m_vertexCount = m_vertexCount;
		return pPoly;
	}

	void SetBox(float x_extent, float y_extent);

	void ComputeMass(void);


	void SetOrient(float radians) { mat22.Set(radians); }

	ShapeType GetType(void) const { return ePoly; }
};

#endif