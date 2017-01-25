#ifndef SAFE_BOX_H_
#define SAFE_BOX_H_

#include "SceneObject.h"

class CBulletSupply;

class CSafeBox:public CSceneObject
{
public:
	CSafeBox();
	~CSafeBox();
	bool GetSate()const {return m_bOpened;}
	void SetRelativeBulletSupply(CSceneObject *pSceneObj);
	void OpenSafeBox();
public://virtual function
	void Draw(HINSTANCE hInstance,HDC hdc);
	int IsOnObject(POINT ptPos);
	bool IsBulletOn(CBullet *pBullet);
protected:
	CBulletSupply *m_pBulletSupply;
	bool m_bOpened;
};

#endif