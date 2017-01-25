#include "stdafx.h"
#include "resource.h"

CBuiding::CBuiding():CSceneObject(OBJECT_BUIDING,926,500)
{

}

CBuiding::~CBuiding()
{

}

void CBuiding::Draw(HINSTANCE hInstance,HDC hdc)
{
	HDC hMemDc = CreateCompatibleDC(hdc);
	HBITMAP hbmp = LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_BUIDING));
	SelectObject(hMemDc,hbmp);
	BitBlt(hdc,m_ptPosition.x,m_ptPosition.y,m_iWidth,m_iHeigth,
		hMemDc,0,0,SRCCOPY);
	DeleteDC(hMemDc);
	DeleteObject(hbmp);
}

