#include "stdafx.h"
#include "resource.h"

CHomeGate::CHomeGate():CSceneObject(OBJECT_HOMEGATE,200,112)
{

}

CHomeGate::~CHomeGate()
{

}

void CHomeGate::Draw(HINSTANCE hInstance,HDC hdc)
{
	HDC hMemDc = CreateCompatibleDC(hdc);
	HBITMAP hbmpTree = LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_MENTALDOOR));
	SelectObject(hMemDc,hbmpTree);
	BitBlt(hdc,m_ptPosition.x,m_ptPosition.y,m_iWidth,m_iHeigth,
		hMemDc,0,0,SRCCOPY);
	DeleteDC(hMemDc);
	DeleteObject(hbmpTree);
}

int CHomeGate::IsOnObject(POINT ptPos)
{
	return ON_NOTHING;
}

bool CHomeGate::IsBulletOn(CBullet *pBullet)
{
	return false;
}