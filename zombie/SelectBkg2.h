#ifndef SELECTBKG2_H_
#define SELECTBKG2_H_

#include "SelectBKG.h"

class CSelectBKG2:public CSelectBKG
{
public:
	CSelectBKG2();
	~CSelectBKG2();
	void PlayClickSound();
public: // virtual func
	void ShowSelectBKG(HINSTANCE hInstance,HDC hdc);
	void IsOnBtn(POINT &ptMouse);
	int IsClickOnBtn();
protected:
	CButtonBKG *m_pSafeBoxOkBtn;
	CButtonBKG *m_pNumBtn[4];
	int m_iNum[4];
};

#endif