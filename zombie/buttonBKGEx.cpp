#include "stdafx.h"

CButtonBKGEx::CButtonBKGEx(int id /* = 0 */,
						   int iWidth /* = 0 */,
						   int iHeight /* = 0 */, 
						   int iAnotherId /* = 0 */,
						   int iSeletedId
						   ):CButtonBKG(id,iWidth,iHeight,iAnotherId),
						   m_bSelected(false),
						   m_iSelectedId(iSeletedId)
{

}

CButtonBKGEx::~CButtonBKGEx()
{

}

void CButtonBKGEx::IsOnBtn(POINT &ptMouse)
{
	RECT rcBtn = {m_ptOrgPos.x,m_ptOrgPos.y,
		m_ptOrgPos.x + m_iBKGWidth,m_ptOrgPos.y + m_iBKGHeight};
	m_bOnBtn = PtInRect(&rcBtn,ptMouse);

	if (m_bSelected) //已经被选中，不改变当前id
		return;

	if (m_bOnBtn)
		m_iBKGCurId = m_iBKGOnBtnId;
	else
		m_iBKGCurId = m_iBKGNotOnBtnId;
}

