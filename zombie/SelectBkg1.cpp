#include "stdafx.h"

extern DWORD WINAPI SelectBkgSoundThread(LPVOID lpParameter);

CSelectBKG1::CSelectBKG1():CSelectBKG(IDB_SELECTBKG1,1017,498)
{
	m_pOkBtn = new CButtonBKG(IDB_OKSMALL,200,56,IDB_OK);

	POINT ptOrg = {400,380};
	m_pOkBtn->SetOrgPoint(ptOrg);

	m_ptOrgPos.x = m_ptOrgPos.y = 0;
}

CSelectBKG1::~CSelectBKG1()
{
	if (m_pOkBtn)
		delete m_pOkBtn;
}

void CSelectBKG1::ShowSelectBKG(HINSTANCE hInstance,HDC hdc)
{
	LoadBKG(hInstance,hdc);

	m_pOkBtn->LoadBKG(hInstance,hdc);
	m_pOkBtn->BltBKG(m_hMemDc,FLAGE_TRANSBLT);

	BltBKG(hdc,FLAG_STRECHBLT);
}

void CSelectBKG1::IsOnBtn(POINT &ptMouse)
{
	m_pOkBtn->IsOnBtn(ptMouse);
}

int CSelectBKG1::IsClickOnBtn()
{
	if (m_pOkBtn->IsClickOnBtn())
		return m_pOkBtn->GetBKGId();
	return FALSE;
}

void CSelectBKG1::PlaySelectBkgSound()
{
	HANDLE hSoundThread = 
		CreateThread(NULL,0,
		SelectBkgSoundThread,
		NULL,0,NULL);
	CloseHandle(hSoundThread);
}