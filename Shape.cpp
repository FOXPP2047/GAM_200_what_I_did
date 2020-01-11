/*******************************************************************************
All content (c)2015, DigiPen (USA) Corporation, all rights reserved.

Primary Author: <yongmin.cho>
Coproducers:
<name> : none

File Description:
Calculate mass or inertia and calculate scope of Rectangle
*******************************************************************************/
#include "Main.h"

/*******************************************************************************
Primary Author: <yongmin.cho>

Parameters:
<param> : none

Returns:
<return> : none

Function Description:
caculate mass and inertia of Circle
*******************************************************************************/
void Circle::ComputeMass()
{
	pBody->mass = PI * radius * radius;
	pBody->inv_mass = 1 / pBody->mass;
	pBody->inertia = 0.5f * pBody->mass * radius * radius;
	pBody->inv_inertia = 1 / pBody->inertia;//(pBody->inertia) ? 1.0f / pBody->inertia : 0.0f;
}


/*******************************************************************************
Primary Author: <yongmin.cho>

Parameters:
<x_extent> : half width of Rectangle
<y_extent> : half height of Rectangle

Returns:
<return> : none

Function Description:
caculate scope of Rectangle and normal vector
*******************************************************************************/
void PolygonShape::SetBox(float x_extent, float y_extent)
{
	m_vertexCount = 4;
	m_vertices[0].Set(-x_extent, -y_extent);
	m_vertices[1].Set(x_extent, -y_extent);
	m_vertices[2].Set(x_extent, y_extent);
	m_vertices[3].Set(-x_extent, y_extent);
	m_normals[0].Set(0.0f, -1.0f);
	m_normals[1].Set(1.0f, 0.0f);
	m_normals[2].Set(0.0f, 1.0f);
	m_normals[3].Set(-1.0f, 0.0f);
}

/*******************************************************************************
Primary Author: <yongmin.cho>

Parameters:
<param> : none


Returns:
<return> : none

Function Description:
caculate mass and inertia of Rectangle
*******************************************************************************/
void PolygonShape::ComputeMass()
{
	Vector c(0.0f, 0.0f);
	float area = 0.0f;
	float I = 0.0f;
	const float inv_3 = 1.0f / 3.0f;

	for (int i1 = 0; i1 < m_vertexCount; ++i1)
	{
		Vector p1(m_vertices[i1]);
		int i2 = i1 + 1 < m_vertexCount ? i1 + 1 : 0;
		Vector p2(m_vertices[i2]);

		float D = Cross(p1, p2);
		float triangleArea = 0.5f * D;

		area += triangleArea;

		c += (p1 + p2) * triangleArea * inv_3;

		float intx2 = p1.x * p1.x + p2.x * p1.x + p2.x * p2.x;
		float inty2 = p1.y * p1.y + p2.y * p1.y + p2.y * p2.y;
		I += (0.25f * inv_3 * D) * (intx2 + inty2);
	}

	c *= 1.0f / area;

	for (int i = 0; i < m_vertexCount; ++i)
	m_vertices[i] -= c;

	pBody->mass = area;
	pBody->inv_mass = (pBody->mass) ? 1.0f / pBody->mass : 0.0f;
	pBody->inertia = I;
	pBody->inertia = (pBody->mass / 12) * (extent.x*extent.x)*(extent.y*extent.y);
	pBody->inv_inertia = 1 / pBody->inv_inertia;// pBody->inertia ? 1.0f / pBody->inertia : 0.0f;
}