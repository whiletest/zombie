#pragma once

#include "SelectBKG.h"

class CMP5;
class CPlayer;

class CSelectBKG5:public CSelectBKG
{
public:
	CSelectBKG5(CPlayer *pPlayer = 0);
	virtual ~CSelectBKG5();
public: // virtual func
	void ShowSelectBKG(HINSTANCE hInstance,HDC hdc);
	void IsOnBtn(POINT &ptMouse);
	int IsClickOnBtn();
protected:
	CButtonBKG *m_pOkBtn;
	CButtonBKG *m_pGetBtn;
	CPlayer *m_pPlayer;
};