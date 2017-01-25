#ifndef GROUND_H_
#define GROUND_H_

#include "SceneObject.h"

class CGround:public CSceneObject
{
public:
	CGround();
	~CGround();
public: //virtual function
	void Draw(HINSTANCE hInstance,HDC hdc);
	int IsOnObject(POINT ptPos);
	bool IsBulletOn(CBullet *pBullet);
};

#endif