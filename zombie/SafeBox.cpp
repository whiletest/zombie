#include "stdafx.h"
#include "resource.h"

CSafeBox::CSafeBox():CSceneObject(OBJECT_SAFEBOX,28,20),m_bOpened(false)
{

}

CSafeBox::~CSafeBox()
{

}

void CSafeBox::Draw(HINSTANCE hInstance,HDC hdc)
{
	HDC hMemDc = CreateCompatibleDC(hdc);
	HBITMAP hbmpTree = LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_SAFEBOX));
	SelectObject(hMemDc,hbmpTree);
	BitBlt(hdc,m_ptPosition.x,m_ptPosition.y,m_iWidth,m_iHeigth,
		hMemDc,0,0,SRCCOPY);
	DeleteDC(hMemDc);
	DeleteObject(hbmpTree);
}

int CSafeBox::IsOnObject(POINT ptPos)
{
	return ON_NOTHING;
}

bool CSafeBox::IsBulletOn(CBullet *pBullet)
{
	return false;
}

void CSafeBox::SetRelativeBulletSupply(CSceneObject *pSceneObj)
{
	m_pBulletSupply = (CBulletSupply*)pSceneObj;
}

void CSafeBox::OpenSafeBox()
{
	POINT ptNewPos = {455,592};
	m_pBulletSupply->SetPosition(ptNewPos);

	m_bOpened = true;
}