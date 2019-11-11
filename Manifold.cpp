/*******************************************************************************
All content (c)2015, DigiPen (USA) Corporation, all rights reserved.

Primary Author: <yongmin.cho>
Coproducers:
<name> : none

File Description:
Call Collision function check collision, give impusle when they are collision
*******************************************************************************/
#include "Main.h"
#include <string>

/*******************************************************************************
Primary Author: <yongmin.cho>

Parameters:
<param> : none

Returns:
<return> : none

Function Description:
check two type of RigidBody, call other Intersection function and check
*******************************************************************************/
void Manifold::Response(void)
{
	if (m_pA->ConnectTransform()->type == eCircle && m_pB->ConnectTransform()->type == eCircle)
	{
		Intersection_CircletoCircle(this, m_pA, m_pB);
		return;
	}
	else if (m_pA->ConnectTransform()->type == eCircle && m_pB->ConnectTransform()->type == ePoly)
	{
		Intersection_CircletoPolygon(this, m_pA, m_pB);
		return;
	}
	else if (m_pA->ConnectTransform()->type == ePoly && m_pB->ConnectTransform()->type == eCircle)
	{
		normal = -normal;
		Intersection_CircletoPolygon(this, m_pB, m_pA);
		return;
	}
}

/*******************************************************************************
Primary Author: <yongmin.cho>

Parameters:
<param> : none

Returns:
<return> : none

Function Description:
Initiailize Manifold data, like restitution or friction
*******************************************************************************/
void Manifold::Initialize(void)
{
	if (m_pA->restitution <= m_pB->restitution)
		min_restitution = m_pA->restitution;
	else min_restitution = m_pB->restitution;

	static_friction = m_pA->staticFriction;
	dynamic_friction = m_pA->dynamicFriction;

	for (int i = 0; i < contact_count; ++i)
	{
		Vector ra = contacts[i] - m_pA->pos;
		Vector rb = contacts[i] - m_pB->pos;

		Vector relativeVel = m_pB->vel + Cross(m_pB->angularVel, rb) -
			m_pA->vel - Cross(m_pA->angularVel, ra);

		if (relativeVel.LengthSqr() - (gravity * FrameRateControl::Get()->GetDeltaTime()).LengthSqr() < EPSILON)
			min_restitution = 0.0f;
	}
}

