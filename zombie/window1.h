#ifndef WINDOW1_H_
#define WINDOW1_H_

#include "SceneObject.h"

class CWindow1:public CSceneObject
{
public:
	enum WINDOW_STATE
	{
		ws_ok,
		ws_crack,
		ws_broken
	};
public:
	CWindow1();
	//////////////////////////////////////////////////////////////////////////
	int getWindowState()const {return m_state;}
	void WindowCrack() {m_state = ws_crack;m_bmpId = IDB_WINDOWCRACK;}
public://virtual function
	void Draw(HINSTANCE hInstance,HDC hdc);
	bool IsBulletOn(CBullet *pBullet);
protected:
	int m_state; //´°×ÓµÄÊôÐÔ
	unsigned int m_bmpId; //Í¼Æ¬id
};

#endif