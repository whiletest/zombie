#include "stdafx.h"
#include "resource.h"

extern void RotateBitmap(HDC,int,int,double,double,HDC,POINT*);

CArrow::CArrow():CBullet(ID_BOW,20,7,12,300,10)
{

}

CArrow::~CArrow()
{

}

void CArrow::Draw(HINSTANCE hInstance,HDC hdc)
{
	HDC hMemDc = CreateCompatibleDC(hdc);
	HBITMAP hbmpBullet = LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_ARROW));
	SelectObject(hMemDc,hbmpBullet);
	POINT ptLogPos = m_ptCurPos;
	DPtoLP(hdc,&ptLogPos,1);
	RotateBitmap(hMemDc,m_iWidth,m_iHeigth,m_dSinA,m_dCosA,hdc,&ptLogPos);
	DeleteDC(hMemDc);
	DeleteObject(hbmpBullet);
}

