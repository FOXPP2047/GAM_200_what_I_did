#include "physics.h"
#include "Debug.h"
#include "FrameRateControl.h"
#include <cmath>

const float resititution = 50;

void Circle::SetVelocity(float x, float y)
{
		circleVel = { x, y };
}

void Circle::SetPosition(float x, float y)
{
		circlePos = { x, y };
}

void Rect::SetVelocity(float x, float y)
{
		rectVel = { x, y };
}

void Rect::SetPosition(float x, float y)
{
		rectPos = { x, y };
}

void Rect::SetPoint()
{
		point[0] = { rectPos.x + x_extent, rectPos.y + y_extent };
		point[1] = { rectPos.x - x_extent, rectPos.y + y_extent };
		point[2] = { rectPos.x - x_extent, rectPos.y - y_extent };
		point[3] = { rectPos.x + x_extent, rectPos.y - y_extent };
}

float Clamp(float min, float max, float value)
{
		if (value < min)
				value = min;

		else if (value > max)
				value = max;

		return value;
}

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
		//return true if circle and circle given is intersecting.
		float distance = sqrtf(powf((Circle1_pos.x - Circle2_pos.x), 2) + powf((Circle1_pos.y - Circle2_pos.y), 2));
		float sumofRadius = Circle1_radius + Circle2_radius;

		if (distance <= sumofRadius)
				return true;
		else
				return false;
}

bool Intersection_Circle_Rect(Vector Circle_pos, Vector Circle_vel, Vector Rect_pos, float x_extent, float y_extent, float Circle_radius, float dt)
{
		Vector nextPos;
		nextPos.x = Circle_pos.x + (Circle_vel.x * dt);
		nextPos.y = Circle_pos.y + (Circle_vel.y * dt);
		if (nextPos.x - Circle_radius <= Rect_pos.x + x_extent
				&& nextPos.x + Circle_radius >= Rect_pos.x - x_extent
				&& nextPos.y - Circle_radius <= Rect_pos.y + y_extent
				&& nextPos.y + Circle_radius >= Rect_pos.y - y_extent)
				return true;

		else return false;
}

bool Intersection_Circle_Rect_Edge(Vector Circle_pos, Vector Rect_pos, float x_extent, float y_extent)
{
		if (Circle_pos.x <= Rect_pos.x - x_extent
				&& Circle_pos.y >= Rect_pos.y + y_extent)
				return true;
		else if (Circle_pos.x >= Rect_pos.x + x_extent
				&& Circle_pos.y <= Rect_pos.y - y_extent)
				return true;
		else if (Circle_pos.x >= Rect_pos.x + x_extent
				&& Circle_pos.y >= Rect_pos.y + y_extent)
				return true;
		else if (Circle_pos.x <= Rect_pos.x - x_extent
				&& Circle_pos.y <= Rect_pos.y - y_extent)
				return true;
		else return false;
}

int LineCheck_Circle_Rect(Vector Circle_pos, Vector Rect_pos, float x_extent, float y_extent)
{
		if (Circle_pos.x >= Rect_pos.x + x_extent
				&& Circle_pos.y < Rect_pos.y + y_extent && Circle_pos.y > Rect_pos.y - y_extent)
				return 1;
		else if (Circle_pos.x <= Rect_pos.x - x_extent
				&& Circle_pos.y < Rect_pos.y + y_extent && Circle_pos.y > Rect_pos.y - y_extent)
				return 2;
		else if (Circle_pos.y >= Rect_pos.y + y_extent
				&& Circle_pos.x < Rect_pos.x + x_extent && Circle_pos.x > Rect_pos.x - x_extent)
				return 3;
		else if (Circle_pos.y <= Rect_pos.y - y_extent
				&& Circle_pos.x < Rect_pos.x + x_extent && Circle_pos.x > Rect_pos.x - x_extent)
				return 4;
		else return 0;
}

