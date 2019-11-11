#ifndef PHYSICS_H
#define PHYSICS_H

#include "math.h"
#include "RigidBody.h"

const float MAX = 2147483647.f;

class Circle
{
public:
		Circle();
		~Circle();
		void SetVelocity(float x, float y);
		void SetPosition(float x, float y);

		float radius;
		float mass;
		float gravity;
		float resititution;

		Vector circlePos;
		Vector circleVel;
};

class Rect
{
public:
		Rect();
		~Rect();
		void SetVelocity(float x, float y);
		void SetPosition(float x, float y);
		void SetPoint();

		float mass;
		float x_extent;
		float y_extent;
		float resititution;

		Vector point[4];
		Vector rectPos;
		Vector rectVel;
};

/*class Data
{
public:
Circle* pCircle1;
Circle* pCircle2;
Rect* pRect1;
Rect* pRect2;

float penetration;
Vector normal;
};*/

float Clamp(float min, float max, float value);

bool Intersection_Point_Rectangle(Vector Point_pos, Vector Rectangle_pos, Vector Rectangle_scale);
bool Intersection_Point_Circle(Vector Point_pos, Vector Circle_pos, float Circle_radius);
bool Intersection_Circle_Circle(Vector Circle1_pos, float Circle1_radius, Vector Circle2_pos, float Circle2_radius);
bool Intersection_Circle_Rect(Vector Circle_pos, Vector Circle_vel, Vector Rect_pos, float x_extent, float y_extent, float Circle_radius, float dt);
bool Intersection_Circle_Rect_Edge(Vector Circle_pos, Vector Rect_pos, float x_extent, float y_extent);
int LineCheck_Circle_Rect(Vector Circle_pos, Vector Rect_pos, float x_extent, float y_extent);

Vector GetUnitNormalVec(Vector Circle1_pos, Vector Circle2_pos);
Vector GetTangentNormalVec(Vector Circle1_pos, Vector Circle2_pos);
void Collision_Circle_Circle(RigidBody* pA, RigidBody* pB);
void Collision_Circle_Rect_Edge(RigidBody* pA, RigidBody* pB, float dt);
void Collision_Circle_Rect(RigidBody* pA, RigidBody* pB, float dt);
//void Collision_Circle_Rect_Edge(Circle* pA, Rect* pB, float dt);
//void Collision_Circle_Rect(Circle* pA, Rect* pB, float dt);
#endif