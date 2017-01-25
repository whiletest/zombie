#ifndef DISK_H_
#define DISK_H_

#include "SceneObject.h"

class CDisk:public CSceneObject
{
public:
	CDisk();
	virtual ~CDisk();
public://virtual function
	void Draw(HINSTANCE hInstance,HDC hdc);
	int IsOnObject(POINT ptPos);
	bool IsBulletOn(CBullet *pBullet);
};

#endif