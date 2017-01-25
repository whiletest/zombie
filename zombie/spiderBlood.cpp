#include "stdafx.h"

CSpiderBlood::CSpiderBlood():CSceneObject(OBJECT_SPIDERBLOOD,24,24)
{

}

void CSpiderBlood::Draw(HINSTANCE hInstance, HDC hdc)
{
	HDC hMemDc = CreateCompatibleDC(hdc);
	HBITMAP hbmp = LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_SPIDERBLOOD));
	SelectObject(hMemDc,hbmp);

	if (m_bMouseOnObj)
		TextOut(hdc,m_ptPosition.x,m_ptPosition.y-15,TEXT("Ö©ÖëÑªÒº"),4);

	BitBlt(hdc,m_ptPosition.x,m_ptPosition.y,m_iWidth,m_iHeigth,
		hMemDc,0,0,SRCCOPY);
	DeleteDC(hMemDc);
	DeleteObject(hbmp);
}