/*******************************************************************************
All content (c)2015, DigiPen (USA) Corporation, all rights reserved.

Primary Author: <yongmin.cho>
Coproducers:
<name> : Seungmin Lee

File Description:
Action of Button in the menu
*******************************************************************************/
#include "MButton.h"
#include "Main.h"

static bool next;
static float angleSpeed = 0.0f;
class ObjectManager;

/*******************************************************************************
Primary Author: <yongmin.cho>
Coproducers:
<name> : Seungmin Lee

Parameters:
<param> : none


Returns:
<return> : none

Function Description:
constructor of MButton
*******************************************************************************/
MButton::MButton(void) : transform(0), m_minmax_check(true), vel(0), speed(1), currButton(0), time(20), enter(true)
{
	m_quit = false;
	m_pause = false;
	m_pauseSet = false;
}

/*******************************************************************************
Primary Author: <yongmin.cho>
Coproducers:
<name> : Seungmin Lee

Parameters:
<param> : none


Returns:
<return> : none

Function Description:
destructor of MButton
*******************************************************************************/
MButton::~MButton(void)
{

}

/*******************************************************************************
Primary Author: <Seungmin Lee>
Coproducers:
<name> : yongmin.cho

Parameters:
<OM> : Object Manager(Not Using)

Returns:
<return> : none

Function Description:
Action of MButton in Menu
*******************************************************************************/
void MButton::Action(ObjectManager& OM)
{
	NOT_USING(OM);
	time += FrameRateControl::Get()->GetDeltaTime();

	if (Input::Get()->GetTriggered(KEY_ARROW_RIGHT) && enter)
	{
		currButton++;
	}
	else if (Input::Get()->GetTriggered(KEY_ARROW_LEFT) && enter)
	{
		currButton--;
	}

	if (currButton < 0)
		currButton = 0;
	else if (currButton > Totalcount)
		currButton = Totalcount;

	if ((Input::Get()->GetTriggered(KEY_RETURN) && enter) || (Input::Get()->GetTriggered(KEY_SPACE) && enter))
	{
		time = 0.0f;
		angleSpeed = 100;
		enter = false;
	}
	
	if (currButton == count)
	{
		const float Y_MAX = 300;
		const float Y_MAX_SPEED = 5;
		const float ANGLE = -30;
		const float ANGLE_SPEED = 10;
		const float FALL_ACC = -1000;
		const float DT = FrameRateControl::Get()->GetDeltaTime();

		if (time < 0.1f)
		{
			transform->pos.y += Y_MAX_SPEED * (Y_MAX - transform->pos.y) * DT;
			transform->rotation += ANGLE_SPEED * (ANGLE - transform->rotation) * DT;
		}
		else if (time < 0.2f)
		{
			transform->pos.y += Y_MAX_SPEED * (Y_MAX - transform->pos.y) * DT;
			transform->rotation += -ANGLE_SPEED * transform->rotation * DT;
		}
		else if (time < 0.3f)
		{
			transform->rotation += -ANGLE_SPEED * 2 * transform->rotation * DT;
		}
		else if (time < 0.5f)
		{
			fallingvel += FALL_ACC * DT;
			transform->pos.y += fallingvel * DT;
		}
		else if (time < 0.6f)
		{
			fallingvel += FALL_ACC * DT;
			transform->pos.y += fallingvel * DT;
		}
	}

	if (m_minmax_check)
	{
		vel += speed * FrameRateControl::Get()->GetDeltaTime();
		if (transform->pos.y > maxY)
		{
			m_minmax_check = false;
		}
	}

	else if (!m_minmax_check)
	{ 
		vel -= speed * FrameRateControl::Get()->GetDeltaTime();
		if (transform->pos.y < minY)
		{
			m_minmax_check = true;
		}
	}

	//cap vel
	if (vel > 10)
		vel = 10;
	else if (vel < -10)
		vel = -10;

	transform->pos.y += vel * FrameRateControl::Get()->GetDeltaTime();
}

void MButton::SetState(STATE state)
{
	m_state = state;
}

void MButton::SetQuit(bool quit)
{
	m_quit = quit;
}