#include "stdafx.h"
#include "resource.h"

CBed::CBed():CSceneObject(OBJECT_BED,180,68)
{

}

CBed::~CBed()
{

}

void CBed::Draw(HINSTANCE hInstance,HDC hdc)
{
	HDC hMemDc = CreateCompatibleDC(hdc);
	HBITMAP hbmpTree = LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_BED));
	SelectObject(hMemDc,hbmpTree);
	BitBlt(hdc,m_ptPosition.x,m_ptPosition.y,m_iWidth,m_iHeigth,
		hMemDc,0,0,SRCCOPY);
	DeleteDC(hMemDc);
	DeleteObject(hbmpTree);
}

int CBed::IsOnObject(POINT ptPos)
{
	if ( ptPos.y >= m_ptPosition.y + 38
		&& ptPos.y < m_ptPosition.y + m_iHeigth
		&& ptPos.x >= m_ptPosition.x
		&& ptPos.x < m_ptPosition.x + m_iWidth )
		return ON_BOTTOMFLOOR;
	return ON_NOTHING;
}

bool CBed::IsBulletOn(CBullet *pBullet)
{
	return false;
}

int CBed::OnObjectWhere(POINT &ptPos)
{
	return ( m_ptPosition.y + 38 );
}