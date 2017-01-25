#include "stdafx.h"

CKey::CKey():CSceneObject(OBJECT_KEY,10,16),
			m_iKeyIndex(0),
			m_bAbleToShootOn(false)
{

}

CKey::~CKey()
{

}

void CKey::Draw(HINSTANCE hInstance, HDC hdc)
{
	HDC hMemDc = CreateCompatibleDC(hdc);
	HBITMAP hbmp = LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_KEY));
	SelectObject(hMemDc,hbmp);
	TransparentBlt(hdc,m_ptPosition.x,m_ptPosition.y,m_iWidth,m_iHeigth,
		hMemDc,0,0,m_iWidth,m_iHeigth,RGB(255,255,255));
	DeleteDC(hMemDc);
	DeleteObject(hbmp);
}

int CKey::IsOnObject(POINT ptPos)
{
	return ON_NOTHING;
}

bool CKey::IsBulletOn(CBullet *pBullet)
{
	if (m_bAbleToShootOn)
	{
		POINT ptPos = pBullet->GetPosition();
		RECT rcRect = {m_ptPosition.x-5,m_ptPosition.y-5,
					   m_ptPosition.x + m_iWidth,
					   m_ptPosition.y + m_iHeigth};
		if ( PtInRect(&rcRect,ptPos) )
		{
			m_ptPosition.y = 605;
			return true;
		}
	}
	return false;
}