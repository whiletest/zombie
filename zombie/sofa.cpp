#include "stdafx.h"
#include "resource.h"

CSofa::CSofa():CSceneObject(OBJECT_SOFA,86,50)
{

}

CSofa::~CSofa()
{

}

void CSofa::Draw(HINSTANCE hInstance,HDC hdc)
{
	HDC hMemDc = CreateCompatibleDC(hdc);
	HBITMAP hbmpTree = LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_SOFA));
	SelectObject(hMemDc,hbmpTree);
	BitBlt(hdc,m_ptPosition.x,m_ptPosition.y,m_iWidth,m_iHeigth,
		hMemDc,0,0,SRCCOPY);
	DeleteDC(hMemDc);
	DeleteObject(hbmpTree);
}

int CSofa::IsOnObject(POINT ptPos)
{
	if (ptPos.y >= m_ptPosition.y
		&& ptPos.y < m_ptPosition.y + m_iHeigth
		&& ptPos.x >= m_ptPosition.x
		&& ptPos.x < m_ptPosition.x + m_iWidth)
		return ON_BOTTOMFLOOR;
	return ON_NOTHING;
}

bool CSofa::IsBulletOn(CBullet *pBullet)
{
	return false;
}

int CSofa::OnObjectWhere(POINT &ptPos)
{
	if (ptPos.x < m_ptPosition.x + 7
		|| ptPos.x > m_ptPosition.x + 77)
		return m_ptPosition.y+21;

	return m_ptPosition.y+26;
}