/*******************************************************************************
All content (c)2015, DigiPen (USA) Corporation, all rights reserved.

Primary Author: <yongmin.cho>
Coproducers:
<name> : none

File Description:
Make Option State
*******************************************************************************/
#include "Option.h"
#include "StateManager.h"
#include "Main.h"
#include<string>

/*******************************************************************************
Primary Author: <yongmin.cho>

Parameters:
<param> : none


Returns:
<return> : none

Function Description:
Initialize the Option state.
*******************************************************************************/
void Option::Initialize(void)
{


    //value reset
    currselect = MAX_OPTION_BUTTON - 1;

    OM.camera.z = 100;
    Graphics::Get()->SetWH();
    OM.font.TextureID = OM.TM.LoadTexture("TGA\\Font.tga");

    pWndData = WindowsSystem::Get()->GetWindowsData();
    WindowsSystem::Get()->HideCursor();

    m_fullScreen = WindowsSystem::Get()->GetWindowsData().fullscreen;
    m_mute = SoundSystem::Get()->IsMute();

    Vector screen_left_w = Graphics::Get()->ScreenToWorld(OM.camera, Vector(0, 0));
    Vector screen_right_w = Graphics::Get()->ScreenToWorld(OM.camera, Graphics::Get()->GetWidth());
    Vector screen_right_h = Graphics::Get()->ScreenToWorld(OM.camera, Graphics::Get()->GetHeight());


    float length = screen_right_w.x - screen_left_w.x;
    float heightt = screen_left_w.y - screen_right_h.y;

    //if (!SoundSystem::Get()->IsPlaying(SoundSystem::Get()->id_Menu))
    //    SoundSystem::Get()->Play_Sound(SoundSystem::Get()->id_Menu, true);

    Object curr;
    Transform* transform;
    Sprite* sprite;
    SpriteText* spritetext;
    curr.CreateObject("BackGround");
    sprite = curr.AddComponent<Sprite>();
    if (SaveData::Get()->level < L1NUM && SaveData::Get()->level >= 0)
        sprite->TextureID = OM.TM.LoadTexture("TGA\\forest_background_F.tga");
    else if (SaveData::Get()->level < L1NUM + L2NUM && SaveData::Get()->level >= L1NUM)
        sprite->TextureID = OM.TM.LoadTexture("TGA\\desert_background_F.tga");
    else if (SaveData::Get()->level >= L1NUM + L2NUM)
        sprite->TextureID = OM.TM.LoadTexture("TGA\\Lava_background_menu.tga");
    transform = curr.AddComponent<Transform>();
    transform->ConnectTo(sprite);
    transform->type = ePoly;
    transform->ortho = false;
    transform->order = -0.1f;
    transform->scale = Vector(length, heightt);
    transform->pos = Vector(0, 0);//Graphics::Get()->ScreenToWorld(OM.camera, Vector(Graphics::Get()->GetWidth() * 0.5f, Graphics::Get()->GetHeight() * 0.5f));

    OM.AddObject(curr);

    curr.CreateObject("SelectButton");
    transform = curr.AddComponent<Transform>();
    transform->type = ePoly;
    transform->ortho = true;
    transform->order = 0.9f;
    transform->color = Color(255, 255, 255, 75);
    transform->scale = 100;
    transform->pos = Vector(Graphics::Get()->GetWidth() * 0.5f, Graphics::Get()->GetHeight() * 0.5f);
    sprite = curr.AddComponent<Sprite>();
    transform->ConnectTo(sprite);

    selectbutton = transform;
    OM.AddObject(curr);

    unsigned currbutton = 0;

    curr.CreateObject("Back Button");
    spritetext = curr.AddComponent<SpriteText>();
    spritetext->message = "BACK";
    spritetext->size = Graphics::Get()->GetHeight() * 0.05f;
    spritetext->center = F_LEFT;
    transform = curr.AddComponent<Transform>();
    transform->ConnectTo(spritetext);
    transform->type = eFont;
    transform->ortho = true;
    transform->order = 1;
    transform->pos.x = gap.x;
    transform->pos.y = spritetext->Size().y * (currbutton + 0.5f) + gap.y * (currbutton + 1);

    buttons[currbutton++] = transform;
    OM.AddObject(curr);

    curr.CreateObject("Mute Button");
    spritetext = curr.AddComponent<SpriteText>();
    spritetext->message = "MUTE";
    spritetext->size = Graphics::Get()->GetHeight() * 0.05f;
    spritetext->center = F_LEFT;
    transform = curr.AddComponent<Transform>();
    transform->ConnectTo(spritetext);
    transform->type = eFont;
    transform->ortho = true;
    transform->order = 1;
    transform->pos.x = gap.x;
    transform->pos.y = spritetext->Size().y * (currbutton + 0.5f) + gap.y * (currbutton + 1);

    buttons[currbutton++] = transform;
    OM.AddObject(curr);

    curr.CreateObject("Volume Down Button");
    spritetext = curr.AddComponent<SpriteText>();
    spritetext->message = "Volume Down";
    spritetext->size = Graphics::Get()->GetHeight() * 0.05f;
    spritetext->center = F_LEFT;
    transform = curr.AddComponent<Transform>();
    transform->ConnectTo(spritetext);
    transform->type = eFont;
    transform->ortho = true;
    transform->order = 1;
    transform->pos.x = gap.x;
    transform->pos.y = spritetext->Size().y * (currbutton + 0.5f) + gap.y * (currbutton + 1);

    buttons[currbutton++] = transform;
    OM.AddObject(curr);

    curr.CreateObject("Volume Up Button");
    spritetext = curr.AddComponent<SpriteText>();
    spritetext->message = "Volume Up";
    spritetext->size = Graphics::Get()->GetHeight() * 0.05f;
    spritetext->center = F_LEFT;
    transform = curr.AddComponent<Transform>();
    transform->ConnectTo(spritetext);
    transform->type = eFont;
    transform->ortho = true;
    transform->order = 1;
    transform->pos.x = gap.x;
    transform->pos.y = spritetext->Size().y * (currbutton + 0.5f) + gap.y * (currbutton + 1);

    buttons[currbutton++] = transform;
    OM.AddObject(curr);

    curr.CreateObject("Fullscreen Button");
    spritetext = curr.AddComponent<SpriteText>();
    spritetext->message = "FULLSCREEN";
    spritetext->size = Graphics::Get()->GetHeight() * 0.05f;
    spritetext->center = F_LEFT;
    transform = curr.AddComponent<Transform>();
    transform->ConnectTo(spritetext);
    transform->type = eFont;
    transform->ortho = true;
    transform->order = 1;
    transform->pos.x = gap.x;
    transform->pos.y = spritetext->Size().y * (currbutton + 0.5f) + gap.y * (currbutton + 1);

    buttons[currbutton++] = transform;
    OM.AddObject(curr);

    curr.CreateObject("Reset Button");
    spritetext = curr.AddComponent<SpriteText>();
    spritetext->message = "Reset the Game";
    spritetext->size = Graphics::Get()->GetHeight() * 0.05f;
    spritetext->center = F_LEFT;
    transform = curr.AddComponent<Transform>();
    transform->ConnectTo(spritetext);
    transform->type = eFont;
    transform->ortho = true;
    transform->order = 1;
    transform->pos.x = gap.x;
    transform->pos.y = spritetext->Size().y * (currbutton + 0.5f) + gap.y * (currbutton + 1);

    buttons[currbutton++] = transform;
    OM.AddObject(curr);


		curr.CreateObject("Confirmation Text");
		spritetext = curr.AddComponent<SpriteText>();
		spritetext->message = "Reset Done!";
		spritetext->size = Graphics::Get()->GetHeight() * 0.05f;
		spritetext->center = F_LEFT;
		transform = curr.AddComponent<Transform>();
		transform->ConnectTo(spritetext);
		transform->type = eFont;
		transform->ortho = true;
		transform->order = 1;
		transform->pos.x = Graphics::Get()->GetWidth() / 3;
		transform->pos.y = spritetext->Size().y * (5.5f) + gap.y * 6;
		transform->visible = false;

		pText = transform;
		OM.AddObject(curr);

    curr.CreateObject("Full ON Button");
    spritetext = curr.AddComponent<SpriteText>();
    spritetext->message = "ON";
    spritetext->size = Graphics::Get()->GetHeight() * 0.05f;
    spritetext->center = F_MIDDLE;
    transform = curr.AddComponent<Transform>();
    transform->ConnectTo(spritetext);
    transform->type = eFont;
    transform->ortho = true;
    transform->order = 1;
    transform->pos.x = Graphics::Get()->GetWidth() / 2;
    transform->pos.y = spritetext->Size().y * (4 + 0.5f) + gap.y * (4 + 1);
    transform->visible = WindowsSystem::Get()->GetWindowsData().fullscreen;

    switchOn_Full = transform;
    OM.AddObject(curr);

    curr.CreateObject("Full OFF Button");
    spritetext = curr.AddComponent<SpriteText>();
    spritetext->message = "OFF";
    spritetext->size = Graphics::Get()->GetHeight() * 0.05f;
    spritetext->center = F_MIDDLE;
    transform = curr.AddComponent<Transform>();
    transform->ConnectTo(spritetext);
    transform->type = eFont;
    transform->ortho = true;
    transform->order = 1;
    transform->pos.x = Graphics::Get()->GetWidth()/2;
    transform->pos.y = spritetext->Size().y * (4 + 0.5f) + gap.y * (4 + 1);
    transform->visible = WindowsSystem::Get()->GetWindowsData().fullscreen;

    switchOff_Full = transform;
    OM.AddObject(curr);

    m_volume = static_cast<int>(SoundSystem::Get()->GetMasterVolume() * 100);

    curr.CreateObject("Volume Text");
    spritetext = curr.AddComponent<SpriteText>();
    spritetext->message = std::to_string((m_volume));
    spritetext->size = Graphics::Get()->GetHeight() * 0.05f;
    spritetext->center = F_MIDDLE;
    transform = curr.AddComponent<Transform>();
    transform->ConnectTo(spritetext);
    transform->type = eFont;
    transform->ortho = true;
    transform->order = 1;
    transform->pos.x = Graphics::Get()->GetWidth() / 2;
    transform->pos.y = spritetext->Size().y * (2.5f + 0.5f) + gap.y * (2.5f + 1);


    VolumeText = spritetext;
    OM.AddObject(curr);


    curr.CreateObject("Mute ON Button");
    spritetext = curr.AddComponent<SpriteText>();
    spritetext->message = "ON";
    spritetext->size = Graphics::Get()->GetHeight() * 0.05f;
    spritetext->center = F_MIDDLE;
    transform = curr.AddComponent<Transform>();
    transform->ConnectTo(spritetext);
    transform->type = eFont;
    transform->ortho = true;
    transform->order = 1;
    transform->pos.x = Graphics::Get()->GetWidth() / 2;
    transform->pos.y = spritetext->Size().y * (1 + 0.5f) + gap.y * (1 + 1);
    transform->visible = SoundSystem::Get()->IsMute();

    switchOn_Mute = transform;
    OM.AddObject(curr);

    curr.CreateObject("Mute OFF Button");
    spritetext = curr.AddComponent<SpriteText>();
    spritetext->message = "OFF";
    spritetext->size = Graphics::Get()->GetHeight() * 0.05f;
    spritetext->center = F_MIDDLE;
    transform = curr.AddComponent<Transform>();
    transform->ConnectTo(spritetext);
    transform->type = eFont;
    transform->ortho = true;
    transform->order = 1;
    transform->pos.x = Graphics::Get()->GetWidth() / 2;
    transform->pos.y = spritetext->Size().y * (1 + 0.5f) + gap.y * (1 + 1);
    transform->visible = SoundSystem::Get()->IsMute();

    switchOff_Mute = transform;
    OM.AddObject(curr);
		this->first_check = true;
}

