#include "stdafx.h"
#include "resource.h"

CDisk::CDisk():CSceneObject(OBJECT_DISK,20,10)
{

}

CDisk::~CDisk()
{

}

void CDisk::Draw(HINSTANCE hInstance,HDC hdc)
{
	HDC hMemDc = CreateCompatibleDC(hdc);
	HBITMAP hbmpTree = LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_DISK));
	SelectObject(hMemDc,hbmpTree);
	BitBlt(hdc,m_ptPosition.x,m_ptPosition.y,m_iWidth,m_iHeigth,
		hMemDc,0,0,SRCCOPY);
	DeleteDC(hMemDc);
	DeleteObject(hbmpTree);
}

int CDisk::IsOnObject(POINT ptPos)
{
	return ON_NOTHING;
}

bool CDisk::IsBulletOn(CBullet *pBullet)
{
	return false;
}