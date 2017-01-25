#include "stdafx.h"
#include "resource.h"

CRoadSign::CRoadSign():CSceneObject(OBJECT_ROADSIGN,45,51)
{

}

CRoadSign::~CRoadSign()
{

}

void CRoadSign::Draw(HINSTANCE hInstance,HDC hdc)
{
	HDC hMemDc = CreateCompatibleDC(hdc);
	HBITMAP hbmpTree = LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_ROADSIGN));
	if (!hbmpTree)
		exit(0);
	SelectObject(hMemDc,hbmpTree);
	BitBlt(hdc,m_ptPosition.x,m_ptPosition.y,m_iWidth,m_iHeigth,
		hMemDc,0,0,SRCCOPY);
	DeleteDC(hMemDc);
	DeleteObject(hbmpTree);
}

int CRoadSign::IsOnObject(POINT ptPos)
{
	return ON_NOTHING;
}

bool CRoadSign::IsBulletOn(CBullet *pBullet)
{
	return false;
}