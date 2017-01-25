#ifndef STICK_H_
#define STICK_H_

#include "SceneObject.h"

class CStick:public CSceneObject
{
public:
	CStick();
	virtual ~CStick();
public://virtual function
	void Draw(HINSTANCE hInstance,HDC hdc);
	int IsOnObject(POINT ptPos);
	bool IsBulletOn(CBullet *pBullet);
};

#endif