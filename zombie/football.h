#ifndef FOOTBALL_H_
#define FOOTBALL_H_

#include "SceneObject.h"

class CFootball:public CSceneObject
{
public:
	CFootball();
	~CFootball();
public://virtual function
	void Draw(HINSTANCE hInstance,HDC hdc);
	int IsOnObject(POINT ptPos);
	bool IsBulletOn(CBullet *pBullet);
	//int OnObjectWhere(POINT &ptPos);
};

#endif