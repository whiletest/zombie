#ifndef BED_H_
#define BED_H_

#include "SceneObject.h"

class CBed:public CSceneObject
{
public:
	CBed();
	virtual ~CBed();
public://virtual function
	int OnObjectWhere(POINT &ptPos);
	void Draw(HINSTANCE hInstance,HDC hdc);
	int IsOnObject(POINT ptPos);
	bool IsBulletOn(CBullet *pBullet);
};

#endif