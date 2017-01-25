#include "stdafx.h"
#include "resource.h"

extern void RotateBitmap(HDC,int,int,double,double,HDC,POINT*);

CBow::CBow():CWeapon(ID_BOW,KIND_HANDGUN,
					 25,50,10,0,500)
{
	m_iHurt = 10;
	lstrcpy(m_szWeaponName,TEXT("¹­¼ý"));
}

CBow::~CBow()
{

}

void CBow::Fire(const POINT &ptPos,double sinA,double cosA)
{
	if (m_iBulletNum)
	{
		CBullet *pBullet = new CArrow;
		pBullet->SetBulletPos(ptPos);
		pBullet->SetAngleValue(sinA,cosA);
		m_vecBullet.push_back(pBullet);
		--m_iBulletNum;

		//	PlayFireSound();
	}
	else
		PlayNoBulletFireSound();
}

void CBow::DrawOnGround(HINSTANCE hInstance, HDC hdc)
{
	HDC hMemDc = CreateCompatibleDC(hdc);
	HBITMAP hbmp = LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_BOW));
	SelectObject(hMemDc,hbmp);
	TransparentBlt(hdc,m_ptPosOnGround.x,m_ptPosOnGround.y,m_iWidth,m_iHeigth,
		hMemDc,0,0,m_iWidth,m_iHeigth,RGB(255,255,255));
	DeleteDC(hMemDc);
	DeleteObject(hbmp);
}

void CBow::Draw(HINSTANCE hInstance, 
						HDC hdc, 
						int iFace, 
						POINT ptPos,
						double sinA,
						double cosA
						)
{
	HDC hMemDc = CreateCompatibleDC(hdc);
	int iGunId = IDB_BOW;
	switch (iFace)
	{
	case FACE_LEFT:
		ptPos.x -= (m_iWidth-5);
		ptPos.y -= 19;
		break;
	case FACE_RIGHT:
		ptPos.x -= 18;
		ptPos.y -= 21;
		if (sinA < -0.5f)
		{
			ptPos.x -= 5;
			ptPos.y -= 5;
		}
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