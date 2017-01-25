#ifndef KEY_H_
#define KEY_H_

#include "SceneObject.h"

class CBullet;

class CKey:public CSceneObject
{
public:
	CKey();
	~CKey();
	//////////////inline function
	void SetKey(int iKey) {m_iKeyIndex = iKey;}
	int GetKeyIndex()const {return m_iKeyIndex;}
	void SetAbleToShootOnFlag(bool flag) {m_bAbleToShootOn = flag;}
	/////////////////////////////
public: //virtual function
	void Draw(HINSTANCE hInstance,HDC hdc);
	int IsOnObject(POINT ptPos);
	bool IsBulletOn(CBullet *pBullet);
protected:
	int m_iKeyIndex;
	bool m_bAbleToShootOn;
};

#endif