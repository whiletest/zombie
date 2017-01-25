#include "stdafx.h"
#include "resource.h"

CWindow1::CWindow1():CSceneObject(OBJECT_WINDOW1,50,50),
                     m_state(ws_ok),
					 m_bmpId(IDB_WINDOW2)
{

}


void CWindow1::Draw(HINSTANCE hInstance,HDC hdc)
{
	HDC hMemDc = CreateCompatibleDC(hdc);
	HBITMAP hbmp = LoadBitmap(hInstance,MAKEINTRESOURCE(m_bmpId));
	SelectObject(hMemDc,hbmp);
	BitBlt(hdc,m_ptPosition.x,m_ptPosition.y,m_iWidth,m_iHeigth,
		hMemDc,0,0,SRCCOPY);
	DeleteDC(hMemDc);
	DeleteObject(hbmp);
}


bool CWindow1::IsBulletOn(CBullet *pBullet)
{
	RECT rcObj;
	GetObjRect(rcObj);
	if (PtInRect(&rcObj,pBullet->GetPosition()))
	{
		if (m_state == ws_crack)
		{
			m_state = ws_broken;
			m_bmpId = IDB_WINDOWBROKEN;
		}
		return true;
	}
	return false;
}