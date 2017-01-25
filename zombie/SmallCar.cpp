#include "stdafx.h"

CSmallCar::CSmallCar():CCar(OBJECT_SMALLCAR,130,50)
{

}

CSmallCar::~CSmallCar()
{

}

void CSmallCar::Draw(HINSTANCE hInstance, HDC hdc)
{
	HDC hMemDc = CreateCompatibleDC(hdc);
	HBITMAP hbmp = LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_SMALLCAR));
	SelectObject(hMemDc,hbmp);
	BitBlt(hdc,m_ptPosition.x,m_ptPosition.y,m_iWidth,m_iHeigth,
		hMemDc,0,0,SRCCOPY);
	DeleteDC(hMemDc);
	DeleteObject(hbmp);
}

int CSmallCar::IsOnObject(POINT ptPos)
{
	if (ptPos.y >= m_ptPosition.y
		&& ptPos.y < m_ptPosition.y + m_iHeigth
		&& ptPos.x >= m_ptPosition.x
		&& ptPos.x < m_ptPosition.x + m_iWidth)
		return ON_BOTTOMFLOOR;
	return ON_NOTHING;
}

bool CSmallCar::IsBulletOn(CBullet *pBullet)
{
	return false;
}

int CSmallCar::OnObjectWhere(POINT &ptPos)
{
	if (ptPos.x < m_ptPosition.x + 17)
		return (m_ptPosition.y + 20);
	if (ptPos.x < m_ptPosition.x + 41)
		return (m_ptPosition.y + 10);
	if (ptPos.x > m_ptPosition.x + 117)
		return (m_ptPosition.y + 26);
	if (ptPos.x > m_ptPosition.x + 100)
		return (m_ptPosition.y + 17);
	if (ptPos.x > m_ptPosition.x + 77)
		return (m_ptPosition.y + 10);
	return m_ptPosition.y;
}