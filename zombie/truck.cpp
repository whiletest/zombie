#include "stdafx.h"

CTruck::CTruck():CCar(OBJECT_TRUCK,0,0)
{

}

CTruck::~CTruck()
{

}

void CTruck::SetTruckKind(_objectIdentify id,
						  int iWidth,
						  int iHeight)
{
	m_iObjectId = id;
	m_iWidth = iWidth;
	m_iHeigth = iHeight;
}

void CTruck::Draw(HINSTANCE hInstance, HDC hdc)
{
	int bmpId;
	switch (m_iObjectId)
	{
	case OBJECT_TRUCK:
		bmpId = IDB_TRUCK;
		break;
	case OBJECT_TRUCK1:
		bmpId = IDB_TRUCK1;
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

int CTruck::IsOnObject(POINT ptPos)
{
	if (ptPos.y >= m_ptPosition.y
		&& ptPos.y < m_ptPosition.y + m_iHeigth/3
		&& ptPos.x >= m_ptPosition.x
		&& ptPos.x < m_ptPosition.x + m_iWidth)
		return ON_BOTTOMFLOOR;
	return ON_NOTHING;
}
