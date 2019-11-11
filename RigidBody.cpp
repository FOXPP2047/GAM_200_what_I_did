/*******************************************************************************
All content (c)2015, DigiPen (USA) Corporation, all rights reserved.

Primary Author: <yongmin.cho>
Coproducers:
<name> : Sukjun Park

File Description:
Make new Rigidbody, and give impusle like gravity
*******************************************************************************/
#include "Main.h"
#include "StateManager.h"
#include <iostream>

/*******************************************************************************
Primary Author: <yongmin.cho>

Parameters:
<param> : none


Returns:
<return> : none

Function Description:
destructor of RigidBody
*******************************************************************************/
RigidBody::~RigidBody(void)
{
	if (m_pShape)
	{
		delete m_pShape;
		m_pShape = 0;
	}
}

/*******************************************************************************
Primary Author: <yongmin.cho>

Parameters:
<param> : none


Returns:
<return> : none

Function Description:
As type, make other shape
*******************************************************************************/
void RigidBody::AddShape(void)
{
	if (!this->ConnectTransform())
		return;
	//std::cout << ConnectTransform()->type << std::endl;
	switch (this->ConnectTransform()->type)
	{
	case eCircle:
		m_pShape = new Circle;
		break;
	case ePoly:
		m_pShape = new PolygonShape();
		break;
	default:
		DEBUG_ASSERT(false, "not working");
		break;
	}
	m_pShape->pBody = this;
}

/*******************************************************************************
Primary Author: <yongmin.cho>

Parameters:
<impulse> : force that given from colllision

Returns:
<return> : none

Function Description:
give only velocity x to RigidBody
*******************************************************************************/
void RigidBody::SetVelocityX(Vector impulse)
{
	this->vel.x = impulse.x * inv_mass;
	this->vel.y += impulse.y * inv_mass;
}

/*******************************************************************************
Primary Author: <yongmin.cho>

Parameters:
<impulse> : force that given from colllision

Returns:
<return> : none

Function Description:
give only velocity y to RigidBody
*******************************************************************************/
void RigidBody::SetVelocityY(Vector impulse)
{
	this->vel.x += impulse.x * inv_mass;
	this->vel.y = impulse.y * inv_mass;
}
/*******************************************************************************
Primary Author: <yongmin.cho>

Parameters:
<impulse> : force that given from colllision
<contactVector> : Not using

Returns:
<return> : none

Function Description:
give only velocity to RigidBody
*******************************************************************************/
void RigidBody::SetVelocity(Vector impulse, Vector contactVector)
{
	NOT_USING(contactVector);
	this->vel = (impulse * inv_mass);
	//angularVel += inv_inertia * Cross(contactVector, impulse);
}

/*******************************************************************************
Primary Author: <yongmin.cho>

Parameters:
<impulse> : force that given from colllision
<contactVector> : make angular velocity

Returns:
<return> : none

Function Description:
give velocity and angular velocity to RigidBody
*******************************************************************************/
static const float limitVel = 100.f;
void RigidBody::SetImpulse(Vector impulse, Vector contactVector, int x)
{
	if (x == 1)
	{
		if (std::abs(impulse.x) > std::abs(impulse.y))
		{
			this->SetVelocityX(impulse);
			//this->vel.x = impulse.x * inv_mass;
			//this->vel.y += impulse.y * inv_mass;
		}

		else if (std::abs(impulse.x) <= std::abs(impulse.y))
		{
			this->SetVelocityY(impulse);
			//this->vel.x += impulse.x * inv_mass;
			//this->vel.y = impulse.y * inv_mass;
		}
	}
	else if (x == 2)
	{
		this->SetVelocityY(impulse);
	}

	else if (x == 0)
	{
		this->vel += impulse;
		//this->vel = impulse;
	}
	this->angularVel += inv_inertia * Cross(contactVector, impulse);
}

/*******************************************************************************
Primary Author: <yongmin.cho>

Parameters:
<param> : none

Returns:
<return> : none

Function Description:
Make a static rigidbody inertia and mass to zero
*******************************************************************************/
void RigidBody::SetStatic(void)
{
	inertia = 0.0f;
	inv_inertia = 0.0f;
	mass = 0.0f;
	inv_mass = 0.0f;
}

/*******************************************************************************
Primary Author: <yongmin.cho>

Parameters:
<radians> :  set angle of Rectangle

Returns:
<return> : none

Function Description:
set angle of Rectangle
*******************************************************************************/
void RigidBody::SetOrient(float radians)
{
	if (!m_pShape)
		return;

	orientation = radians;
	m_pShape->SetOrient(radians);
}

/*******************************************************************************
Primary Author: <yongmin.cho>

Parameters:
<OM> :  Not using

Returns:
<return> : none

Function Description:
As type of RigidBody, set radius or extent and so on
*******************************************************************************/
void RigidBody::Action(ObjectManager& OM)
{
	NOT_USING(OM);

	//set the values with transform
	pos = transform->pos;

	Circle* pCircle = 0;
	PolygonShape* pPolygon = 0;

	if (!m_pShape)
		return;

	switch (this->ConnectTransform()->type)
	{
	case eCircle:
		pCircle = dynamic_cast<Circle *>(m_pShape);
		this->inv_mass = 0.05f;
		//pCircle->Initialize();
		pCircle->radius = transform->scale.x * 0.5f;
		vel += ((gravity)* FrameRateControl::Get()->GetDeltaTime());
		//DEBUG_PRINT("%f, %f\n", gravity.x, gravity.y);
		break;

	case ePoly:
		pPolygon = dynamic_cast<PolygonShape *>(m_pShape);
		//pPolygon->Initialize();
		this->SetStatic();
		pPolygon->extent = transform->scale * 0.5f;
		pPolygon->SetOrient(transform->rotation * (PI / 180.f));
		pPolygon->SetBox(pPolygon->extent.x, pPolygon->extent.y);
		//if (this->GetParent()->SearchComponent<Platform>())
		//	DEBUG_PRINT("PosX : %f, PosY : %f\n", this->ConnectTransform()->pos.x, this->ConnectTransform()->pos.y);
		break;

	default:
		break;
	}
	//DEBUG_PRINT("%f, %f\n", OM.camera.pos.x, OM.camera.pos.y);
	//add vel to pos
	//ApplyVel(this, FrameRateControl::Get()->GetDeltaTime());



	///pos += vel * FrameRateControl::Get()->GetDeltaTime();
	//DEBUG_PRINT("%f %f\n", pos.x, pos.y);
	//pos to transform

	transform->pos = pos;

}

/*******************************************************************************
Primary Author: <yongmin.cho>

Parameters:
<OM> :  push_front to OM

Returns:
<return> : none

Function Description:
push_front to OM
*******************************************************************************/
void RigidBody::AddToSpace(ObjectManager& OM)
{
	OM.physics_space.RigidBody_space.push_front(this);
}