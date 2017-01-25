#ifndef HOME_GATE_H_
#define HOME_GATE_H_

#include "SceneObject.h"

class CHomeGate:public CSceneObject
{
public:
	CHomeGate();
	~CHomeGate();
public://virtual function
	void Draw(HINSTANCE hInstance,HDC hdc);
	int IsOnObject(POINT ptPos);
	bool IsBulletOn(CBullet *pBullet);
};

#endif