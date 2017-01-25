#include "stdafx.h"
#include "resource.h"

CMessiPaper::CMessiPaper():CSceneObject(OBJECT_MESSIPAPER,50,40)
{

}

CMessiPaper::~CMessiPaper()
{

}

void CMessiPaper::Draw(HINSTANCE hInstance,HDC hdc)
{
	HDC hMemDc = CreateCompatibleDC(hdc);
	HBITMAP hbmpTree = LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_MESSIPAPER));
	SelectObject(hMemDc,hbmpTree);
	BitBlt(hdc,m_ptPosition.x,m_ptPosition.y,m_iWidth,m_iHeigth,
		hMemDc,0,0,SRCCOPY);
	DeleteDC(hMemDc);
	DeleteObject(hbmpTree);
}

int CMessiPaper::IsOnObject(POINT ptPos)
{
	return ON_NOTHING;
}

bool CMessiPaper::IsBulletOn(CBullet *pBullet)
{
	return false;
}
