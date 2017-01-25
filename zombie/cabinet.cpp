#include "stdafx.h"
#include "resource.h"

CCabinet::CCabinet():CSceneObject(OBJECT_CABINET,100,80),m_bOpen(false),m_pWeapon(0)
{

}

CCabinet::~CCabinet()
{

}

void CCabinet::Draw(HINSTANCE hInstance,HDC hdc)
{
	int ibmpID;
	if (m_bOpen)
		ibmpID = IDB_CABINETOPEN;
	else
		ibmpID = IDB_CABINETCLOSE;
	HDC hMemDc = CreateCompatibleDC(hdc);
	HBITMAP hbmpTree = LoadBitmap(hInstance,MAKEINTRESOURCE(ibmpID));
	SelectObject(hMemDc,hbmpTree);
	TransparentBlt(hdc,m_ptPosition.x,m_ptPosition.y,m_iWidth,m_iHeigth,
		hMemDc,0,0,m_iWidth,m_iHeigth,RGB(255,255,255));
	DeleteDC(hMemDc);
	DeleteObject(hbmpTree);
}

bool CCabinet::UseCabinet(CWeapon **ppWeapon)
{
	m_bOpen = !m_bOpen;
	if (m_bOpen)
	{
		if (!m_pWeapon)
		{
			m_pWeapon = new CBow;
			POINT pos = {400,580};
			m_pWeapon->SetPosOnGround(pos);
			*ppWeapon = m_pWeapon;

			return true;
		}
	}

	return false;
}