#ifndef WASH_POT_H_
#define WASH_POT_H_

#include "SceneObject.h"

class CWashPot:public CSceneObject
{
public:
	CWashPot();
	~CWashPot();
public://virtual function
	void Draw(HINSTANCE hInstance,HDC hdc);
	int IsOnObject(POINT ptPos);
	bool IsBulletOn(CBullet *pBullet);
};

#endif