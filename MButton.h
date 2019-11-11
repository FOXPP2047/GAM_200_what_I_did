/*******************************************************************************
All content (c)2015, DigiPen (USA) Corporation, all rights reserved.

Primary Author: <yongmin.cho>
Coproducers:
<name> : Seungmin Lee

File Description:
Header of MButton
*******************************************************************************/
#ifndef MBUTTON_H
#define MBUTTON_H

#include "Component.h"
#include "Transform.h"
#include "StateManager.h"

class MButton : public Component
{
public:
	MButton(void);
	~MButton(void);
	virtual void Action(ObjectManager& OM);
	virtual const char* GetComponentType(void) { return typeid(this).name(); }
	void ConnectTo(Transform* ptransform) { transform = ptransform; }
	Transform* ConnectTransform(void) { return transform; }
	void SetState(STATE state);
	void SetLevel(unsigned int level);
	void SetQuit(bool quit);
	void SetPause(bool pause);
	void SetPauseS(bool pause);

	float speed;
	float maxY;
	float minY;
	int count;
	float time;
	int Totalcount;
	bool enter;
private:
	Transform* transform;
	STATE m_state;
	int currButton;
	bool m_check;
	unsigned int m_level = 0;
	bool m_quit;
	bool m_pause;
	bool m_pauseSet;
	int m_id;
	bool m_minmax_check;
	float vel;
	
	float fallingvel = 0;
};
#endif