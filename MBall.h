/*******************************************************************************
All content (c)2015, DigiPen (USA) Corporation, all rights reserved.

Primary Author: <yongmin.cho>
Coproducers:
<name> : Seungmin Lee
<name> : Sukjun Park

File Description:
Header of MBall
*******************************************************************************/
#ifndef MBALL_H
#define MBALL_H

#include "Component.h"
#include "Transform.h"
//#include "MButton.h"

class MBall : public Component
{
public:
	MBall(void);
	~MBall(void);
	virtual void Action(ObjectManager& OM);
	virtual const char* GetComponentType(void) { return typeid(this).name(); }
	void ConnectTo(Transform* ptransform) { transform = ptransform; }
	Transform* ConnectTransform(void) { return transform; }
	Transform* pBt[4];
	Vector saveVector;
	bool GetMenuBall(void);
	void SetMenuBall(bool check);
	float time;
	bool enter;
	bool* confirmquit;
	bool* enterHL;

private:
	Transform* transform;
	Vector targetPos;
	int currButton;
	bool menuBallCheck;
	float vel;
};

#endif