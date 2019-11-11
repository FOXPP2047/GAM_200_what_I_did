#include "MBall.h"
#include "Collision.h"
#include "Main.h"

const float SPEED = 7;

class ObjectManager;

LSBall::LSBall(void) : cameraPoint1(0), cameraPoint2(0), cameraPoint3(0), initiate(false), transform(0), targetPos(0), vel(0), Level1Num(L1NUM), Level2Num(L2NUM), Level3Num(L3NUM), m_time(0.f), Shop(true)
{
	
}

LSBall::~LSBall(void)
{

}

void LSBall::Action(ObjectManager& OM)
{

	if (Shop)
	{
		if (!initiate)
		{
			cameraPoint1 = Graphics::Get()->ScreenToWorld(OM.camera, Vector(Graphics::Get()->GetWidth() * 0.5f, Graphics::Get()->GetHeight() * 0.5f));

			cameraPoint2 = Graphics::Get()->ScreenToWorld(OM.camera, Vector(Graphics::Get()->GetWidth() * 1.5f, Graphics::Get()->GetHeight() * 0.5f));

			cameraPoint3 = Graphics::Get()->ScreenToWorld(OM.camera, Vector(Graphics::Get()->GetWidth() * 2.5f, Graphics::Get()->GetHeight() * 0.5f));
			if (StateManager::Get()->GetPreviousState() == STATE::MENU)
			{
				if (SaveData::Get()->level < Level1Num && SaveData::Get()->level >= 0)
					OM.camera.pos = Graphics::Get()->ScreenToWorld(OM.camera, Vector(Graphics::Get()->GetWidth() * 0.5f, Graphics::Get()->GetHeight() * 0.5f));
				else if (SaveData::Get()->level >= Level1Num && SaveData::Get()->level < Level1Num + Level2Num)
					OM.camera.pos = Graphics::Get()->ScreenToWorld(OM.camera, Vector(Graphics::Get()->GetWidth() * 1.5f, Graphics::Get()->GetHeight() * 0.5f));
				else if (SaveData::Get()->level >= Level1Num + Level2Num)
					OM.camera.pos = Graphics::Get()->ScreenToWorld(OM.camera, Vector(Graphics::Get()->GetWidth() * 2.5f, Graphics::Get()->GetHeight() * 0.5f));
			}
			else
			{
				if (SaveData::Get()->current_level < Level1Num && SaveData::Get()->current_level >= 0)
					OM.camera.pos = Graphics::Get()->ScreenToWorld(OM.camera, Vector(Graphics::Get()->GetWidth() * 0.5f, Graphics::Get()->GetHeight() * 0.5f));

				else if (SaveData::Get()->current_level >= Level1Num && SaveData::Get()->current_level < Level1Num + Level2Num)
					OM.camera.pos = Graphics::Get()->ScreenToWorld(OM.camera, Vector(Graphics::Get()->GetWidth() * 1.5f, Graphics::Get()->GetHeight() * 0.5f));
				else if (SaveData::Get()->current_level >= Level1Num + Level2Num)
					OM.camera.pos = Graphics::Get()->ScreenToWorld(OM.camera, Vector(Graphics::Get()->GetWidth() * 2.5f, Graphics::Get()->GetHeight() * 0.5f));
			}

			if (StateManager::Get()->GetPreviousState() == STATE::MENU)
				currButton = SaveData::Get()->level;
			else if (StateManager::Get()->GetPreviousState() == STATE::CUTSCENE)
				currButton = SaveData::Get()->level;
			else currButton = SaveData::Get()->current_level;

			if (currButton >= TOTALBUTTON)
				currButton = 0;

			transform->pos.x = pBt[currButton]->pos.x;

			initiate = true;
		}

		//DEBUG_PRINT("%i\n", StateManager::Get()->GetCurrentLevel());

		if (transform->pos.y < pBt[0]->pos.y - pBt[0]->scale.y)
		{
			transform->pos.y = Graphics::Get()->ScreenToWorld(OM.camera, Vector(Graphics::Get()->GetWidth() * 0.05f, Graphics::Get()->GetHeight() * 0.6f)).y;
		}

		if (StateManager::Get()->GetPreviousState() == STATE::CUTSCENE)
		{
			if (SaveData::Get()->m_stage1_clear_F == 1)
			{
				currButton++;
				++SaveData::Get()->m_stage1_clear_F;
				LevelDataSave();
			}
			else if (SaveData::Get()->m_stage2_clear_F == 1)
			{
				currButton++;
				++SaveData::Get()->m_stage2_clear_F;
				LevelDataSave();
			}
			else if (SaveData::Get()->m_stage3_clear_F == 1)
			{
				currButton++;
				++SaveData::Get()->m_stage3_clear_F;
				LevelDataSave();
			}
		}
		//if (SaveData::Get()->m_stage1_clear_F == 1)
		//{
		//	currButton++;
		//	++SaveData::Get()->m_stage1_clear_F;
		//	LevelDataSave();
		//}

		//else if (SaveData::Get()->m_stage2_clear_F == 1)
		//{
		//	currButton++;
		//	++SaveData::Get()->m_stage2_clear_F;
		//	LevelDataSave();
		//	m_time = 0.f;
		//}

		//else if (SaveData::Get()->m_stage3_clear_F == 1)
		//{
		//	currButton++;
		//	++SaveData::Get()->m_stage3_clear_F;
		//	LevelDataSave();
		//}

		//if (!m_time)
		//{
			if (Input::Get()->GetTriggered(KEY_ARROW_RIGHT))
			{
				currButton++;
			}

			else if (Input::Get()->GetTriggered(KEY_ARROW_LEFT))
			{
				currButton--;
			}
		//}

		if (currButton < 0)
		{
			currButton = 0;
		}
		else if (currButton > SaveData::Get()->level)
		{
			currButton = SaveData::Get()->level;
		}

		if (currButton < Level1Num && currButton >= 0)
		{
			OM.camera.pos.x += (cameraPoint1.x - OM.camera.pos.x) * SPEED * FrameRateControl::Get()->GetDeltaTime();
		}
		else if (currButton >= Level1Num && currButton < Level1Num + Level2Num)
		{
			OM.camera.pos.x += (cameraPoint2.x - OM.camera.pos.x) * SPEED * FrameRateControl::Get()->GetDeltaTime();
		}
		else if (currButton >= Level1Num + Level2Num)
		{
			OM.camera.pos.x += (cameraPoint3.x - OM.camera.pos.x) * SPEED * FrameRateControl::Get()->GetDeltaTime();
		}
		//if (SaveData::Get()->level > 6)
		//		SaveData::Get()->level = 6;
		//if (!static_cast<int>(StateManager::Get()->SetEpisode()))
		//{
		//	if (currButton > 6)
		//		
		//}
		if (currButton <= SaveData::Get()->level)
			targetPos = pBt[currButton]->pos;
		//if (currButton == 7)
		//	transform->pos.x += (targetPos.x - transform->pos.x) * FrameRateControl::Get()->GetDeltaTime();
		//else
		transform->pos.x += (targetPos.x - transform->pos.x) * SPEED * FrameRateControl::Get()->GetDeltaTime();

		if (Input::Get()->GetTriggered(KEY_RETURN) || (!Input::Get()->GetPressed(KEY_SHIFT) && Input::Get()->GetTriggered(KEY_SPACE)))
		{
			StateManager::Get()->SetNextState(Level);
			StateManager::Get()->SetLevel() = currButton + static_cast<int>(StateManager::Get()->SetEpisode()) * 10;
			SaveData::Get()->current_state = Level;
			SaveData::Get()->current_level = currButton;
		}

		vel -= SPEED * 30.f * FrameRateControl::Get()->GetDeltaTime();

		for (int i = 0; i < SaveData::Get()->level + 1; i++)
		{
			if (SaveData::Get()->level >= TOTALBUTTON)
				break;

			if (Intersection_Circle_Rect(transform->pos, 0, pBt[i]->pos, pBt[i]->scale.x * 0.5f, pBt[i]->scale.y * 0.38f, transform->scale.x * 0.5f, FrameRateControl::Get()->GetDeltaTime()))
			{
				vel = SPEED * 10;
				SoundSystem::Get()->Pause_Sound(SoundSystem::Get()->id_Jump, false);
			}
		}
		//if (SaveData::Get()->level + 1 > L1NUM)
		//{
		if (Input::Get()->GetPressed(KEY_SHIFT) && Input::Get()->GetTriggered(KEY_SPACE))
		{
			//currButton = L1NUM;
			currButton = SaveData::Get()->level;
			transform->pos.x = pBt[currButton]->pos.x;
		}

		transform->pos.y += vel * FrameRateControl::Get()->GetDeltaTime();
	}

	//}
	//if (transform->pos.y < 100)
	//	vel = SPEED * 100;
}