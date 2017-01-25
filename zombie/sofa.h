#ifndef SOFA_H_
#define SOFA_H_

#include "SceneObject.h"

class CSofa:public CSceneObject
{
public:
	CSofa();
	~CSofa();
public://virtual function
	void Draw(HINSTANCE hInstance,HDC hdc);
	int IsOnObject(POINT ptPos);
	bool IsBulletOn(CBullet *pBullet);
	int OnObjectWhere(POINT &ptPos);
};

#endif