#include "stdafx.h"

CGround::CGround():CSceneObject(OBJECT_GROUND,0,30)
{

}

CGround::~CGround()
{

}

void CGround::Draw(HINSTANCE hInstance,HDC hdc)
{
	MoveToEx(hdc,m_ptPosition.x,m_ptPosition.y,NULL);
	LineTo(hdc,m_ptPosition.x+m_iWidth,m_ptPosition.y);

	HPEN hPen = CreatePen(PS_SOLID,2,RGB(0,0,0));
	HPEN hOldPen = (HPEN)SelectObject(hdc,hPen);
	for (int i = m_ptPosition.x;
		i < m_ptPosition.x+m_iWidth;i += 5)
	{
		MoveToEx(hdc,i,m_ptPosition.y,NULL);
		LineTo(hdc,i-5,m_ptPosition.y+5);
	}
	SelectObject(hdc,hOldPen);
	DeleteObject(hPen);
}

int CGround::IsOnObject(POINT ptPos)
{
	if (   ptPos.y >= m_ptPosition.y-5
		&& ptPos.y < m_ptPosition.y + m_iHeigth
		&& ptPos.x >= m_ptPosition.x
		&& ptPos.x < m_ptPosition.x + m_iWidth)
		return ON_BOTTOMFLOOR;
	return ON_NOTHING;
}

bool CGround::IsBulletOn(CBullet *pBullet)
{
	POINT ptPos = pBullet->GetPosition();
	if ( ptPos.y > m_ptPosition.y
		&& ptPos.y < m_ptPosition.y + m_iHeigth)
		return true;
	return false;
}