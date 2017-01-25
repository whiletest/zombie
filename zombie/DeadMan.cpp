#include "stdafx.h"
#include "resource.h"


CDeadMan::CDeadMan():CDead(ID_DEADMAN,0,0,0,0,0)
{
	//…Ë÷√π•ª˜∑∂Œß
	m_rcAttack.left = m_rcAttack.top = 0;
	m_rcAttack.right = 0;
	m_rcAttack.bottom = 0;

	m_bDied = true;
}

CDeadMan::~CDeadMan()
{

}

void CDeadMan::SetHuntRect(const RECT &rcClient)
{
	m_rcHunt.right = 0;
	m_rcHunt.bottom = 0; 
}

void CDeadMan::DrawDiedZombie(HINSTANCE hInstance,HDC hdc)
{
}

void CDeadMan::Draw(HINSTANCE hInstance,HDC hdc)
{
	int ibmpDeadID;
	switch (m_iIndex)
	{
	case 1:
		ibmpDeadID = IDB_DEADMAN1;
		break;
	case 2:
		ibmpDeadID = IDB_SMALLZOMBIEDIEL;
		break;
	case 3:
		ibmpDeadID = IDB_SMALLZOMBIEDIER;
		break;
	default:
		break;
	}
	HBITMAP hbmpZombie = LoadBitmap(hInstance,MAKEINTRESOURCE(ibmpDeadID));
	HDC hMemdc = CreateCompatibleDC(hdc);
	SelectObject(hMemdc,hbmpZombie);
	TransparentBlt(hdc,m_ptCurPos.x-m_iWidth/2,m_ptCurPos.y-m_iHeigth,
		m_iWidth,m_iHeigth,
		hMemdc,0,0,m_iWidth,m_iHeigth,RGB(255,255,255));
	DeleteDC(hMemdc);
	DeleteObject(hbmpZombie);

}

bool CDeadMan::Move(CPlayer &player,const RECT &rc)
{
	return false;
}