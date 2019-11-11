/*******************************************************************************
All content (c)2015, DigiPen (USA) Corporation, all rights reserved.

Primary Author: <yongmin.cho>
Coproducers:
Sukjun Park : Intersection tests

File Description:
Check Collision.
*******************************************************************************/
#include "Main.h"

/*******************************************************************************
Primary Author: Sukjun Park

Parameters:
axis : the position of axis of rotation
pos : position of the target
degree : angle of the rotation

Returns:
Vector : rotated target's value.

Function Description:
Rotates a point with axis.
*******************************************************************************/
const Vector Rotate_by_Axis(const Vector axis, const Vector pos, const float degree)
{
	const Vector v = pos - axis;
	const float theta = degree * PI / 180;
	Vector vr(cosf(theta) * v.x - sinf(theta) * v.y, sinf(theta) * v.x + cosf(theta) * v.y);

	return axis + vr;
}


/*******************************************************************************
Primary Author: Sukjun Park

Parameters:
Point_pos : position of Point<ex) mouse Point>
Rectangle_pos : position of Rectangle
Rectangle_scale : scale of Rectangle
rotation : rotated angle of Rectangle

Returns:
<return> : true or false

Function Description:
if there are Intersect with Point and Rectangle, return true, else return false
*******************************************************************************/
const bool Intersection_Point_Rectangle_rot(const Vector Point_pos, const Vector Rectangle_pos, const Vector Rectangle_scale, const float rotation)
{
	Vector new_Point_pos = Rotate_by_Axis(Rectangle_pos,Point_pos,-rotation);

	return Intersection_Point_Rectangle(new_Point_pos, Rectangle_pos, Rectangle_scale);
}


/*******************************************************************************
Primary Author: <yongmin.cho>

Parameters:
<Point_pos> : position of Point<ex) mouse Point>
<Rectangle_pos> : position of Rectangle
<Rectangle_scale> : scale of Rectangle

Returns:
<return> : true or false

Function Description:
if there are Intersect with Point and Rectangle, return true, else return false
*******************************************************************************/
bool Intersection_Point_Rectangle(Vector Point_pos, Vector Rectangle_pos, Vector Rectangle_scale)
{
	Rectangle_scale *= 0.5f;

	//return true if point and rectangle given is intersecting.
	if (Point_pos.x < Rectangle_pos.x - Rectangle_scale.x)
		return false;
	else if (Point_pos.x > Rectangle_pos.x + Rectangle_scale.x)
		return false;
	else if (Point_pos.y > Rectangle_pos.y + Rectangle_scale.y)
		return false;
	else if (Point_pos.y < Rectangle_pos.y - Rectangle_scale.y)
		return false;
	else
		return true;
}

/*******************************************************************************
Primary Author: Sukjun Park

Parameters:
Rectangle1_pos   : rec1 pos 
Rectangle1_scale : rec1 scale
Rectangle1_pos   : rec2 pos
Rectangle1_scale : rec2 scale

Returns:
bool : return true if intersects

Function Description:
check intersection between rectangle and a rectangle.
*******************************************************************************/
bool Intersection_Rectangle_Rectangle(const Vector& Rectangle1_pos, const Vector& Rectangle1_scale, const Vector& Rectangle2_pos, const Vector& Rectangle2_scale)
{
	//return if intersecting
	if (Rectangle1_pos.x + Rectangle1_scale.x * 0.5f > Rectangle2_pos.x - Rectangle2_scale.x * 0.5f && Rectangle1_pos.x - Rectangle1_scale.x * 0.5f < Rectangle2_pos.x + Rectangle2_scale.x * 0.5f)
		if (Rectangle1_pos.y + Rectangle1_scale.y * 0.5f > Rectangle2_pos.y - Rectangle2_scale.y * 0.5f && Rectangle1_pos.y - Rectangle1_scale.y * 0.5f < Rectangle2_pos.y + Rectangle2_scale.y * 0.5f)
			return true;

	return false;
}

