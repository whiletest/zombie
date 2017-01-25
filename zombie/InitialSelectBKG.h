#ifndef INITIAL_SELECT_BKG
#define INITIAL_SELECT_BKG

#include "SelectBKG.h"

class CButtonBKG;

class CInitialSelectBKG:public CSelectBKG
{
public:
	CInitialSelectBKG();
	~CInitialSelectBKG();
public: // virtual func
	void ShowSelectBKG(HINSTANCE hInstance,HDC hdc);
	void IsOnBtn(POINT &ptMouse);
	int IsClickOnBtn();
protected:
	CButtonBKG *m_pStartBtn;
	CButtonBKG *m_pOperateBtn;
};

#endif