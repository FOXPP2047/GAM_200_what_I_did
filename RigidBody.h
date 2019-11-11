/*******************************************************************************
All content (c)2015, DigiPen (USA) Corporation, all rights reserved.

Primary Author: <yongmin.cho>
Coproducers:
<name> : Sukjun Park

File Description:
Header of RigidBody
*******************************************************************************/
#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include <typeinfo>
#include "Component.h"
#include "math.h"
#include "Graphics.h"
#include "Shape.h"
class ObjectManager;

template <typename T>
class SPACE;
class ObjectManager;
class Transform;

class RigidBody : public Component
{
public:
	RigidBody() : pos(0), vel(0), force(0), acc(0), orientation(0), angularVel(0), torque(0), mass(20), inertia(10), m_pShape(0), staticFriction(0.5f)
		, dynamicFriction(0.3f), restitution(1.f), transform(0), isCollisionOn(true), isRecordingOn(false), Spring(false), LineCheck(4), EdgeOn(false) {}
	~RigidBody(void);
	virtual void Action(ObjectManager& OM);
	virtual const char* GetComponentType(void) { return typeid(this).name(); }
	void AddToSpace(ObjectManager& OM);
	void ConnectTo(Transform* ptransform) { transform = ptransform; }

	void AddShape(void);
	Transform* ConnectTransform(void) { return transform; }

	void SetVelocity(Vector impulse, Vector contactVector);
	void SetVelocityX(Vector impulse);
	void SetVelocityY(Vector impulse);
	void SetImpulse(Vector impulse, Vector contactVector, int x);
	void SetStatic(void);
	void SetOrient(float radians);
	Shape* m_pShape;

	Vector pos;
	Vector vel;
	Vector force;

	float acc;

	float orientation;
	float angularVel;
	float torque;
	float mass;
	float inv_mass;
	float inertia;
	float inv_inertia = 1 / inertia;

	float staticFriction;
	float dynamicFriction;
	float restitution;
	bool Spring;
	bool EdgeOn;
	int LineCheck;
	bool isCollisionOn;
	bool isRecordingOn;
private:
	Transform* transform;
};
#endif