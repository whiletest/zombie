#ifndef ROAD_SIGN_H_
#define ROAD_SIGN_H_

#include "SceneObject.h"

class CRoadSign:public CSceneObject
{
public:
	CRoadSign();
	~CRoadSign();
public://virtual function
	void Draw(HINSTANCE hInstance,HDC hdc);
	int IsOnObject(POINT ptPos);
	bool IsBulletOn(CBullet *pBullet);
};

#endif