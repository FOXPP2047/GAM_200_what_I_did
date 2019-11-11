/*******************************************************************************
All content (c)2016, DigiPen (USA) Corporation, all rights reserved.

Primary Author: Yongmin Cho
Coproducers:
none

File Description:
CutScene state
*******************************************************************************/
#include "CutScene.h"
#include "StateManager.h"
#include "Main.h"

/*******************************************************************************
Primary Author: <yongmin.cho>

Parameters:
<param> : none

Returns:
<return> : none

Function Description:
Initialize of CutScene
*******************************************************************************/
void CutScene::Initialize(void)
{
	OM.camera.z = 200;
	Graphics::Get()->SetWH();

	WindowsSystem::Get()->HideCursor();
	const int CutScene_F2D = OM.TM.LoadTexture("TGA\\CutScene_F2D.tga");
	const int CutScene_D2L = OM.TM.LoadTexture("TGA\\CutScene_D2L.tga");

	pWndData = WindowsSystem::Get()->GetWindowsData();

	Object curr;
	Transform *transform;
	Sprite *sprite;

	this->time = 0.0f;

	Vector screen_left_w = Graphics::Get()->ScreenToWorld(OM.camera, Vector(0, 0));
	Vector screen_right_w = Graphics::Get()->ScreenToWorld(OM.camera, Graphics::Get()->GetWidth());
	Vector screen_left_h = Graphics::Get()->ScreenToWorld(OM.camera, Graphics::Get()->GetHeight());

	const float length = screen_right_w.x - screen_left_w.x;
	const float height = screen_left_w.y - screen_left_h.y;

	if (SaveData::Get()->m_stage1_clear_F == 1)
	{
		curr.CreateObject("CUTSCENE_F2D");
		sprite = curr.AddComponent<Sprite>();
		sprite->TextureID = CutScene_F2D;
		transform = curr.AddComponent<Transform>();
		transform->ortho = false;
		transform->ConnectTo(sprite);
		transform->type = ePoly;
		transform->scale = Vector(2 * length, height);
		transform->pos = Vector(length * 0.5f, 0);

		OM.AddObject(curr);
	}

	else if (SaveData::Get()->m_stage2_clear_F == 1)
	{
		curr.CreateObject("CUTSCENE_D2L");
		sprite = curr.AddComponent<Sprite>();
		sprite->TextureID = CutScene_D2L;
		transform = curr.AddComponent<Transform>();
		transform->ortho = false;
		transform->ConnectTo(sprite);
		transform->type = ePoly;
		transform->scale = Vector(2 * length, height);
		transform->pos = Vector(length * 0.5f, 0);

		OM.AddObject(curr);
	}

	curr.CreateObject("Ball");
	transform = curr.AddComponent<Transform>();
	transform->type = eCircle;
	transform->ortho = false;
	transform->order = 1.0f;
	transform->scale = 10;
	transform->pos = Vector(-length/5, -height * 0.2f);
	ParticleEmitter* particle = curr.AddComponent<ParticleEmitter>();
	particle->ConnectTo(transform);
	particle->emit_rate = 0.016f * 0.5f;
	particle->emit_amount = 1;
	particle->emit_size_X = transform->scale.x * 0.7f;
	particle->emit_size_Y = transform->scale.y * 0.7f;
	if ((int)GameData::Get()->skinlist.size() > SaveData::Get()->currskin)
	{
		auto pData = GameData::Get()->skinlist.at(SaveData::Get()->currskin);

		particle->emit_tga = pData.TGA_particle;
		if (particle->emit_tga == "") particle->emit_tga = "TGA\\highlight.tga";
		particle->emit_speed = pData.emit_speed;
		particle->emit_size_X = transform->scale.x * 0.7f;
		particle->emit_size_Y = transform->scale.y * 0.7f;
		particle->emit_size_unified = pData.emit_size_unified;

		if (pData.TGA_texture != "")
		{
			Sprite* sprite = curr.AddComponent<Sprite>();
			sprite->path = pData.TGA_texture;
			sprite->TextureID = OM.TM.LoadTGAstack(sprite->path).cID;
			transform->ConnectTo(sprite);
		}
	}
	else
		particle->emit_tga = "TGA\\highlight.tga";
	particle->emit_lifetime = 0.016f * 30;
	particle->emit_speed = 0;
	particle->emit_wind = -50;
	particle->init = particle_init_firework;
	particle->update = particle_update_shop;
	particle->emit_tga = "TGA\\highlight.tga";
	particle->maxParticle_amount = 100;
	transform->ConnectTo(particle);
	ShopBall* shopball = curr.AddComponent<ShopBall>();
	shopball->ConnectTo(transform);
	shopball->GROUND_BORDER = transform->pos.y + 10;
	shopball->unlocked = true;

	OM.AddObject(curr);
}

/*******************************************************************************
Primary Author: <yongmin.cho>

Parameters:
<param> : none

Returns:
<return> : none

Function Description:
Update of CutScene
*******************************************************************************/
void CutScene::Update(void)
{
	this->time += FrameRateControl::Get()->GetDeltaTime();
	Graphics::Get()->DrawStart();

	if (Input::Get()->GetTriggered(KEY_RETURN))
		StateManager::Get()->SetNextState(LSelect);
	if (this->time > 5.f)
		StateManager::Get()->SetNextState(LSelect);
	Object* search1 = OM.SearchObject("CUTSCENE_F2D");
	Object* search2 = OM.SearchObject("CUTSCENE_D2L");
	if (search1)
		search1->SearchComponent<Transform>()->pos.x += -50 * FrameRateControl::Get()->GetDeltaTime();
	else if (search2)
		search2->SearchComponent<Transform>()->pos.x += -50 * FrameRateControl::Get()->GetDeltaTime();
	OM.UpdateObjects();

	Graphics::Get()->Draw(OM);
	Graphics::Get()->DrawEnd(pWndData);
}

/*******************************************************************************
Primary Author: <yongmin.cho>

Parameters:
<param> : none

Returns:
<return> : none

Function Description:
Shutdown of CutScene
*******************************************************************************/
void CutScene::Shutdown(void)
{
	DEBUG_PRINT("CUT_SCENE SHUTDOWN\n");
	
	OM.TM.UnloadTexture();
	OM.DeleteAllObjects();

}