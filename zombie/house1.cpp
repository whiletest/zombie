#include "stdafx.h"
#include "resource.h"

CHouse1::CHouse1():CSceneObject(OBJECT_HOUSE1,0,0),m_iIndex(IDB_HOUSE1)
{

}

CHouse1::~CHouse1()
{

}

void CHouse1::Draw(HINSTANCE hInstance,HDC hdc)
{
	HDC hMemDc = CreateCompatibleDC(hdc);
	HBITMAP hbmpTree = LoadBitmap(hInstance,MAKEINTRESOURCE(m_iIndex));
	SelectObject(hMemDc,hbmpTree);
	BitBlt(hdc,m_ptPosition.x,m_ptPosition.y,m_iWidth,m_iHeigth,
		hMemDc,0,0,SRCCOPY);
	DeleteDC(hMemDc);
	DeleteObject(hbmpTree);
}

int CHouse1::IsOnObject(POINT ptPos)
{
	return ON_NOTHING;
}

bool CHouse1::IsBulletOn(CBullet *pBullet)
{
	return false;
}