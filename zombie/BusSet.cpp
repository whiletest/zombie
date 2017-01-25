#include "stdafx.h"
#include "resource.h"

CBusSet::CBusSet():CSceneObject(OBJECT_BUSSET,21,22)
{

}

CBusSet::~CBusSet()
{

}

void CBusSet::Draw(HINSTANCE hInstance,HDC hdc)
{
	HDC hMemDc = CreateCompatibleDC(hdc);
	HBITMAP hbmpTree = LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_BUSSET));
	SelectObject(hMemDc,hbmpTree);
	BitBlt(hdc,m_ptPosition.x,m_ptPosition.y,m_iWidth,m_iHeigth,
		hMemDc,0,0,SRCCOPY);
	DeleteDC(hMemDc);
	DeleteObject(hbmpTree);
}

int CBusSet::IsOnObject(POINT ptPos)
{
	if ( ptPos.y >= m_ptPosition.y
		&& ptPos.y < m_ptPosition.y + m_iHeigth
		&& ptPos.x >= m_ptPosition.x
		&& ptPos.x < m_ptPosition.x + m_iWidth )
		return ON_BOTTOMFLOOR;
	return ON_NOTHING;
}

bool CBusSet::IsBulletOn(CBullet *pBullet)
{
	return false;
}

int CBusSet::OnObjectWhere(POINT &ptPos)
{
	return ( m_ptPosition.y + 10 );
}