Vector GetUnitNormalVec(Vector Circle1_pos, Vector Circle2_pos)
{
		Vector unitNormal = Circle2_pos - Circle1_pos;

		unitNormal.x /= sqrt(powf(unitNormal.x, 2) + powf(unitNormal.y, 2));
		unitNormal.y /= sqrt(powf(unitNormal.x, 2) + powf(unitNormal.y, 2));

		return unitNormal;
}

Vector GetTangentNormalVec(Vector Circle1_pos, Vector Circle2_pos)
{
		Vector unitTangent = GetUnitNormalVec(Circle1_pos, Circle2_pos);

		unitTangent.x = unitTangent.y;
		unitTangent.y = -unitTangent.x;

		return unitTangent;
}

void Collision_Circle_Circle(RigidBody* pA, RigidBody* pB)
{
	if (!pA || !pB)
		return;

	//Normal Vector
	Vector N;
	N.x = pB->pos.x - pA->pos.x;
	N.y = pB->pos.y - pA->pos.y;

	//Unit Normal Vector
	Vector UN;
	UN.x = N.x / sqrtf(N.x * N.x + N.y * N.y);
	UN.y = N.y / sqrtf(N.x * N.x + N.y * N.y);

	//Unit Tangent Vector
	Vector UT;
	UT.x = -UN.y;
	UT.y = UN.x;

	//Scalar Velocity in normal direction
	Vector SN;
	SN.x = DotProduct(pA->vel, UN);
	SN.y = DotProduct(pB->vel, UN);

	//Scalar Velocity in tangent direction
	Vector ST;
	ST.x = DotProduct(pA->vel, UT);
	ST.y = DotProduct(pB->vel, UT);

	//New Tangential Velocity
	Vector NST = ST;

	//New Normal Velocity
	Vector NSN;
	NSN.x = (SN.x*(pA->mass - pB->mass) + 2 * pB->mass*SN.y) / (pA->mass + pB->mass);
	NSN.y = (SN.y*(pB->mass - pA->mass) + 2 * pA->mass*SN.x) / (pA->mass + pB->mass);

	//New Vector in normal direction for obj 
	Vector NVNobj;
	NVNobj.x = NSN.x * UN.x;
	NVNobj.y = NSN.x * UN.y;

	//New Vector in normal direction for target
	Vector NVNtarget;
	NVNtarget.x = NSN.y * UN.x;
	NVNtarget.y = NSN.y * UN.y;

	//New Vector in normal direction for obj 
	Vector NVTobj;
	NVTobj.x = NST.x * UT.x;
	NVTobj.y = NST.x * UT.y;

	//New Vector in normal direction for target
	Vector NVTtarget;
	NVTtarget.x = NST.y * UT.x;
	NVTtarget.y = NST.y * UT.y;

	//New Vector for obj
	Vector NVobj;
	NVobj.x = NVNobj.x + NVTobj.x;
	NVobj.y = NVNobj.y + NVTobj.y;

	//New Vector for target
	Vector NVtarget;
	NVtarget.x = NVNtarget.x + NVTtarget.x;
	NVtarget.y = NVNtarget.y + NVTtarget.y;

		pA->vel = NVobj;
		pB->vel = NVtarget;

	//float S1n = DotProduct(pA->vel, GetUnitNormalVec(pA->pos, pB->pos));
	//float S2n = DotProduct(pB->vel, GetUnitNormalVec(pA->pos, pB->pos));
	//float S1t = DotProduct(pA->vel, GetTangentNormalVec(pA->pos, pB->pos));
	//float S2t = DotProduct(pB->vel, GetTangentNormalVec(pA->pos, pB->pos));
	//float NewS1n = (S1n*(pA->mass - pB->mass) + 2 * pB->mass*S2n) / (pA->mass + pB->mass);
	//float NewS2n = (S2n*(pB->mass - pA->mass) + 2 * pA->mass*S1n) / (pA->mass + pB->mass);
	//float NewS1t = S1t;
	//float NewS2t = S2t;

	//pA->vel = (GetUnitNormalVec(pA->pos, pB->pos) * NewS1n + GetTangentNormalVec(pA->pos, pB->pos) * NewS1t);
	//pB->vel = (GetUnitNormalVec(pA->pos, pB->pos) * NewS2n + GetTangentNormalVec(pA->pos, pB->pos) * NewS2t);
}