/*******************************************************************************
Primary Author: <yongmin.cho>

Parameters:
<param> : none

Returns:
<return> : none

Function Description:
With Collision data, give impusle to RigidBody
*******************************************************************************/
void Manifold::ApplyImpulse(void)
{
	if (Equal(m_pA->inv_mass + m_pB->inv_mass, 0))
	{
		InfiniteMassCorrection();
		return;
	}

	static Vector fakeVel = 0;
	for (int i = 0; i < contact_count; ++i)
	{
		Vector ra = contacts[i] - m_pA->pos;
		Vector rb = contacts[i] - m_pB->pos;
		Vector rv = 0;
		if (m_pA->ConnectTransform()->type == eCircle)
		{
			m_pA->inv_mass = 0.05f;
		}
			
		else if (m_pB->ConnectTransform()->type == eCircle)
		{
			m_pB->inv_mass = 0.05f;
		}

		if (m_pA->ConnectTransform()->type == eCircle && m_pA->vel.x == 0.0f)
			rv = m_pB->vel + Cross(m_pB->angularVel, rb) - (m_pA->vel + 0.00001f) - Cross(m_pA->angularVel, ra);
		else if (m_pB->ConnectTransform()->type == eCircle && m_pB->vel.x == 0.0f)
			rv = (m_pB->vel + 0.00001f) + Cross(m_pB->angularVel, rb) - m_pA->vel - Cross(m_pA->angularVel, ra);
		else
			rv = (m_pB->vel) + Cross(m_pB->angularVel, rb) - m_pA->vel - Cross(m_pA->angularVel, ra);
		float contactVel = Dot(rv, normal);

		if (contactVel >= 0)
			return;

		float raCrossN = Cross(ra, normal);
		float rbCrossN = Cross(rb, normal);
		float invMassSum = m_pA->inv_mass + m_pB->inv_mass + Squared(raCrossN) * m_pA->inv_inertia + Squared(rbCrossN) * m_pB->inv_inertia;

		float scalar_impusle = -(1.0f + min_restitution) * contactVel;

		scalar_impusle /= invMassSum;
		scalar_impusle /= (float)contact_count;

		const float Edge_Spring = 1500;
		const float Ball_Spring = 1500;
		const float BALLTWOBALL = 1000;

		Vector impulse_j = normal * scalar_impusle;
		Vector impulse_Edge = normal * Edge_Spring;
		Vector impulse = normal * Ball_Spring;
		Vector twoImpulse = normal * BALLTWOBALL;

		if (m_pA->ConnectTransform()->type == eCircle && m_pB->ConnectTransform()->type == eCircle)
		{
			if (!m_pA->isRecordingOn || !m_pB->isRecordingOn)
			{
				//Good
				MEmitter::Get()->CB_RB = true;
			}

			else if (m_pA->isRecordingOn && m_pB->isRecordingOn)
			{
				MEmitter::Get()->RB_RB = true;
				return;
			}

			if (!m_pA->isRecordingOn && m_pB->isRecordingOn)
			{
				if (std::abs(m_pA->ConnectTransform()->pos.x - m_pB->ConnectTransform()->pos.x) <= 0.01f)
					m_pA->ConnectTransform()->pos.x += 0.1f;
				if (std::abs(m_pA->ConnectTransform()->pos.y - m_pB->ConnectTransform()->pos.y) <= 0.01f)
					m_pA->ConnectTransform()->pos.y += 0.1f;
				//if (std::abs(m_pA->ConnectTransform()->pos.y - m_pB->ConnectTransform()->pos.y) < 7
				//	&& std::abs(m_pA->ConnectTransform()->pos.x - m_pB->ConnectTransform()->pos.x) < 7)
				//	DEBUG_PRINT("PYA PYA\n");
				Vector n = m_pA->ConnectTransform()->pos - m_pB->ConnectTransform()->pos;
				//n.Normalize();
				float p = ((Dot(m_pA->vel, n) - Dot(m_pB->vel, n)) * 2.f) / (m_pA->mass + m_pB->mass);
				static Vector w;
				w = /*m_pA->vel*/ - n * p * m_pA->mass;
				//DEBUG_PRINT("%f, %f\n", w.x, w.y);
				m_pA->SetImpulse(w, ra, 0);
				return;
			}
		}

		else if (m_pA->ConnectTransform()->type == eCircle && m_pB->ConnectTransform()->type == ePoly)
		{
			Platform* p = m_pB->GetParent()->SearchComponent<Platform>();

			if (!p)
				return;

			if (p->mode == FIRE)
			{
				SoundSystem::Get()->Play_Sound(SoundSystem::Get()->id_fire, false);
			}

			if (p->mode == NORMAL || p->mode == HAZARD || p->mode == WATER)
			{
				if (p->mode == WATER)
				{
					SoundSystem::Get()->Play_Sound(SoundSystem::Get()->id_waterfall, false);
				}
					//MEmitter::Get()->waterfall = true;

				else
				{
					if (m_pA->isRecordingOn)
					{
						//SA_BOUNCE_RBALL_PLATFORM
						MEmitter::Get()->RB_Platform = true;
					}

					else if (!m_pA->isRecordingOn)
					{
						//SA_BOUNCE_CBALL_PLATFORM
						MEmitter::Get()->CB_Platform = true;
					}
				}
			}
			impulse_j.Normalize();
			impulse_j *= Ball_Spring;


			if (p->mode == NORMAL || p->mode == HAZARD || p->mode == WATER)
			{
				if ((std::abs(m_pB->ConnectTransform()->rotation) >= 0 && std::abs(m_pB->ConnectTransform()->rotation) < 45))
				{
					m_pA->SetImpulse(-impulse_j, ra, 1);
					m_pB->SetImpulse(impulse_j, rb, 1);

				}

				else
				{
					//DEBUG_PRINT("%f\n", m_pB->ConnectTransform()->rotation);
					m_pA->SetImpulse(-impulse_j, ra, 2);
					m_pB->SetImpulse(impulse_j, rb, 2);
				}
			}
		}

		else if (m_pA->ConnectTransform()->type == ePoly && m_pB->ConnectTransform()->type == eCircle)
		{
			Platform* p = m_pA->GetParent()->SearchComponent<Platform>();

			if (!p)
				return;

			if (p->mode == FIRE)
			{
				SoundSystem::Get()->Play_Sound(SoundSystem::Get()->id_fire, false);
			}

			if (p->mode == NORMAL || p->mode == HAZARD || p->mode == WATER)
			{
				if (p->mode == WATER)
				{
					SoundSystem::Get()->Play_Sound(SoundSystem::Get()->id_waterfall, false);
				}
				else
				{
					if (m_pA->isRecordingOn)
					{
						//SA_BOUNCE_RBALL_PLATFORM
						MEmitter::Get()->RB_Platform = true;
					}

					else if (!m_pA->isRecordingOn)
					{
						//SA_BOUNCE_CBALL_PLATFORM
						MEmitter::Get()->CB_Platform = true;
					}
				}
			}

			impulse_j.Normalize();
			impulse_j *= Ball_Spring;

			if (p->mode == NORMAL || p->mode == HAZARD || p->mode == WATER)
			{
				if ((std::abs(m_pA->ConnectTransform()->rotation) >= 0 && std::abs(m_pA->ConnectTransform()->rotation) <= 15))
				{
					m_pA->SetImpulse(-impulse_j, ra, 1);
					m_pB->SetImpulse(impulse_j, rb, 1);

				}

				else
				{
					//DEBUG_PRINT("%f\n", m_pB->ConnectTransform()->rotation);
					m_pA->SetImpulse(-impulse_j, ra, 2);
					m_pB->SetImpulse(impulse_j, rb, 2);
				}
			}
		}
	}
	//m_pA->SetImpulse(-impulse_j, ra);
	//m_pB->SetImpulse(impulse_j, rb);

	//rv = m_pB->vel + Cross(m_pB->angularVel, rb) - m_pA->vel - Cross(m_pA->angularVel, ra);

	//Vector t = rv - (normal * Dot(rv, normal));
	//t.Normalize();

	//float jt = -Dot(rv, t);
	//jt /= invMassSum;
	//jt /= (float)contact_count;

	//if (Equal(jt, 0.0f))
	//	return;

	//Vector tangentImpulse;
	//if (std::abs(jt) < scalar_impusle * static_friction)
	//	tangentImpulse = t * jt;
	//else
	//	tangentImpulse = t * -scalar_impusle * dynamic_friction;

	//m_pA->SetImpulse(-tangentImpulse, ra);
	//m_pB->SetImpulse(tangentImpulse, rb);

}

