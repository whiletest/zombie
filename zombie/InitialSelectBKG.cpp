#include "stdafx.h"

CInitialSelectBKG::CInitialSelectBKG():CSelectBKG(IDB_INITIALIZE,1017,498)
{
	m_pStartBtn = new CButtonBKG(IDB_STARTSMALL,200,56,IDB_START);
	m_pOperateBtn = new CButtonBKG(IDB_OPERATESMALL,200,56,IDB_OPERATE);

	POINT ptOrg = {400,380};
	m_pStartBtn->SetOrgPoint(ptOrg);

	ptOrg.x = 100;
	ptOrg.y = 380;
	m_pOperateBtn->SetOrgPoint(ptOrg);

	m_ptOrgPos.x = m_ptOrgPos.y = 0;
}

CInitialSelectBKG::~CInitialSelectBKG()
{
	if (m_pStartBtn)
		delete m_pStartBtn;
	if (m_pOperateBtn)
		delete m_pOperateBtn;
}

void CInitialSelectBKG::ShowSelectBKG(HINSTANCE hInstance,HDC hdc)
{
	LoadBKG(hInstance,hdc);

	m_pStartBtn->LoadBKG(hInstance,hdc);
	m_pStartBtn->BltBKG(m_hMemDc,FLAGE_TRANSBLT);

	m_pOperateBtn->LoadBKG(hInstance,hdc);
	m_pOperateBtn->BltBKG(m_hMemDc,FLAGE_TRANSBLT);

	BltBKG(hdc,FLAG_STRECHBLT);
}

void CInitialSelectBKG::IsOnBtn(POINT &ptMouse)
{
	 m_pStartBtn->IsOnBtn(ptMouse);
	 m_pOperateBtn->IsOnBtn(ptMouse);
}

int CInitialSelectBKG::IsClickOnBtn()
{
	if (m_pStartBtn->IsClickOnBtn())
		return m_pStartBtn->GetBKGId();
	if (m_pOperateBtn->IsClickOnBtn())
		return m_pOperateBtn->GetBKGId();
	return FALSE;
}