/*******************************************************************************
Primary Author: <yongmin.cho>

Parameters:
<Point_pos> : position of Point<ex) mouse Point>
<Cricle_pos> : position of Circle
<Circle_radius> : radius of Circle

Returns:
<return> : true or false

Function Description:
if there are Intersect with Point and Cricle, return true, else return false
*******************************************************************************/
bool Intersection_Point_Circle(Vector Point_pos, Vector Circle_pos, float Circle_radius)
{
	//return true if point and circle given is intersecting.
	float distance = sqrtf(powf((Point_pos.x - Circle_pos.x), 2) + powf((Point_pos.y - Circle_pos.y), 2));

	if (distance <= Circle_radius)
		return true;
	else
		return false;
}

bool Intersection_Circle_Circle(Vector Circle1_pos, float Circle1_radius, Vector Circle2_pos, float Circle2_radius)
{
	float distance = sqrtf(powf(Circle1_pos.x - Circle2_pos.x, 2) + powf(Circle1_pos.y - Circle2_pos.y, 2));

	if (distance <= Circle1_radius + Circle2_radius)
		return true;
	else return false;
}
/*******************************************************************************
Primary Author: <yongmin.cho>

Parameters:
<Cricle_pos> : position of Circle
<Circle_vel> : velocity of Circle
<Rect_pos> : position of Rectangle
<x_extent> : half scale of x of Rectangle
<y_extent> : half scale of x of Rectangle
<Circle_radius> : radius of Circle
<dt> : for next position

Returns:
<return> : true or false

Function Description:
if there are Intersect with Rectangle and Cricle, 
return true, else return false
*******************************************************************************/
bool Intersection_Circle_Rect(Vector Circle_pos, Vector Circle_vel, Vector Rect_pos, float x_extent, float y_extent, float Circle_radius, float dt)
{
	NOT_USING(dt);
	NOT_USING(Circle_vel);
	Vector nextPos;
	nextPos.x = Circle_pos.x;// +(Circle_vel.x * dt);
	nextPos.y = Circle_pos.y;// +(Circle_vel.y * dt);
	if (nextPos.x - Circle_radius <= Rect_pos.x + x_extent
		&& nextPos.x + Circle_radius >= Rect_pos.x - x_extent
		&& nextPos.y - Circle_radius <= Rect_pos.y + y_extent
		&& nextPos.y + Circle_radius >= Rect_pos.y - y_extent)
		return true;

	else return false;
}

/*******************************************************************************
Primary Author: <yongmin.cho>

Parameters:
<pM> : manifold what save collision data
<pA> : RigidBody for Circle
<pB> : RigidBody for other Circle

Returns:
<return> : none

Function Description:
if there are collision between pA and pB, save count and other in pM
*******************************************************************************/
void Intersection_CircletoCircle(Manifold *pM, RigidBody *pA, RigidBody *pB)
{
	Circle *pCircle1 = dynamic_cast<Circle *>(pA->m_pShape);
	Circle *pCircle2 = dynamic_cast<Circle *>(pB->m_pShape);

	if (!pCircle1 || !pCircle2)
		return;
	if (pCircle1->radius == 0 || pCircle2->radius == 0)
			return;
	Vector normal = pB->ConnectTransform()->pos - pA->ConnectTransform()->pos;

	float squaredDistance = normal.LengthSqr();
	float radius = pCircle1->radius + pCircle2->radius;

	if (squaredDistance >= radius * radius)
	{
		pM->contact_count = 0;
		return;
	}

	float distance = std::sqrt(squaredDistance);

	pM->contact_count = 1;

	Graphics::Get()->SetDebugmodePrint("Circle-Circle collided!");

	if (distance == 0.0f)
	{
		pM->penetration = pCircle1->radius;
		pM->normal = Vector(1, 0);
		pM->contacts[0] = pA->ConnectTransform()->pos;
	}
	else
	{
		pM->penetration = radius - distance;
		pM->normal = normal / distance;
		pM->contacts[0] = pM->normal * pCircle1->radius + pA->ConnectTransform()->pos;
	}
}

