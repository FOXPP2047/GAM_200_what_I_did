/*******************************************************************************
All content (c)2015, DigiPen (USA) Corporation, all rights reserved.

Primary Author: <yongmin.cho>
Coproducers:
<name> : Sukjun Park

File Description:
Using Action function, action the ball in the menu
*******************************************************************************/
#include "MBall.h"
#include "Collision.h"
#include "Main.h"

const float Menu_Spring = 700.f;
static float dt = 0.0f;

class ObjectManager;

/*******************************************************************************
Primary Author: <yongmin.cho>

Parameters:
<param> : none


Returns:
<return> : none

Function Description:
constructor of MBall
*******************************************************************************/
MBall::MBall(void) : transform(0), currButton(0), targetPos(0), vel(0), menuBallCheck(false), time(20), enter(true)
{
}

/*******************************************************************************
Primary Author: <yongmin.cho>

Parameters:
<param> : none


Returns:
<return> : none

Function Description:
destructor of MBall
*******************************************************************************/
MBall::~MBall(void)
{

}

/*******************************************************************************
Primary Author: <yongmin.cho>

Parameters:
<OM> : ObjectManager(Not Using)


Returns:
<return> : none

Function Description:
Action of MBall in Menu
*******************************************************************************/
void MBall::Action(ObjectManager& OM)
{
	NOT_USING(OM);

	time += FrameRateControl::Get()->GetDeltaTime();

	const float SPEED = 7;

	if (currButton < 0)
		currButton = 0;
	else if (currButton > 3)
		currButton = 3;

	if (transform->pos.y < 100)
	{
		transform->pos.y = 500;
	}

	targetPos = pBt[currButton]->pos;

	transform->pos.x += (targetPos.x - transform->pos.x) * SPEED * FrameRateControl::Get()->GetDeltaTime();

	if (!*confirmquit)
	{
		if ((Input::Get()->GetTriggered(KEY_RETURN) && enter) || (Input::Get()->GetTriggered(KEY_SPACE) && enter))
		{
			time = 0.0f;
			enter = false;
		}

		if (Input::Get()->GetTriggered(KEY_ARROW_RIGHT) && enter)
		{
			currButton++;
			if (vel < -10)
				vel = SPEED * 10;
		}
		else if (Input::Get()->GetTriggered(KEY_ARROW_LEFT) && enter)
		{
			currButton--;
			if (vel < -10)
				vel = SPEED * 20;
		}

		if (time >= 0.6f &&time <= 2.0f)
			switch (currButton)
			{
				case 0:
					StateManager::Get()->SetNextState(LSelect);
					break;
				case 1:
					//WindowsSystem::Get()->SetFullScreen(false);
					StateManager::Get()->SetNextState(Credit);
					break;
				case 2:
					StateManager::Get()->SetNextState(OPTION);
					break;
				case 3:
					*confirmquit = true;
					enter = true;
					time = 100;
					break;
				default:
					break;
			}
	}
		

	vel -= SPEED * 300.f * FrameRateControl::Get()->GetDeltaTime();

	for (int i = 0; i < 4; i++)
	{
		if (Intersection_Circle_Rect(transform->pos, 0, pBt[i]->pos, pBt[i]->scale.x * 0.5f, pBt[i]->scale.y * 0.4f, transform->scale.x * 0.5f, FrameRateControl::Get()->GetDeltaTime()))
		{
			vel = SPEED * 100;
			SoundSystem::Get()->Pause_Sound(SoundSystem::Get()->id_Jump, false);
		}
	}

	if (transform->pos.y < 100)
		vel = SPEED * 100;


	transform->pos.y += vel * FrameRateControl::Get()->GetDeltaTime();
}

bool MBall::GetMenuBall()
{
	return this->menuBallCheck;
}

void MBall::SetMenuBall(bool check)
{
	menuBallCheck = check;
}