/*******************************************************************************
Primary Author: <yongmin.cho>

Parameters:
<param> : none


Returns:
<return> : none

Function Description:
Update the Option state.
*******************************************************************************/
void Option::Update(void)
{

    Graphics::Get()->DrawStart();
    WindowsSystem::Get()->CursorUpdate();

    const float GAP = 5;

		//static Object curr;
		//static Transform* transform;
    //volume
    //m_volume = static_cast<int>(SoundSystem::Get()->GetMasterVolume() * 100);
    VolumeText->message = std::to_string(m_volume);

    //update buttons
    selectbutton->pos.x = buttons[currselect]->pos.x + buttons[currselect]->ConnectSpriteText()->Size().x * 0.5f;
    selectbutton->pos.y = buttons[currselect]->ConnectSpriteText()->Size().y * (currselect + 0.5f) + gap.y * (currselect + 1);
    selectbutton->scale = buttons[currselect]->ConnectSpriteText()->Size() + GAP;

    for (int i = 0; i < MAX_OPTION_BUTTON; ++i)
        buttons[i]->color = i == currselect ? Color(70, 70, 70) : Color(255, 255, 255);

    //traverse
    if (Input::Get()->GetTriggered(KEY_ARROW_UP))
    {
        if (++currselect == MAX_OPTION_BUTTON) currselect = 0;
    }
    else if (Input::Get()->GetTriggered(KEY_ARROW_DOWN))
    {
        if (--currselect == -1) currselect = MAX_OPTION_BUTTON - 1;
    }
    //selected
    else if (Input::Get()->GetTriggered(KEY_SPACE) || Input::Get()->GetTriggered(KEY_RETURN))
    {
        switch (currselect)
        {
        case 0://back
            if (StateManager::Get()->GetPreviousState() == PAUSE)
            {
                StateManager::Get()->Resume();
            }
            else
            {
                StateManager::Get()->SetNextState(StateManager::Get()->GetPreviousState());
            }
            break;
        case 1://mute
            m_mute = !m_mute;
            SoundSystem::Get()->Mute_All(m_mute);
            break;
        case 2://volume down
            if (m_mute)
            {
                m_mute = !m_mute;
                SoundSystem::Get()->Mute_All(m_mute);
            }
            m_volume -= 10;
            if (m_volume < 0)
                m_volume = 0;
            SoundSystem::Get()->SetMasterVolume(static_cast<float>(m_volume) / 100);
            break;
        case 3://volume up
            if (m_mute)
            {
                m_mute = !m_mute;
                SoundSystem::Get()->Mute_All(m_mute);
            }
            m_volume += 10;
            if (m_volume > 100)
                m_volume = 100;
            SoundSystem::Get()->SetMasterVolume(static_cast<float>(m_volume) / 100);

            break;
        case 4://fullscreen
            m_fullScreen = !m_fullScreen;
            WindowsSystem::Get()->SetFullScreen(m_fullScreen);
            WindowsSystem::Get()->SetRCheck(WindowsSystem::Get()->GetWindowsData().fullscreen);

            break;
        case 5://reset
						pText->visible = true;
		
            SaveData::Get()->level = 0;
            SaveData::Get()->star.clear();
            SaveData::Get()->numstar = 0;
            SaveData::Get()->currskin = 0;
            SaveData::Get()->skin.clear();
            SaveData::Get()->skin.insert(std::map<int, bool>::value_type(0, true));
						SaveData::Get()->m_stage1_clear_F = 0;
						SaveData::Get()->m_stage2_clear_F = 0;
						SaveData::Get()->m_stage3_clear_F = 0;
						LevelDataSave();
            break;
        default:
            break;
        }
    }


    //update switch buttons
    if (WindowsSystem::Get()->GetWindowsData().fullscreen)
    {
        switchOff_Full->visible = false;
        switchOn_Full->visible = true;

    }
    else
    {
        switchOff_Full->visible = true;
        switchOn_Full->visible = false;
    }
    //mute on off
    if (m_mute)
    {
        switchOff_Mute->visible = false;
        switchOn_Mute->visible = true;
    }
    else
    {
        switchOff_Mute->visible = true;
        switchOn_Mute->visible = false;

    }

    if (Input::Get()->GetTriggered(KEY_ESCAPE))
    {
        if (StateManager::Get()->GetPreviousState() == PAUSE)
        {
            StateManager::Get()->Resume();
            WindowsSystem::Get()->SetShowCursor();
        }
        else
        {
            StateManager::Get()->SetNextState(StateManager::Get()->GetPreviousState());
            WindowsSystem::Get()->HideCursor();
        }

    }

		if (pText->visible)
		{
			static float time = 0.f;
			time += FrameRateControl::Get()->GetDeltaTime();

			if (time > 2.f)
			{
				time = 0.f;
				pText->visible = false;
			}
		}
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
Shutdown the Option state.
*******************************************************************************/
void Option::Shutdown(void)
{
    LevelDataSave();
    STATE next = StateManager::Get()->GetNextState();
    if (next != LSelect && next != MENU && next != OPTION && next != Shop)
        SoundSystem::Get()->Stop_Sound(SoundSystem::Get()->id_Menu);


    if (StateManager::Get()->GetNextState() == PAUSE)
        SoundSystem::Get()->Pause_Sound_All(true);

    Graphics::Get()->SetWH();
    OM.TM.UnloadTexture();
    OM.DeleteAllObjects();
}