void Collision_Circle_Rect_Edge(RigidBody* pA, RigidBody* pB, float dt)
{
	const float left = pB->pos.x - pB->extent.x;
	const float right = pB->pos.x + pB->extent.x;
	const float bottom = pB->pos.y - pB->extent.y;
	const float top = pB->pos.y + pB->extent.y;

	Vector nextPos;
	nextPos.x = pA->pos.x + (pA->vel.x * dt);
	nextPos.y = pA->pos.y + (pA->vel.y * dt);

	float dx = nextPos.x - pA->pos.x;
	float dy = nextPos.y - pA->pos.y;
	float ltime = MAX;
	float rtime = MAX;
	float ttime = MAX;
	float btime = MAX;


	if (pA->pos.x - pA->radius < left && nextPos.x + pA->radius > left)
	{
		ltime = ((left - pA->radius) - pA->pos.x) / dx;
	}

	if (pA->pos.x + pA->radius > right && nextPos.x - pA->radius < right)
	{
		rtime = (pA->pos.x - (right + pA->radius)) / -dx;
	}
	if (pA->pos.y - pA->radius < top && nextPos.y + pA->radius > top)
	{
		ttime = ((top - pA->radius) - pA->pos.y) / dy;
	}
	if (pA->pos.y + pA->radius > bottom && nextPos.y - pA->radius < bottom)
	{
		btime = (pA->pos.y - (bottom + pA->radius)) / -dy;
	}

	float cornerX = MAX;
	float cornerY = MAX;

	if (ltime != MAX)
		cornerX = left;

	else if (rtime != MAX)
		cornerX = right;

	if (ttime != MAX)
		cornerY = top;

	else if (btime != MAX)
		cornerY = bottom;

	if (cornerX != MAX && cornerY == MAX)
		cornerY = (dy > 0.0f ? bottom : top);

	if (cornerY != MAX && cornerX == MAX)
		cornerX = (dx > 0.0f ? right : left);

	double lineLength = sqrt(dx * dx + dy * dy);
	double cornerdx = cornerX - pA->pos.x;
	double cornerdy = cornerY - pA->pos.y;
	double cornerdist = sqrt(cornerdx * cornerdx + cornerdy * cornerdy);
	double innerAngle = acos((cornerdx * dx + cornerdy * dy) / (lineLength * cornerdist));
	double innerAngleSin = sin(innerAngle);
	double angle1Sin = innerAngleSin * cornerdist * (1 / pA->radius);

	if (ABS((float)angle1Sin) > 1.0f)
		return;

	double angle1 = PI - asin(angle1Sin);
	double angle2 = PI - innerAngle - angle1;
	double intersectionDistance = pA->radius * sin(angle2) / innerAngleSin;

	float time = (float)(intersectionDistance / lineLength);

	if (time > 1.0f || time < 0.0f)
		return;

	float ix = time * dx + pA->pos.x;
	float iy = time * dy + pA->pos.y;
	float nx = (float)((ix - cornerX) * (1 / pA->radius));
	float ny = (float)((iy - cornerY) * (1 / pA->radius));

	float scalar = sqrtf(powf(pA->vel.x, 2) + powf(pA->vel.y, 2));
	pA->vel = { nx * scalar, ny * scalar };
}

