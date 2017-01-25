#ifndef TVSET_H_
#define TVSET_H_

#include "SceneObject.h"

class CTv:public CSceneObject
{
public:
	CTv();
	~CTv();
	void PowerOn() {m_bOnPower = true;}
	void PowerOff() {m_bOnPower = false;}
	void PutInDisk() {m_bDisk = true;}
	bool GetPowerState()const {return m_bOnPower;}
	bool GetDiskState()const {return m_bDisk;}
public://virtual function
	void Draw(HINSTANCE hInstance,HDC hdc);
	int IsOnObject(POINT ptPos);
	bool IsBulletOn(CBullet *pBullet);
protected:
	bool m_bOnPower; //是否有电
	bool m_bDisk; //是否有影碟
};

#endif