#ifndef BUS_SET_H_
#define BUS_SET_H_

#include "SceneObject.h"

class CBusSet:public CSceneObject
{
public:
	CBusSet();
	~CBusSet();
public://virtual function
	int OnObjectWhere(POINT &ptPos);
	void Draw(HINSTANCE hInstance,HDC hdc);
	int IsOnObject(POINT ptPos);
	bool IsBulletOn(CBullet *pBullet);
};

#endif