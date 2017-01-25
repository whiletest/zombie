#include "stdafx.h"

CMask::CMask(int id /* = OBJECT_MASK1 */,
			 int iwidth /* = 24 */,
			 int height /* = 20 */):
             CSceneObject(id,iwidth,height)
{

}

CMask::~CMask()
{

}


void CMask::Draw(HINSTANCE hInstance, HDC hdc)
{
	int bmpId = 0;
	switch (m_iObjectId)
	{
	case OBJECT_MASK1:
		bmpId = IDB_MASK1;
		break;
	case OBJECT_MASK2:
		bmpId = IDB_MASK2;
		break;
	default:
		break;
	}

	HDC hMemDc = CreateCompatibleDC(hdc);
	HBITMAP hbmp = LoadBitmap(hInstance,MAKEINTRESOURCE(bmpId));
	SelectObject(hMemDc,hbmp);

	if (m_bMouseOnObj)
		TextOut(hdc,m_ptPosition.x,m_ptPosition.y-15,TEXT("Ãæ¾ß"),2);

	BitBlt(hdc,m_ptPosition.x,m_ptPosition.y,m_iWidth,m_iHeigth,
		hMemDc,0,0,SRCCOPY);
	DeleteDC(hMemDc);
	DeleteObject(hbmp);
}