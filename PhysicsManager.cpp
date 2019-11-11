/*******************************************************************************
All content (c)2015, DigiPen (USA) Corporation, all rights reserved.

Primary Author: <yongmin.cho>
Coproducers:
<name> : Sukjun Park

File Description:
Update all physics like position and velocity.
*******************************************************************************/
#include "Main.h"

const float MAXSPEED = 150.f;

/*******************************************************************************
Primary Author: <yongmin.cho>

Parameters:
<pB> : For changing Forces
<dt> : For adding velocity

Returns:
<return> : none

Function Description:
if rigidbody have zero mass, didn't move, else as Force change the velocity
*******************************************************************************/
void ApplyForces(RigidBody *pB, float dt)
{
	if (!pB->inv_mass)
		return;

	//b->vel += (b->force * b->inv_mass + gravity) * (dt);
	//b->angularVel += b->torque * b->inv_inertia * (dt);
	pB->vel += ((pB->force) * pB->inv_mass) * (dt / 2.f);

	//if (pB->ConnectTransform()->type == eCircle)
	//	DEBUG_PRINT("%f %f\n", pB->force.x, pB->force.y);
	pB->angularVel += pB->torque * pB->inv_inertia * (dt / 2.f);
}

/*******************************************************************************
Primary Author: <yongmin.cho>

Parameters:
<pB> : For changing Position
<dt> : For adding velocity

Returns:
<return> : none

Function Description:
if rigidbody have zero mass, didn't move, else as position change the velocity
*******************************************************************************/
const float limitVel = 100.f;
void ApplyVel(RigidBody *pB, float dt)
{
	if (!pB->inv_mass)
		return;
	if (pB->ConnectTransform()->type == eCircle)
	{
		Vector limitcheck = pB->vel;

		if (limitcheck.Length() >= limitVel)
		{
			pB->vel.Normalize();
			pB->vel *= limitVel;
		}
	}
	
	pB->ConnectTransform()->pos += pB->vel * dt;
	pB->orientation += pB->angularVel * dt;
	//pB->SetOrient(pB->orientation);
	//ApplyForces(pB, dt);
}

/*******************************************************************************
Primary Author: <yongmin.cho>

Parameters:
<pB> : For changing Position

Returns:
<return> : none

Function Description:
Make all force to zero
*******************************************************************************/
void ForceToZero(RigidBody *pB)
{
	RigidBody *pA = pB;
	pA->force.Set(0, 0);
	pA->torque = 0;
}

/*******************************************************************************
Primary Author: <yongmin.cho>

Parameters:
<param> : none

Returns:
<return> : none

Function Description:
Update all rigidbody
*******************************************************************************/
void PHYSICS_SPACE::UpdateRigidBody(void)
{
	manifold.clear();
	//collision check
	std::list<RigidBody*>::iterator end = RigidBody_space.end();
	//this Obj

	for (std::list<RigidBody*>::iterator currObj = RigidBody_space.begin();
		currObj != end; ++currObj)
	{
		RigidBody* currobj = *currObj;
		//other Obj
		for (std::list<RigidBody*>::iterator otherObj = currObj;
			otherObj != end; ++otherObj)
		{
			if (!(*currObj)->isCollisionOn || !(*otherObj)->isCollisionOn)
				continue;

			RigidBody* otherobj = *otherObj;

			//If error, return
			if (!currobj || !otherobj)
				continue;

			if (!currobj->inv_mass && !otherobj->inv_mass)
				continue;

			if (currobj != otherobj)
			{
				Manifold m(currobj, otherobj);
				m.Response();

				if (m.contact_count)
				{
					manifold.push_back(m);
					if (currobj->GetParent()->SearchComponent<Controller>() != NULL &&
						currobj->GetParent()->SearchComponent<Controller>()->isRecordPlaying == false)
					{
						//HAZARD PLATFORM

						if (currobj->GetParent()->SearchComponent<Controller>()->death <= 0 &&
							otherobj->GetParent()->SearchComponent<Platform>() != NULL &&
							otherobj->GetParent()->SearchComponent<Platform>()->mode == HAZARD)
							currobj->GetParent()->SearchComponent<Controller>()->death += 0.1f;

						//FIRE PLATFORM
						if (currobj->GetParent()->SearchComponent<Controller>()->fire <= 0 &&
							otherobj->GetParent()->SearchComponent<Platform>() != NULL &&
							otherobj->GetParent()->SearchComponent<Platform>()->mode == FIRE)
							currobj->GetParent()->SearchComponent<Controller>()->fire += FrameRateControl::Get()->GetDeltaTime();
						//WATER PLATFORM
						if (currobj->GetParent()->SearchComponent<Controller>()->fire > 0 && 
							otherobj->GetParent()->SearchComponent<Platform>() != NULL &&
							otherobj->GetParent()->SearchComponent<Platform>()->mode == WATER)
							currobj->GetParent()->SearchComponent<Controller>()->fire = 0;
					}
				}
			}
		}
	}

	for (int i = 0; i < static_cast<int>(manifold.size()); ++i)
	{
		manifold[i].Initialize();
	}

	//for (int i = 0; i < (int)manifold.size(); ++i)
	//{
	//	manifold[i].PositionalCorrection();
	//}

	/*for (int j = 0; j < 10; ++j)
	{*/
		for (int i = 0; i < static_cast<int>(manifold.size()); ++i)
		{
			manifold[i].ApplyImpulse();
		}
	//}

		for (std::list<RigidBody*>::iterator currObj = RigidBody_space.begin();
			currObj != end; ++currObj)
		{
			RigidBody* currobj = *currObj;
			ApplyVel(currobj, FrameRateControl::Get()->GetDeltaTime());
		}

	for (std::list<RigidBody*>::iterator currObj = RigidBody_space.begin();
		currObj != end; ++currObj)
	{
		//RigidBody* currobj = *currObj;
		//ForceToZero(currobj);
		/*if ((int)manifold.size() > 0 && currobj->GetParent()->SearchComponent<Controller>() != NULL && 
			currobj->GetParent()->SearchComponent<Controller>()->isRecordPlaying == false)
			currobj->GetParent()->SearchComponent<Controller>()->SaveRecord();*/
	}

}