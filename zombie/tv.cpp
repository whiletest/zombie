#include "stdafx.h"
#include "resource.h"

CTv::CTv():CSceneObject(OBJECT_TV,50,35),
		   m_bOnPower(false),
		   m_bDisk(false)
{

}

CTv::~CTv()
{

}

void CTv::Draw(HINSTANCE hInstance,HDC hdc)
{
	HDC hMemDc = CreateCompatibleDC(hdc);
	HBITMAP hbmpTree = LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_TV));
	SelectObject(hMemDc,hbmpTree);
	BitBlt(hdc,m_ptPosition.x,m_ptPosition.y,m_iWidth,m_iHeigth,
		hMemDc,0,0,SRCCOPY);
	DeleteDC(hMemDc);
	DeleteObject(hbmpTree);
}

int CTv::IsOnObject(POINT ptPos)
{
	if ( ptPos.y >= m_ptPosition.y 
		&& ptPos.y < m_ptPosition.y + m_iHeigth
		&& ptPos.x >= m_ptPosition.x
		&& ptPos.x < m_ptPosition.x + m_iWidth )
		return ON_BOTTOMFLOOR;
	return ON_NOTHING;
}

bool CTv::IsBulletOn(CBullet *pBullet)
{
	return false;
}