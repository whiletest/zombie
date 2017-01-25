#include "stdafx.h"

CBike::CBike():CCar(OBJECT_BIKE,0,0)
{

}

CBike::~CBike()
{

}

void CBike::SetBikeKind(_objectIdentify id,
						  int iWidth,
						  int iHeight)
{
	m_iObjectId = id;
	m_iWidth = iWidth;
	m_iHeigth = iHeight;
}

void CBike::Draw(HINSTANCE hInstance, HDC hdc)
{
	int bmpId;
	switch (m_iObjectId)
	{
	case OBJECT_BIKE:
		bmpId = IDB_BIKE;
		break;
	default:
		return;
	}
	HDC hMemDc = CreateCompatibleDC(hdc);
	HBITMAP hbmp = LoadBitmap(hInstance,MAKEINTRESOURCE(bmpId));
	SelectObject(hMemDc,hbmp);
	BitBlt(hdc,m_ptPosition.x,m_ptPosition.y,m_iWidth,m_iHeigth,
		hMemDc,0,0,SRCCOPY);
	DeleteDC(hMemDc);
	DeleteObject(hbmp);
}

int CBike::IsOnObject(POINT ptPos)
{
	return ON_NOTHING;
}
