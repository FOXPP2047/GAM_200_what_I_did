/*******************************************************************************
All content (c)2015, DigiPen (USA) Corporation, all rights reserved.

Primary Author: Yongmin Cho
Coproducers: None

File Description:
Header File of CutScene state
*******************************************************************************/
#ifndef CUT_SCENE_H
#define CUT_SCENE_H

#include"BaseState.h"

class CutScene : public BaseState
{
public:
	virtual void Initialize(void);
	virtual void Update(void);
	virtual void PauseUpdate(void) {};
	virtual void Shutdown(void);

private:
	float time;
};


#endif