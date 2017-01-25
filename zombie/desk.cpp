#include "stdafx.h"
#include "resource.h"

CDesk::CDesk():CSceneObject(OBJECT_DESK,50,30)
{

}

CDesk::~CDesk()
{

}

void CDesk::Draw(HINSTANCE hInstance,HDC hdc)
{
	HDC hMemDc = CreateCompatibleDC(hdc);
	HBITMAP hbmpTree = LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_DESK));
	SelectObject(hMemDc,hbmpTree);
	BitBlt(hdc,m_ptPosition.x,m_ptPosition.y,m_iWidth,m_iHeigth,
		hMemDc,0,0,SRCCOPY);
	DeleteDC(hMemDc);
	DeleteObject(hbmpTree);
}

int CDesk::IsOnObject(POINT ptPos)
{
	if (ptPos.y >= m_ptPosition.y
		&& ptPos.y < m_ptPosition.y + m_iHeigth
		&& ptPos.x >= m_ptPosition.x
		&& ptPos.x < m_ptPosition.x + m_iWidth)
		return ON_BOTTOMFLOOR;
	return ON_NOTHING;
}

bool CDesk::IsBulletOn(CBullet *pBullet)
{
	return false;
}
