#include "stdafx.h"
#include "resource.h"

CBulletSupply::CBulletSupply():CSceneObject(OBJECT_BULLETSUPPLY,14,4)
{

}

CBulletSupply::~CBulletSupply()
{

}

void CBulletSupply::Draw(HINSTANCE hInstance,HDC hdc)
{
	HDC hMemDc = CreateCompatibleDC(hdc);
	HBITMAP hbmpTree = LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_BULLETSUPPLY));
	SelectObject(hMemDc,hbmpTree);

	if (m_bMouseOnObj)
		TextOut(hdc,m_ptPosition.x,m_ptPosition.y-15,TEXT("×Óµ¯"),2);

	BitBlt(hdc,m_ptPosition.x,m_ptPosition.y,m_iWidth,m_iHeigth,
		hMemDc,0,0,SRCCOPY);
	DeleteDC(hMemDc);
	DeleteObject(hbmpTree);
}

int CBulletSupply::IsOnObject(POINT ptPos)
{
	return ON_NOTHING;
}

bool CBulletSupply::IsBulletOn(CBullet *pBullet)
{
	return false;
}