void Collision_Circle_Rect(RigidBody* pA, RigidBody* pB, float dt)
{
	Vector nextPos;
	nextPos.x = pA->pos.x + (pA->vel.x * dt);
	nextPos.y = pA->pos.y + (pA->vel.y * dt);

	Vector collisionPos;

	if (LineCheck_Circle_Rect(pA->pos, pB->pos, pB->extent.x, pB->extent.y) == 1)
	{
		collisionPos.x = (pB->pos.x + pB->extent.x) + pA->radius;
		collisionPos.y = pA->pos.y + (nextPos.y - pA->pos.y) * (collisionPos.x - pA->pos.x) / (nextPos.x - pA->pos.y);
		pA->pos.x = collisionPos.x;
		pA->pos.y = collisionPos.y;
		pA->vel.x *= -1;
	}

	else if (LineCheck_Circle_Rect(pA->pos, pB->pos, pB->extent.x, pB->extent.y) == 2)
	{
		collisionPos.x = (pB->pos.x - pB->extent.x) - pA->radius;
		collisionPos.y = pA->pos.y + (nextPos.y - pA->pos.y) * (collisionPos.x - pA->pos.x) / (nextPos.x - pA->pos.y);
		pA->pos.x = collisionPos.x;
		pA->pos.y = collisionPos.y;
		pA->vel.x *= -1;
	}
	else if (LineCheck_Circle_Rect(pA->pos, pB->pos, pB->extent.x, pB->extent.y) == 3)
	{
		collisionPos.y = (pB->pos.y + pB->extent.y) + pA->radius;
		collisionPos.x = pA->pos.x + (nextPos.x - pA->pos.x) * (collisionPos.y - pA->pos.y) / (nextPos.y - pA->pos.y);
		pA->pos.x = collisionPos.x;
		pA->pos.y = collisionPos.y;
		pA->vel.y = resititution;
	}
	else if (LineCheck_Circle_Rect(pA->pos, pB->pos, pB->extent.x, pB->extent.y) == 4)
	{
		collisionPos.y = (pB->pos.y - pB->extent.y) - pA->radius;
		collisionPos.x = pA->pos.x + (nextPos.x - pA->pos.x) * (collisionPos.y - pA->pos.y) / (nextPos.y - pA->pos.y);
		pA->pos.x = collisionPos.x;
		pA->pos.y = collisionPos.y;
		pA->vel.y = -resititution;
	}

}

