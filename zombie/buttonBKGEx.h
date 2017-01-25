#ifndef _buttonBKGEX_
#define _buttonBKGEX_

#include "buttonBKG.h"

class CButtonBKGEx:public CButtonBKG
{
public:
	CButtonBKGEx(int id = 0,
		int iWidth = 0,
		int iHeight = 0,
		int iAnotherId = 0,
		int iSelectedId = 0);
	virtual ~CButtonBKGEx();
	////////////////////////////////
	void Select() {m_bSelected = true;m_iBKGCurId = m_iSelectedId;}
	void CancelSelect() {m_bSelected = false;m_iBKGCurId = m_iBKGNotOnBtnId;}
	bool getSelectedState()const {return m_bSelected;}
	////////////////////////////////////
public: // virtual
	void IsOnBtn(POINT &ptMouse);
protected:
	bool m_bSelected;
	int m_iSelectedId;
};

#endif