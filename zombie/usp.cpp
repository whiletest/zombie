#include "stdafx.h"
#include "resource.h"

extern void RotateBitmap(HDC,int,int,double,double,HDC,POINT*);

CUSP::CUSP():CWeapon(ID_USP,KIND_HANDGUN,
					30,17,12,48,163)
{
	m_iHurt = 20;
	lstrcpy(m_szWeaponName,TEXT("USP"));
}

CUSP::~CUSP()
{

}

void CUSP::Fire(const POINT &ptPos,double sinA,double cosA)
{
	if (m_iBulletNum)
	{
		CBullet *pBullet = new CDEBullet;
		pBullet->SetBulletPos(ptPos);
		pBullet->SetAngleValue(sinA,cosA);
		pBullet->SetHurt(25);
		m_vecBullet.push_back(pBullet);
		--m_iBulletNum;

		PlayFireSound();
	}
	else
		PlayNoBulletFireSound();
}

void CUSP::DrawOnGround(HINSTANCE hInstance, HDC hdc)
{
	HDC hMemDc = CreateCompatibleDC(hdc);
	HBITMAP hbmp = LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_USPRIGHT));
	SelectObject(hMemDc,hbmp);
	TransparentBlt(hdc,m_ptPosOnGround.x,m_ptPosOnGround.y,m_iWidth,m_iHeigth,
		hMemDc,0,0,m_iWidth,m_iHeigth,RGB(255,255,255));
	DeleteDC(hMemDc);
	DeleteObject(hbmp);
}

void CUSP::Draw(HINSTANCE hInstance, 
						HDC hdc, 
						int iFace, 
						POINT ptPos,
						double sinA,
						double cosA
						)
{
	HDC hMemDc = CreateCompatibleDC(hdc);
	int iGunId;
	switch (iFace)
	{
	case FACE_LEFT:
		iGunId = IDB_USPLEFT;
		ptPos.x -= (m_iWidth-5);
		ptPos.y -= 15;
		break;
	case FACE_RIGHT:
		iGunId = IDB_USPRIGHT;
		ptPos.x -= 5;
		ptPos.y -= 10;
		if (sinA < -0.5f)
			ptPos.y -= 10;
		break;
	default:
		break;
	}
	HBITMAP hbmpGun = LoadBitmap(hInstance,MAKEINTRESOURCE(iGunId));
	SelectObject(hMemDc,hbmpGun);
	RotateBitmap(hMemDc,m_iWidth,m_iHeigth,sinA,cosA,hdc,&ptPos);
	DeleteDC(hMemDc);
	DeleteObject(hbmpGun);
}
