#include "stdafx.h"

CLadder::CLadder():CSceneObject(OBJECT_LADDER,299,196)
{
	m_keyPoint[0].x = 53;m_keyPoint[0].y = 0;
	m_keyPoint[1].x = 84;m_keyPoint[1].y = 22;
	m_keyPoint[2].x = 115;m_keyPoint[2].y = 42;
	m_keyPoint[3].x = 140;m_keyPoint[3].y = 66;
	m_keyPoint[4].x = 172;m_keyPoint[4].y = 84;
	m_keyPoint[5].x = 194;m_keyPoint[5].y = 105;
	m_keyPoint[6].x = 214;m_keyPoint[6].y = 123;
	m_keyPoint[7].x = 241;m_keyPoint[7].y = 141;
	m_keyPoint[8].x = 267;m_keyPoint[8].y = 158;
	m_keyPoint[9].x = m_iWidth;m_keyPoint[9].y = 177;
	m_keyPoint[10].x = m_iWidth;m_keyPoint[10].y = m_iHeigth;
}

CLadder::~CLadder()
{

}

void CLadder::Draw(HINSTANCE hInstance, HDC hdc)
{
	HDC hMemDc = CreateCompatibleDC(hdc);
	HBITMAP hbmp = LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_LADDER));
	SelectObject(hMemDc,hbmp);
	BitBlt(hdc,m_ptPosition.x,m_ptPosition.y,m_iWidth,m_iHeigth,
		hMemDc,0,0,SRCCOPY);
	DeleteDC(hMemDc);
	DeleteObject(hbmp);
}

int CLadder::IsOnObject(POINT ptPos)
{
	const int litte = 2; //上楼时用
	RECT rcRrea; 
	POINT ptLeftTop = m_ptPosition; //左上角
	for (int i = 0;i != 10;++i)
	{
		rcRrea.left = ptLeftTop.x;
		rcRrea.top = ptLeftTop.y;
		rcRrea.right = m_ptPosition.x + m_keyPoint[i].x + litte;
		rcRrea.bottom = m_ptPosition.y + m_keyPoint[i+1].y + litte;

		if (PtInRect(&rcRrea,ptPos))
			return ON_BOTTOMFLOOR;

		ptLeftTop.x = rcRrea.right - litte;
		ptLeftTop.y = rcRrea.bottom - litte;
	}
	return ON_NOTHING;
}

int CLadder::OnObjectWhere(POINT &ptPos)
{
	for (int i = 0;i != 11;++i)
	{
		if (ptPos.x <= m_ptPosition.x + m_keyPoint[i].x)
		{
			return m_ptPosition.y + m_keyPoint[i].y;
		}
	}
	return m_ptPosition.y + m_iHeigth;
}