/*******************************************************************************
Primary Author: <yongmin.cho>

Parameters:
<param> : none

Returns:
<return> : none

Function Description:
Prepare position reallocate for pentrate one rigidbody to ohter rigidbody
*******************************************************************************/
void Manifold::PositionalCorrection(void)
{
	const float allowance = 0.001f; // Penetration allowance
	const float percent = 0.4f; // Penetration percentage to correct
	float max = 0.f;

	if (penetration - allowance > 0.0f)
		max = penetration - allowance;
	else
		return;// max = 0.0f;

	float inv_mass_sum = 0.f;
	if (m_pA->ConnectTransform()->type == eCircle)
		inv_mass_sum = m_pA->inv_mass * 2.f;
	else if (m_pB->ConnectTransform()->type == eCircle)
		inv_mass_sum = m_pB->inv_mass * 2.f;
	Vector correction = normal * percent * (max / inv_mass_sum);
	m_pA->pos -= correction * m_pA->inv_mass;
	m_pB->pos += correction * m_pB->inv_mass;
}

/*******************************************************************************
Primary Author: <yongmin.cho>

Parameters:
<param> : none

Returns:
<return> : none

Function Description:
if there two rigidbody mass is zero, give there velocity zero.
*******************************************************************************/
void Manifold::InfiniteMassCorrection(void)
{
	m_pA->vel.Set(0, 0);
	m_pB->vel.Set(0, 0);
}

/*******************************************************************************
Primary Author: <yongmin.cho>

Parameters:
<param> : none

Returns:
<return> : none

Function Description:
Make two rigidbody Force to zero
*******************************************************************************/
void Manifold::SetForceToZero(void)
{
	m_pA->force.Set(0, 0);
	m_pB->force.Set(0, 0);
}
