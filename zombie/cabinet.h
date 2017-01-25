#ifndef CABINET_H_
#define CABINET_H_

#include "SceneObject.h"
class CWeapon;

class CCabinet:public CSceneObject
{
public:
	CCabinet();
	~CCabinet();
	bool UseCabinet(CWeapon **ppWeapon);
public://virtual function
	virtual void Draw(HINSTANCE hInstance,HDC hdc);
protected:
	bool m_bOpen;
	CWeapon *m_pWeapon;
};


#endif