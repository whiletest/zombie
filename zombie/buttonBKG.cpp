#include "stdafx.h"

CButtonBKG::CButtonBKG(int id /* = 0 */,
					   int iWidth /* = 0 */,
					   int iHeight /* = 0 */,
					   int iAotherId)
					   :CSelectBKG(id,iWidth,iHeight),
					   m_bOnBtn(FALSE),
					   m_iBKGOnBtnId(iAotherId),
					   m_iBKGNotOnBtnId(id)
{

}

CButtonBKG::~CButtonBKG()
{

}

void CButtonBKG::IsOnBtn(POINT &ptMouse)
{
	RECT rcBtn = {m_ptOrgPos.x,m_ptOrgPos.y,
		m_ptOrgPos.x + m_iBKGWidth,m_ptOrgPos.y + m_iBKGHeight};
	m_bOnBtn = PtInRect(&rcBtn,ptMouse);
	if (m_bOnBtn)
		m_iBKGCurId = m_iBKGOnBtnId;
	else
		m_iBKGCurId = m_iBKGNotOnBtnId;
}


int CButtonBKG::IsClickOnBtn()
{
	if (m_bOnBtn)
		return m_iBKGCurId;
	return FALSE;
}

void CButtonBKG::ShowSelectBKG(HINSTANCE hInstance,HDC hdc)
{
//NULL
}

void CButtonBKG::SetBtnBkgID(int ID)
{
	m_iBKGCurId = m_iBKGOnBtnId = m_iBKGNotOnBtnId = ID;
}