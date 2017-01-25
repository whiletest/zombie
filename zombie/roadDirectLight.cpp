#include "stdafx.h"


CRoadDirectLight::CRoadDirectLight():CDoor(OBJECT_ROADDIRECTLIGHT,0,0)
{

}

CRoadDirectLight::~CRoadDirectLight()
{

}

void CRoadDirectLight::Draw(HINSTANCE hInstance, HDC hdc)
{
	static int count = 0;
	int id;

	count = (count+1)%50;
	if (count < 25)
		id = IDB_ROADDIRECTLIGHT;
	else
		id = IDB_ROADDIRECTLIGHT1;

	HDC hMemDc = CreateCompatibleDC(hdc);
	HBITMAP hbmp = LoadBitmap(hInstance,MAKEINTRESOURCE(id));
	SelectObject(hMemDc,hbmp);

	if (m_bMouseOnObj)
		TextOut(hdc,m_ptPosition.x-40,m_ptPosition.y-15,TEXT("红绿灯/按E进入邻接街道"),12);

	BitBlt(hdc,m_ptPosition.x,m_ptPosition.y,m_iWidth,m_iHeigth,
		hMemDc,0,0,SRCCOPY);
	DeleteDC(hMemDc);
	DeleteObject(hbmp);
}