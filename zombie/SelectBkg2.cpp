#include "stdafx.h"

extern DWORD WINAPI ClickSoundThread(LPVOID lpParameter);

CSelectBKG2::CSelectBKG2():CSelectBKG(IDB_SAFEBOXBKG,1017,498)
{
	for (int i = 0;i != 4;++i)
		m_iNum[i] = IDB_NUM0;

	POINT ptOrg[4] = {332,109,423,112,514,112,604,112};

	for (int i = 0;i != 4;++i)
	{
		m_pNumBtn[i] = new CButtonBKG(m_iNum[i],55,46,m_iNum[i]);
		m_pNumBtn[i]->SetOrgPoint(ptOrg[i]);
	}

	ptOrg[0].x = 400;
	ptOrg[0].y = 430;
	m_pSafeBoxOkBtn = new CButtonBKG(IDB_SAFEBOXOKSMALL,200,56,IDB_SAFEBOXOK);
	m_pSafeBoxOkBtn->SetOrgPoint(ptOrg[0]);

	m_ptOrgPos.x = m_ptOrgPos.y = 0;
}

CSelectBKG2::~CSelectBKG2()
{
	for (int i = 0;i != 4;++i)
	{
		if (m_pNumBtn[i])
		{
			delete m_pNumBtn[i];
			m_pNumBtn[i] = NULL;
		}
	}

	if (m_pSafeBoxOkBtn)
		delete m_pSafeBoxOkBtn;
	m_pSafeBoxOkBtn = NULL;
}

void CSelectBKG2::ShowSelectBKG(HINSTANCE hInstance,HDC hdc)
{
	LoadBKG(hInstance,hdc);

	for (int i = 0;i != 4;++i)
	{
		m_pNumBtn[i]->LoadBKG(hInstance,hdc);
		m_pNumBtn[i]->BltBKG(m_hMemDc,FLAG_BITBLT);
	}

	m_pSafeBoxOkBtn->LoadBKG(hInstance,hdc);
	m_pSafeBoxOkBtn->BltBKG(m_hMemDc,FLAGE_TRANSBLT);

	BltBKG(hdc,FLAG_STRECHBLT);
}

void CSelectBKG2::IsOnBtn(POINT &ptMouse)
{
	for (int i = 0;i != 4;++i)
		m_pNumBtn[i]->IsOnBtn(ptMouse);

	m_pSafeBoxOkBtn->IsOnBtn(ptMouse);
}

int CSelectBKG2::IsClickOnBtn()
{
	for (int i = 0;i != 4;++i)
	{
		if ( m_pNumBtn[i]->IsClickOnBtn() )
		{
			PlayClickSound();

			++m_iNum[i];
			if (m_iNum[i] == IDB_NUM9 + 1)
				m_iNum[i] = IDB_NUM0;
			m_pNumBtn[i]->SetBtnBkgID(m_iNum[i]);

			if (   m_iNum[0] == IDB_NUM1
				&& m_iNum[1] == IDB_NUM2
				&& m_iNum[2] == IDB_NUM1
				&& m_iNum[3] == IDB_NUM8 )
			{
				return PASSWORD_RIGHT;
			}

			Sleep(200);

			break;
		}
	}

	if ( m_pSafeBoxOkBtn->IsClickOnBtn() )
		return m_pSafeBoxOkBtn->GetBKGId();

	return FALSE;
}

void CSelectBKG2::PlayClickSound()
{
	HANDLE hSoundThread = 
		CreateThread(NULL,0,
		ClickSoundThread,
		NULL,0,NULL);
	CloseHandle(hSoundThread);
}