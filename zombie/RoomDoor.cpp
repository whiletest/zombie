#include "stdafx.h"

CRoomDoor::CRoomDoor():CDoor(OBJECT_ROOM_DOOR,0,0)
{

}

CRoomDoor::~CRoomDoor()
{

}

void CRoomDoor::Draw(HINSTANCE hInstance, HDC hdc)
{
	HDC hMemDc = CreateCompatibleDC(hdc);
	HBITMAP hbmp = LoadBitmap(hInstance,MAKEINTRESOURCE(m_iDoorType));
	SelectObject(hMemDc,hbmp);
	BitBlt(hdc,m_ptPosition.x,m_ptPosition.y,m_iWidth,m_iHeigth,
		hMemDc,0,0,SRCCOPY);
	DeleteDC(hMemDc);
	DeleteObject(hbmp);
}

int CRoomDoor::IsOnObject(POINT ptPos)
{
	return ON_NOTHING;
}

bool CRoomDoor::IsBulletOn(CBullet *pBullet)
{
	return false;
}