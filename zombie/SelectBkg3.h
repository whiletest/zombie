#ifndef SELECTBKG3_H_
#define SELECTBKG3_H_

#include "SelectBKG.h"

class CSelectBKG3:public CSelectBKG
{
public:
	CSelectBKG3();
	~CSelectBKG3();
public: // virtual func
	void ShowSelectBKG(HINSTANCE hInstance,HDC hdc);
	void IsOnBtn(POINT &ptMouse);
	int IsClickOnBtn();
protected:
	CButtonBKG *m_pOkBtn;
};

#endif