#ifndef SELECTBKG1_H_
#define SELECTBKG1_H_

#include "SelectBKG.h"

class CSelectBKG1:public CSelectBKG
{
public:
	CSelectBKG1();
	~CSelectBKG1();
public: // virtual func
	void ShowSelectBKG(HINSTANCE hInstance,HDC hdc);
	void IsOnBtn(POINT &ptMouse);
	int IsClickOnBtn();
	void PlaySelectBkgSound();
protected:
	CButtonBKG *m_pOkBtn;
};

#endif