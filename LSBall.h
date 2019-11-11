#ifndef LSBALL_H
#define LSBALL_H

#include "Component.h"
#include "Transform.h"
#define TOTALBUTTON 32
#define L1NUM 12
#define L2NUM 12
#define L3NUM 8

class LSBall : public Component
{
public:
	LSBall(void);
	~LSBall(void);
	virtual void Action(ObjectManager& OM);
	virtual const char* GetComponentType(void) { return typeid(this).name(); }
	void ConnectTo(Transform* ptransform) { transform = ptransform; }
	Transform* ConnectTransform(void) { return transform; }
	Transform* pBt[TOTALBUTTON];
	Vector saveVector;

	int Level1Num;
	int Level2Num;
	int Level3Num;
	bool Shop;
	//int save_point;
private:
	Transform* transform;
	Vector targetPos;
	int currButton;
	float vel;

	Vector cameraPoint1, cameraPoint2, cameraPoint3;
	bool initiate;
	float m_time;
};

#endif