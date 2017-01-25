#include "stdafx.h"
#include "resource.h"

CStick::CStick():CSceneObject(OBJECT_STICK,12,21)
{

}

CStick::~CStick()
{

}

void CStick::Draw(HINSTANCE hInstance,HDC hdc)
{
	HDC hMemDc = CreateCompatibleDC(hdc);
	HBITMAP hbmpTree = LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_STICK));
	SelectObject(hMemDc,hbmpTree);
	BitBlt(hdc,m_ptPosition.x,m_ptPosition.y,m_iWidth,m_iHeigth,
		hMemDc,0,0,SRCCOPY);
	DeleteDC(hMemDc);
	DeleteObject(hbmpTree);
}

int CStick::IsOnObject(POINT ptPos)
{
	return ON_NOTHING;
}

bool CStick::IsBulletOn(CBullet *pBullet)
{
	return false;
}