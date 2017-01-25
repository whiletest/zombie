#ifndef GRASS_H_
#define GRASS_H_

#include "SceneObject.h"

class CGrass:public CSceneObject
{
public:
	CGrass();
	~CGrass();
public: //virtual function
	void Draw(HINSTANCE hInstance,HDC hdc);
	int IsOnObject(POINT ptPos);
	bool IsBulletOn(CBullet *pBullet);
};

#endif