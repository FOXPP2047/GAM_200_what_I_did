/*******************************************************************************
All content (c)2015, DigiPen (USA) Corporation, all rights reserved.

Primary Author: <yongmin.cho>
Coproducers:
<name> : none

File Description:
Header of Option.cpp
*******************************************************************************/
#ifndef OPTION_H
#define OPTION_H

#include "BaseState.h"

const unsigned MAX_OPTION_BUTTON = 6;

class Option : public BaseState
{
public:

	virtual void Initialize(void);
	virtual void Update(void);
    virtual void PauseUpdate(void) {};
    virtual void Shutdown(void);
	void SetFullScreen(bool statefullscreen) { m_fullScreen = statefullscreen; }
	bool m_fullScreen;
    bool m_mute;
private:

    int currselect = 0;
    Transform* buttons[MAX_OPTION_BUTTON]; //remember, reversed order
    Transform* selectbutton = nullptr;
    Transform* switchOn_Full = nullptr;
    Transform* switchOff_Full = nullptr;

    Transform* switchOn_Mute = nullptr;
    Transform* switchOff_Mute = nullptr;
    SpriteText* VolumeText = nullptr;

		Transform *pText = 0;
    int m_volume;
    Vector gap = 20;
		bool first_check;
};
#endif