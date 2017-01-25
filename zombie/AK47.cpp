#include "stdafx.h"
#include "resource.h"

extern void RotateBitmap(HDC,int,int,double,double,HDC,POINT*);


CAK47::CAK47():CWeapon(ID_AK47,KIND_LONGGUN,50,22,30,90,116)
{
	m_iHurt = 32;
	lstrcpy(m_szWeaponName,TEXT("AK47"));
}

CAK47::~CAK47()
{

}

void CAK47::Fire(const POINT &ptPos, double sinA, double cosA)
{
	if (m_iBulletNum)
	{
		CBullet *pBullet = new CDEBullet;
		pBullet->SetBulletPos(ptPos);
		pBullet->SetAngleValue(sinA,cosA);
		pBullet->SetHurt(32);
		m_vecBullet.push_back(pBullet);
		--m_iBulletNum;

		PlayFireSound();
	}
	else
		PlayNoBulletFireSound();
}


void CAK47::DrawOnGround(HINSTANCE hInstance, HDC hdc)
{
	HDC hMemDc = CreateCompatibleDC(hdc);
	HBITMAP hbmp = LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_AK47RIGHT));
	SelectObject(hMemDc,hbmp);
	TransparentBlt(hdc,m_ptPosOnGround.x,m_ptPosOnGround.y,m_iWidth,m_iHeigth,
		hMemDc,0,0,m_iWidth,m_iHeigth,RGB(255,255,255));
	DeleteDC(hMemDc);
	DeleteObject(hbmp);
}

void CAK47::Draw(HINSTANCE hInstance, 
				HDC hdc,
				int iFace, 
				POINT ptPos,
				double sinA, 
				double cosA )
{
	HDC hMemDc = CreateCompatibleDC(hdc);
	int iGunId;
	switch (iFace)
	{
	case FACE_LEFT:
		iGunId = IDB_AK47LEFT;
		ptPos.x -= m_iWidth/2;
		ptPos.y -= 10;
		break;
	case FACE_RIGHT:
		iGunId = IDB_AK47RIGHT;
		ptPos.x -= m_iWidth/2;
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