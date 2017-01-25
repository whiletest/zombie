#ifndef BUTTON_BKG_H_
#define BUTTON_BKG_H_

#include "SelectBKG.h"

class CButtonBKG:public CSelectBKG
{
public:
	CButtonBKG(int id = 0,
		int iWidth = 0,
		int iHeight = 0,
		int iAnotherId = 0);
	virtual ~CButtonBKG();
	void SetBtnBkgID(int ID);
	bool getIsOnBtn()const {return (bool)m_bOnBtn;}
public://virtual func
	void ShowSelectBKG(HINSTANCE hInstance,HDC hdc);
	void IsOnBtn(POINT &ptMouse);
	int IsClickOnBtn();
protected:
	BOOL m_bOnBtn;
	int m_iBKGOnBtnId;
	int m_iBKGNotOnBtnId;
};

#endif