/*void Collision_Circle_Rect_Edge(Circle* pA, Rect* pB, float dt)
{
		const float left = pB->rectPos.x - pB->x_extent;
		const float right = pB->rectPos.x + pB->x_extent;
		const float bottom = pB->rectPos.y - pB->y_extent;
		const float top = pB->rectPos.y + pB->y_extent;

		Vector nextPos;
		nextPos.x = pA->circlePos.x + (pA->circleVel.x * dt);
		nextPos.y = pA->circlePos.y + (pA->circleVel.y * dt);

		float dx = nextPos.x - pA->circlePos.x;
		float dy = nextPos.y - pA->circlePos.y;
		float ltime = MAX;
		float rtime = MAX;
		float ttime = MAX;
		float btime = MAX;


		if (pA->circlePos.x - pA->radius < left && nextPos.x + pA->radius > left)
		{
				ltime = ((left - pA->radius) - pA->circlePos.x) / dx;
		}

		if (pA->circlePos.x + pA->radius > right && nextPos.x - pA->radius < right)
		{
				rtime = (pA->circlePos.x - (right + pA->radius)) / -dx;
		}
		if (pA->circlePos.y - pA->radius < top && nextPos.y + pA->radius > top)
		{
				ttime = ((top - pA->radius) - pA->circlePos.y) / dy;
		}
		if (pA->circlePos.y + pA->radius > bottom && nextPos.y - pA->radius < bottom)
		{
				btime = (pA->circlePos.y - (bottom + pA->radius)) / -dy;
		}

		float cornerX = MAX;
		float cornerY = MAX;

		if (ltime != MAX)
				cornerX = left;

		else if (rtime != MAX)
				cornerX = right;

		if (ttime != MAX)
				cornerY = top;

		else if (btime != MAX)
				cornerY = bottom;

		if (cornerX != MAX && cornerY == MAX)
				cornerY = (dy > 0.0f ? bottom : top);

		if (cornerY != MAX && cornerX == MAX)
				cornerX = (dx > 0.0f ? right : left);

		double lineLength = sqrt(dx * dx + dy * dy);
		double cornerdx = cornerX - pA->circlePos.x;
		double cornerdy = cornerY - pA->circlePos.y;
		double cornerdist = sqrt(cornerdx * cornerdx + cornerdy * cornerdy);
		double innerAngle = acos((cornerdx * dx + cornerdy * dy) / (lineLength * cornerdist));
		double innerAngleSin = sin(innerAngle);
		double angle1Sin = innerAngleSin * cornerdist * (1 / pA->radius);

		if (ABS((float)angle1Sin) > 1.0f)
				return;

		double angle1 = PI - asin(angle1Sin);
		double angle2 = PI - innerAngle - angle1;
		double intersectionDistance = pA->radius * sin(angle2) / innerAngleSin;

		float time = (float)(intersectionDistance / lineLength);

		if (time > 1.0f || time < 0.0f)
				return;

		float ix = time * dx + pA->circlePos.x;
		float iy = time * dy + pA->circlePos.y;
		float nx = (float)((ix - cornerX) * (1 / pA->radius));
		float ny = (float)((iy - cornerY) * (1 / pA->radius));

		float scalar = sqrtf(powf(pA->circleVel.x, 2) + powf(pA->circleVel.y, 2));
		pA->circleVel = { nx * scalar, ny * scalar };
}

void Collision_Circle_Rect(Circle* pA, Rect* pB, float dt)
{
		Vector nextPos;
		nextPos.x = pA->circlePos.x + (pA->circleVel.x * dt);
		nextPos.y = pA->circlePos.y + (pA->circleVel.y * dt);

		Vector collisionPos;

		if (LineCheck_Circle_Rect(pA->circlePos, pB->rectPos, pB->x_extent, pB->y_extent) == 1)
		{
				collisionPos.x = (pB->rectPos.x + pB->x_extent) + pA->radius;
				collisionPos.y = pA->circlePos.y + (nextPos.y - pA->circlePos.y) * (collisionPos.x - pA->circlePos.x) / (nextPos.x - pA->circlePos.y);
				pA->circlePos.x = collisionPos.x;
				pA->circlePos.y = collisionPos.y;
				pA->circleVel.x *= -1;
		}

		else if (LineCheck_Circle_Rect(pA->circlePos, pB->rectPos, pB->x_extent, pB->y_extent) == 2)
		{
				collisionPos.x = (pB->rectPos.x - pB->x_extent) - pA->radius;
				collisionPos.y = pA->circlePos.y + (nextPos.y - pA->circlePos.y) * (collisionPos.x - pA->circlePos.x) / (nextPos.x - pA->circlePos.y);
				pA->circlePos.x = collisionPos.x;
				pA->circlePos.y = collisionPos.y;
				pA->circleVel.x *= -1;
		}
		else if (LineCheck_Circle_Rect(pA->circlePos, pB->rectPos, pB->x_extent, pB->y_extent) == 3)
		{
				collisionPos.y = (pB->rectPos.y + pB->y_extent) + pA->radius;
				collisionPos.x = pA->circlePos.x + (nextPos.x - pA->circlePos.x) * (collisionPos.y - pA->circlePos.y) / (nextPos.y - pA->circlePos.y);
				pA->circlePos.x = collisionPos.x;
				pA->circlePos.y = collisionPos.y;
				pA->circleVel.y *= -1;
		}
		else if (LineCheck_Circle_Rect(pA->circlePos, pB->rectPos, pB->x_extent, pB->y_extent) == 4)
		{
				collisionPos.y = (pB->rectPos.y - pB->y_extent) - pA->radius;
				collisionPos.x = pA->circlePos.x + (nextPos.x - pA->circlePos.x) * (collisionPos.y - pA->circlePos.y) / (nextPos.y - pA->circlePos.y);
				pA->circlePos.x = collisionPos.x;
				pA->circlePos.y = collisionPos.y;
				pA->circleVel.y *= -1;
		}
}*/