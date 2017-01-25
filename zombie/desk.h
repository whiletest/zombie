#ifndef DESK_H_
#define DESK_H_

#include "SceneObject.h"

class CDesk:public CSceneObject
{
public:
	CDesk();
	~CDesk();
public://virtual function
	void Draw(HINSTANCE hInstance,HDC hdc);
	int IsOnObject(POINT ptPos);
	bool IsBulletOn(CBullet *pBullet);
	//int OnObjectWhere(POINT &ptPos);
};

#endif