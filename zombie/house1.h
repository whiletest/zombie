#ifndef HOUSE1_H_
#define HOUSE1_H_

#include "SceneObject.h"

class CHouse1:public CSceneObject
{
public:
	CHouse1();
	~CHouse1();
	void SetHouseIndex(int index) {m_iIndex = index;}
public://virtual function
	void Draw(HINSTANCE hInstance,HDC hdc);
	int IsOnObject(POINT ptPos);
	bool IsBulletOn(CBullet *pBullet);
protected:
	int m_iIndex; //·¿×ÓË÷Òý
};

#endif