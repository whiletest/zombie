#include "stdafx.h"
#include "resource.h"

CWashPot::CWashPot():CSceneObject(OBJECT_WASHPOT,60,40)
{

}

CWashPot::~CWashPot()
{

}

void CWashPot::Draw(HINSTANCE hInstance,HDC hdc)
{
	HDC hMemDc = CreateCompatibleDC(hdc);
	HBITMAP hbmpTree = LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_WASHPOT));
	SelectObject(hMemDc,hbmpTree);
	BitBlt(hdc,m_ptPosition.x,m_ptPosition.y,m_iWidth,m_iHeigth,
		hMemDc,0,0,SRCCOPY);
	DeleteDC(hMemDc);
	DeleteObject(hbmpTree);
}

int CWashPot::IsOnObject(POINT ptPos)
{
	return ON_NOTHING;
}

bool CWashPot::IsBulletOn(CBullet *pBullet)
{
	return false;
}