#include "stdafx.h"
#include "resource.h"

extern void RotateBitmap(HDC,int,int,double,double,HDC,POINT*);

CMP5::CMP5():CWeapon(ID_MP5,KIND_LONGGUN,
						50,23,30,120,91)
{
	m_iHurt = 19;
	lstrcpy(m_szWeaponName,TEXT("MP5"));
}

CMP5::~CMP5()
{

}

void CMP5::Fire(const POINT &ptPos,double sinA,double cosA)
{
	if (m_iBulletNum)
	{
		CBullet *pBullet = new CDEBullet;
		pBullet->SetBulletPos(ptPos);
		pBullet->SetAngleValue(sinA,cosA);
		pBullet->SetHurt(19);
		m_vecBullet.push_back(pBullet);
		--m_iBulletNum;

		PlayFireSound();
	}
	else
		PlayNoBulletFireSound();
}

void CMP5::DrawOnGround(HINSTANCE hInstance, HDC hdc)
{
	HDC hMemDc = CreateCompatibleDC(hdc);
	HBITMAP hbmp = LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_MP5RIGHT));
	SelectObject(hMemDc,hbmp);
	TransparentBlt(hdc,m_ptPosOnGround.x,m_ptPosOnGround.y,m_iWidth,m_iHeigth,
		hMemDc,0,0,m_iWidth,m_iHeigth,RGB(255,255,255));
	DeleteDC(hMemDc);
	DeleteObject(hbmp);
}

void CMP5::Draw(HINSTANCE hInstance, 
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
		iGunId = IDB_MP5LEFT;
		ptPos.x -= (m_iWidth/2-5);
		ptPos.y -= 10;
		break;
	case FACE_RIGHT:
		iGunId = IDB_MP5RIGHT;
		ptPos.x -= (m_iWidth/2+8);
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