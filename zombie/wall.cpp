#include "stdafx.h"

CWall::CWall():CSceneObject(OBJECT_WALL,70,0),m_iType(TYPE_VERT)
{

}

CWall::~CWall()
{

}

void CWall::Draw(HINSTANCE hInstance,HDC hdc)
{
	HPEN hPen = CreatePen(PS_SOLID,2,RGB(0,0,0));
	HPEN hOldPen = (HPEN)SelectObject(hdc,hPen);
    if (m_iType == TYPE_VERT)
    {
		MoveToEx(hdc,m_ptPosition.x,m_ptPosition.y,NULL);
		LineTo(hdc,m_ptPosition.x,m_ptPosition.y-m_iHeigth);
    }
	else
	{
		MoveToEx(hdc,m_ptPosition.x,m_ptPosition.y,NULL);
		LineTo(hdc,m_ptPosition.x + m_iHeigth,m_ptPosition.y);
	}

	SelectObject(hdc,hOldPen);
	DeleteObject(hPen);
}

int CWall::IsOnObject(POINT ptPos)
{
	if (m_iType == TYPE_VERT)
	{
		if (ptPos.x > m_ptPosition.x
			&& ptPos.x < m_ptPosition.x + m_iWidth)
			return ON_WALL;
	}

	return ON_NOTHING;
}

bool CWall::IsBulletOn(CBullet *pBullet)
{
	POINT ptPos = pBullet->GetPosition();
	if (m_iType == TYPE_VERT)
	{
		if ( ptPos.x > m_ptPosition.x
		&& ptPos.x < m_ptPosition.x + m_iWidth )
		return true;
	}
	else
	{
		if (ptPos.y < m_ptPosition.y
			&& ptPos.y > m_ptPosition.y - m_iWidth)
			return true;
	}
	return false;
}