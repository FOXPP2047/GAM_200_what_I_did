/*******************************************************************************
All content (c)2015, DigiPen (USA) Corporation, all rights reserved.

Primary Author: <yongmin.cho>
Coproducers:
<name> : none

File Description:
Header of Manifold.cpp
*******************************************************************************/
#ifndef MANIFOLD_H
#define MANIFOLD_H
#include "Singleton.hpp"
class RigidBody;

class MEmitter : public Singleton<MEmitter>
{
public:
    bool RB_RB = false;
    bool CB_RB = false;
    bool CB_Platform = false;
    bool RB_Platform = false;
		bool waterfall = false;
		bool fire = false;
};

class Manifold
{
public:
    Manifold() {};
    ~Manifold() {};
	Manifold(RigidBody* pA, RigidBody* pB) : m_pA(pA), m_pB(pB), contact_count(0) { /*Audio::Get()->LoadAudio();*/ }
	//~Manifold() { Audio::Get()->ReleaseAudio(); }
	RigidBody* m_pA;
	RigidBody* m_pB;

	float penetration;
	Vector normal;
	Vector contacts[2];
	int contact_count;
	float min_restitution;
	float dynamic_friction;
	float static_friction;

	void Response(void);
	void Initialize(void);
	void ApplyImpulse(void);
	void PositionalCorrection(void);
	void InfiniteMassCorrection(void);
	void SetForceToZero(void);
};
#endif