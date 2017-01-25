#ifndef BULLET_SUPPLY_H_
#define BULLET_SUPPLY_H_

#include "SceneObject.h"

class CBulletSupply:public CSceneObject
{
public:
	CBulletSupply();
	~CBulletSupply();
	void SetWeaponKind(int kind) {m_iWeaponKind = kind;}
	void SetBulletNum(int num) {m_iBulletNum = num;}
	int GetWeaponKind()const {return m_iWeaponKind;}
	int GetBulletNum()const {return m_iBulletNum;}
public://virtual function
	void Draw(HINSTANCE hInstance,HDC hdc);
	int IsOnObject(POINT ptPos);
	bool IsBulletOn(CBullet *pBullet);
protected:
	int m_iWeaponKind;
	int m_iBulletNum;
};

#endif