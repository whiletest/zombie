#include "stdafx.h"
#include "resource.h"

CRain::CRain():CSceneObject(OBJECT_RAIN,2,3),
               m_iVertSpeed(0)
{
	m_iSoundId = _sound_rain;
}

CRain::~CRain()
{

}

void CRain::Draw(HINSTANCE hInstance,HDC hdc)
{
	//HPEN hPen = CreatePen(PS_SOLID,m_iWidth,RGB(0,0,0));
	//HPEN hOldPen = (HPEN)SelectObject(hdc,hPen);
	
	MoveToEx(hdc,m_ptPosition.x,m_ptPosition.y,NULL);
	LineTo(hdc,m_ptPosition.x,m_ptPosition.y+m_iHeigth);

	//SelectObject(hdc,hOldPen);
	//DeleteObject(hPen);
}

void CRain::Move()
{
	m_ptPosition.y += m_iVertSpeed;
	m_iVertSpeed += g_iGravity;
}
