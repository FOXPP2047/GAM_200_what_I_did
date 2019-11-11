/*******************************************************************************
All content (c)2015, DigiPen (USA) Corporation, all rights reserved.

Primary Author: <yongmin.cho>
Coproducers:
<name> : Sukjun Park

File Description:
Header of Physics Manager.
*******************************************************************************/
#ifndef PHYSICSMANAGER_H 
#define PHYSICSMANAGER_H

#include <list>
#include <vector>
#include "Manifold.h"
class RigidBody;

class PHYSICS_SPACE
{
public:
	//space
	void UpdateRigidBody(void);
	std::list<RigidBody*> RigidBody_space;
	std::vector<Manifold> manifold;
};

void ApplyForces(RigidBody *b, float dt);
void ApplyVel(RigidBody *b, float dt);
void ForceToZero(RigidBody *b);
#endif