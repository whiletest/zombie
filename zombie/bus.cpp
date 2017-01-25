#include "stdafx.h"

CBus::CBus():CCar(OBJECT_BUS,367,100)
{

}

CBus::~CBus()
{

}

void CBus::Draw(HINSTANCE hInstance, HDC hdc)
{
	HDC hMemDc = CreateCompatibleDC(hdc);
	HBITMAP hbmp = LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_BUS));
	SelectObject(hMemDc,hbmp);
	BitBlt(hdc,m_ptPosition.x,m_ptPosition.y,m_iWidth,m_iHeigth,
		hMemDc,0,0,SRCCOPY);
	DeleteDC(hMemDc);
	DeleteObject(hbmp);
}

int CBus::IsOnObject(POINT ptPos)
{
	if (ptPos.y >= m_ptPosition.y
		&& ptPos.y < m_ptPosition.y + m_iHeigth/3
		&& ptPos.x >= m_ptPosition.x
		&& ptPos.x < m_ptPosition.x + m_iWidth)
		return ON_BOTTOMFLOOR;
	return ON_NOTHING;
}

bool CBus::IsBulletOn(CBullet *pBullet)
{
	return false;
}