#ifndef SOCKET_H_
#define SOCKET_H_

#include "SceneObject.h"

class CTv;

class CSocket:public CSceneObject
{
public:
	CSocket();
	~CSocket();
	void SetRelativeTv(CSceneObject *pSceneObj) {m_pTv = (CTv*)pSceneObj;}
	void UseSocket();
protected:
	void PlaySocketSound();
public://virtual function
	void Draw(HINSTANCE hInstance,HDC hdc);
	int IsOnObject(POINT ptPos);
	bool IsBulletOn(CBullet *pBullet);
protected:
	bool m_bPowerOn;
	CTv *m_pTv;
};

#endif