#include "stdafx.h"

/*extern DWORD WINAPI SelectBkgSoundThread(LPVOID lpParameter);*/

CSelectBKG5::CSelectBKG5(CPlayer *pPlayer):
                                    CSelectBKG(IDB_MP5BKG,1017,498),
                                    m_pPlayer(pPlayer)
{
	m_pOkBtn = new CButtonBKG(IDB_OKSMALL,200,56,IDB_OK);
	POINT ptOrg = {400,380};
	m_pOkBtn->SetOrgPoint(ptOrg);

	m_pGetBtn = new CButtonBKG(IDB_GETSMALL,200,56,IDB_GETBIG);
	ptOrg.x += 300;
	m_pGetBtn->SetOrgPoint(ptOrg);

	m_ptOrgPos.x = m_ptOrgPos.y = 0;
}

CSelectBKG5::~CSelectBKG5()
{
	if (m_pOkBtn)
		delete m_pOkBtn;
	if (m_pGetBtn)
		delete m_pGetBtn;
}

void CSelectBKG5::ShowSelectBKG(HINSTANCE hInstance,HDC hdc)
{
	LoadBKG(hInstance,hdc);

	m_pOkBtn->LoadBKG(hInstance,hdc);
	m_pOkBtn->BltBKG(m_hMemDc,FLAGE_TRANSBLT);

	m_pGetBtn->LoadBKG(hInstance,hdc);
	m_pGetBtn->BltBKG(m_hMemDc,FLAGE_TRANSBLT);

	BltBKG(hdc,FLAG_STRECHBLT);
}

void CSelectBKG5::IsOnBtn(POINT &ptMouse)
{
	m_pOkBtn->IsOnBtn(ptMouse);
	m_pGetBtn->IsOnBtn(ptMouse);
}

int CSelectBKG5::IsClickOnBtn()
{
	int btnId;
	if (btnId = m_pOkBtn->IsClickOnBtn())
		return btnId;
	if (btnId = m_pGetBtn->IsClickOnBtn())
	{
		int numCoin = m_pPlayer->getObjNumInBag(OBJECT_COIN);
		if (numCoin > 9)
		{
			for (int i = 0;i != 10;++i)
				m_pPlayer->IsUseObject(OBJECT_COIN);
			return btnId;
		}
		return FALSE;
	}

	return FALSE;
}
