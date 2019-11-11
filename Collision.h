/*******************************************************************************
All content (c)2015, DigiPen (USA) Corporation, all rights reserved.

Primary Author: <yongmin.cho>
Coproducers:
<name> : none

File Description:
Header of Colllision.cpp
*******************************************************************************/
#ifndef INTERSECTION_H
#define INTERSECTION_H
//class decalaration
class Manifold;
class RigidBody;
const Vector Rotate_by_Axis(const Vector axis, const Vector pos, const float degree);
//boolean of Intersection.
bool Intersection_Point_Rectangle(Vector Point_pos, Vector Rectangle_pos, Vector Rectangle_scale);
bool Intersection_Rectangle_Rectangle(const Vector& Rectangle1_pos, const Vector& Rectangle1_scale, const Vector& Rectangle2_pos, const Vector& Rectangle2_scale);
const bool Intersection_Point_Rectangle_rot(const Vector Point_pos, const Vector Rectangle_pos, const Vector Rectangle_scale, const float rotation);
bool Intersection_Point_Circle(Vector Point_pos, Vector Circle_pos, float Circle_radius);
bool Intersection_Circle_Circle(Vector Circle1_pos, float Circle1_radius, Vector Circle2_pos, float Circle2_radius);
bool Intersection_Circle_Rect(Vector Circle_pos, Vector Circle_vel, Vector Rect_pos, float x_extent, float y_extent, float Circle_radius, float dt);
//void function to check Intersect between Circle to Circle and Circle to Rectangle.
void Intersection_CircletoCircle(Manifold *m, RigidBody *a, RigidBody *b);
void Intersection_CircletoPolygon(Manifold *m, RigidBody *a, RigidBody *b);
#endif