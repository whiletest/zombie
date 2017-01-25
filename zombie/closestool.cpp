#include "stdafx.h"
#include "resource.h"

CClosestool::CClosestool():CSceneObject(OBJECT_CLOSESTOOL,30,39),
						   m_bDiskFinded(false)
{

}

CClosestool::~CClosestool()
{

}

void CClosestool::Draw(HINSTANCE hInstance,HDC hdc)
{
	HDC hMemDc = CreateCompatibleDC(hdc);
	HBITMAP hbmpTree = LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_CLOSESTOOL));
	SelectObject(hMemDc,hbmpTree);
	BitBlt(hdc,m_ptPosition.x,m_ptPosition.y,m_iWidth,m_iHeigth,
		hMemDc,0,0,SRCCOPY);
	DeleteDC(hMemDc);
	DeleteObject(hbmpTree);
}

int CClosestool::IsOnObject(POINT ptPos)
{
	if ( ptPos.y >= m_ptPosition.y 
		&& ptPos.y < m_ptPosition.y + m_iHeigth
		&& ptPos.x >= m_ptPosition.x
		&& ptPos.x < m_ptPosition.x + m_iWidth )
		return ON_BOTTOMFLOOR;
	return ON_NOTHING;
}

bool CClosestool::IsBulletOn(CBullet *pBullet)
{
	return false;
}

int CClosestool::OnObjectWhere(POINT &ptPos)
{
	if (ptPos.x < m_ptPosition.x + 13)
	{
		return (m_ptPosition.y + 13);
	}
	return m_ptPosition.y;
}

void CClosestool::FindDisk()
{
	if (m_pDisk)
	{
		POINT ptNewPos = {165,573};
		m_pDisk->SetPosition(ptNewPos);

		m_pDisk = NULL;
		m_bDiskFinded = true;
	}
}