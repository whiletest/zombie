#include "stdafx.h"

CGrass::CGrass():CSceneObject(OBJECT_GRASS,115,36)
{

}

CGrass::~CGrass()
{

}

void CGrass::Draw(HINSTANCE hInstance, HDC hdc)
{
	HDC hMemDc = CreateCompatibleDC(hdc);
	HBITMAP hbmp = LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_GRASS));
	SelectObject(hMemDc,hbmp);
	BitBlt(hdc,m_ptPosition.x,m_ptPosition.y,m_iWidth,m_iHeigth,
		hMemDc,0,0,SRCCOPY);
	DeleteDC(hMemDc);
	DeleteObject(hbmp);
}

int CGrass::IsOnObject(POINT ptPos)
{
	if (ptPos.y >= m_ptPosition.y
		&& ptPos.y < m_ptPosition.y + m_iHeigth
		&& ptPos.x >= m_ptPosition.x
		&& ptPos.x < m_ptPosition.x + m_iWidth)
		return ON_GRASS;
	return ON_NOTHING;
}

bool CGrass::IsBulletOn(CBullet *pBullet)
{
	return false;
}