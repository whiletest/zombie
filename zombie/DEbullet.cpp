#include "stdafx.h"
#include "resource.h"

extern void RotateBitmap(HDC,int,int,double,double,HDC,POINT*);

CDEBullet::CDEBullet():CBullet(ID_DESERT_EAGLE,13,7,15,300,46)
{

}

CDEBullet::~CDEBullet()
{

}

void CDEBullet::Draw(HINSTANCE hInstance,HDC hdc)
{
	HDC hMemDc = CreateCompatibleDC(hdc);
	HBITMAP hbmpBullet = LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_DEBULLET));
	SelectObject(hMemDc,hbmpBullet);
	POINT ptLogPos = m_ptCurPos;
	DPtoLP(hdc,&ptLogPos,1);
	RotateBitmap(hMemDc,m_iWidth,m_iHeigth,m_dSinA,m_dCosA,hdc,&ptLogPos);
	DeleteDC(hMemDc);
	DeleteObject(hbmpBullet);
}