/*******************************************************************************
Primary Author: <yongmin.cho>

Parameters:
<pM> : manifold what save collision data
<pA> : RigidBody for Circle
<pB> : RigidBody for other Rectangle(PolygonShape)

Returns:
<return> : none

Function Description:
if there are collision between pA and pB, save count and other in pM
*******************************************************************************/
void Intersection_CircletoPolygon(Manifold *pM, RigidBody *pA, RigidBody *pB)
{
	Circle *pCircle = dynamic_cast<Circle *>(pA->m_pShape);
	PolygonShape *pPolygon = dynamic_cast<PolygonShape *>(pB->m_pShape);
	
	if (!pCircle || !pPolygon)
		return;

	pM->contact_count = 0;

	Vector center = pA->ConnectTransform()->pos; // Circle position
	center = pPolygon->mat22.Transpose() * (center - pB->ConnectTransform()->pos);

	float separation = -FLT_MAX;
	int faceNormal = 0;
	for (int i = 0; i < pPolygon->m_vertexCount; ++i)
	{
		float sper = Dot(pPolygon->m_normals[i], center - pPolygon->m_vertices[i]);

		if (sper > pCircle->radius)
			return;

		if (sper > separation)
		{
			separation = sper;
			faceNormal = i;
		}
	}

	Vector v1 = pPolygon->m_vertices[faceNormal];
	int i2 = faceNormal + 1 < pPolygon->m_vertexCount ? faceNormal + 1 : 0;

	Vector v2 = pPolygon->m_vertices[i2];

	if (separation < EPSILON)
	{
		Graphics::Get()->SetDebugmodePrint("Circle-Platform collided!");

		pM->contact_count = 1;
		pM->normal = -(pPolygon->mat22 * pPolygon->m_normals[faceNormal]);
		pM->contacts[0] = pM->normal * pCircle->radius + pA->ConnectTransform()->pos;
		pM->penetration = pCircle->radius;
		//pA->EdgeOn = true;
		return;
	}

	float dot1 = Dot(center - v1, v2 - v1);
	float dot2 = Dot(center - v2, v1 - v2);
	pM->penetration = pCircle->radius - separation;
	//Up Right Edge
	if (dot1 <= 0.0f)
	{
		if (DistanceSquared(center, v1) > pCircle->radius * pCircle->radius)
			return;
		Graphics::Get()->SetDebugmodePrint("Circle-Platform_edge collided!");
		pA->EdgeOn = true;
		pM->contact_count = 1;
		Vector normal = v1 - center;
		normal = pPolygon->mat22 * normal;
		normal.Normalize();
		pM->normal = normal;
		v1 = pPolygon->mat22 * v1 + pB->ConnectTransform()->pos;
		pM->contacts[0] = v1;
		return;
	}
	//Bottom left Edge
	else if (dot2 <= 0.0f)
	{
		if (DistanceSquared(center, v2) > pCircle->radius * pCircle->radius)
			return;
		
		Graphics::Get()->SetDebugmodePrint("Circle-Platform_edge collided!");
		pA->EdgeOn = true;
		pM->contact_count = 1;
		Vector normal = v2 - center;
		v2 = pPolygon->mat22 * v2 + pB->ConnectTransform()->pos;
		pM->contacts[0] = v2;
		normal = pPolygon->mat22 * normal;
		normal.Normalize();
		pM->normal = normal;
		return;
	}

	else
	{
		Vector normal = pPolygon->m_normals[faceNormal];
		if (Dot(center - v1, normal) > pCircle->radius)
			return;

		if (faceNormal == 0)
			pA->LineCheck = 0;
		else if (faceNormal == 1)
			pA->LineCheck = 1;
		if (faceNormal == 2)
			pA->LineCheck = 2;
		else if (faceNormal == 3)
			pA->LineCheck = 3;

		Graphics::Get()->SetDebugmodePrint("Circle-Platform collided!");

		normal = pPolygon->mat22 * normal;
		pM->normal = -normal;
		pM->contacts[0] = pM->normal * pCircle->radius + pA->ConnectTransform()->pos;
		pM->contact_count = 1;
		return;
	}
}