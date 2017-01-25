#include "stdafx.h"
#include "resource.h"

CPaper::CPaper():CSceneObject(OBJECT_PAPER,28,18),m_iIndex(1)
{

}

CPaper::~CPaper()
{

}

void CPaper::Draw(HINSTANCE hInstance,HDC hdc)
{
	HDC hMemDc = CreateCompatibleDC(hdc);
	HBITMAP hbmpTree = LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_PAPER));
	SelectObject(hMemDc,hbmpTree);
	BitBlt(hdc,m_ptPosition.x,m_ptPosition.y,m_iWidth,m_iHeigth,
		hMemDc,0,0,SRCCOPY);
	DeleteDC(hMemDc);
	DeleteObject(hbmpTree);
}

int CPaper::IsOnObject(POINT ptPos)
{
	return ON_NOTHING;
}

bool CPaper::IsBulletOn(CBullet *pBullet)
{
	return false;
}
