#include "stdafx.h"

CSelectBKG3::CSelectBKG3():CSelectBKG(IDB_SELECTBKG3,1017,498)
{
	m_pOkBtn = new CButtonBKG(IDB_OKSMALL,200,56,IDB_OK);

	POINT ptOrg = {400,380};
	m_pOkBtn->SetOrgPoint(ptOrg);

	m_ptOrgPos.x = m_ptOrgPos.y = 0;
}

CSelectBKG3::~CSelectBKG3()
{
	if (m_pOkBtn)
		delete m_pOkBtn;
}

void CSelectBKG3::ShowSelectBKG(HINSTANCE hInstance,HDC hdc)
{
	LoadBKG(hInstance,hdc);

	m_pOkBtn->LoadBKG(hInstance,hdc);
	m_pOkBtn->BltBKG(m_hMemDc,false);

	BltBKG(hdc,true);
}

void CSelectBKG3::IsOnBtn(POINT &ptMouse)
{
	m_pOkBtn->IsOnBtn(ptMouse);
}

int CSelectBKG3::IsClickOnBtn()
{
	if (m_pOkBtn->IsClickOnBtn())
		return m_pOkBtn->GetBKGId();
	return FALSE;
}