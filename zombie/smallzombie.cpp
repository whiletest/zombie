#include "stdafx.h"
#include "resource.h"


CSmallZombie::CSmallZombie():CDead(ID_SMALLZOMBIE,31,54,2,10,200)
{
	m_soundHuntId = _sound_smallZombie;
	m_soundShootenId = _sound_smallZombie;

	//设置攻击范围
	m_rcAttack.left = m_rcAttack.top = 0;
	m_rcAttack.right = m_iWidth;
	m_rcAttack.bottom = m_iHeigth + 5;
}

CSmallZombie::~CSmallZombie()
{

}

void CSmallZombie::SetHuntRect(const RECT &rcClient)
{
	m_rcHunt.right = rcClient.right;
	m_rcHunt.bottom = 3*m_iHeigth; 
}

void CSmallZombie::DrawDiedZombie(HINSTANCE hInstance,HDC hdc)
{
	static int ibmp;
	HDC hMemDc = CreateCompatibleDC(hdc);
	HBITMAP hbmp;
	switch (m_iDirection)
	{
	case FACE_LEFT:
		ibmp = IDB_SMALLZOMBIEDIEL;
		break;
	case FACE_RIGHT:
		ibmp = IDB_SMALLZOMBIEDIER;
		break;
	}
	hbmp = LoadBitmap(hInstance,MAKEINTRESOURCE(ibmp));
	SelectObject(hMemDc,hbmp);
	TransparentBlt(hdc,m_ptCurPos.x,m_ptCurPos.y-m_iWidth,m_iHeigth,m_iWidth,
		hMemDc,0,0,m_iHeigth,m_iWidth,RGB(255,255,255));
	DeleteDC(hMemDc);
	DeleteObject(hbmp);
}

void CSmallZombie::Draw(HINSTANCE hInstance,HDC hdc)
{
	if (m_bDied)
	{
		DrawDiedZombie(hInstance,hdc);
		return;
	}

	static int ibmpZombieID = IDB_SMALLZOMBIEL1;
	switch (m_iDirection)
	{
	case FACE_RIGHT:
		m_iStepRate = (m_iStepRate+1)%6;
		if (m_iStepRate < 3)
			ibmpZombieID = IDB_SMALLZOMBIER1;
		else
			ibmpZombieID = IDB_SMALLZOMBIER2;
		break;
	case FACE_LEFT:
		m_iStepRate = (m_iStepRate+1)%6;
		if (m_iStepRate < 3)
			ibmpZombieID = IDB_SMALLZOMBIEL1;
		else
			ibmpZombieID = IDB_SMALLZOMBIEL2;
		break;
	}

	HBITMAP hbmpZombie = LoadBitmap(hInstance,MAKEINTRESOURCE(ibmpZombieID));
	HDC hMemdc = CreateCompatibleDC(hdc);
	SelectObject(hMemdc,hbmpZombie);
	TransparentBlt(hdc,m_ptCurPos.x-m_iWidth/2,m_ptCurPos.y-m_iHeigth,
		m_iWidth,m_iHeigth,hMemdc,0,0,
		m_iWidth,m_iHeigth,RGB(255,255,255));
	DeleteDC(hMemdc);
	DeleteObject(hbmpZombie);

	//被击中时出血
	if (m_bBulletHitOn)
		BloodOut(hInstance,hdc);
}

bool CSmallZombie::Move(CPlayer &player,const RECT &rc)
{
	if (m_bDied)
		return false;

	POINT ptPos = player.GetCurPos();
	//在攻击区域
	if ( IsInAttackRect(ptPos) )
	{
		player.LoseBlood(m_iHurt);
		player.SetBloodOutFlag(true);
	}
	//在追捕区域
	else if ( IsInHuntRect(ptPos) )
	{
		ChangeDirection(ptPos.x);

		switch (m_iDirection)
		{
		case FACE_LEFT:
			m_ptCurPos.x -= m_iSpeed;
			break;
		case FACE_RIGHT:
			m_ptCurPos.x += m_iSpeed;
			break;
		default:
			break;
		}

		switch (m_iVertState)
		{
		case MOVE_DOWN:
			m_iVertSpeed += CDead::m_iGravity;
			m_ptCurPos.y += m_iVertSpeed;
			break;
		case MOVE_UP:
			m_iVertSpeed -= CDead::m_iGravity;
			if (m_iVertSpeed <= 0)
			{
				m_iVertSpeed = 0;
				m_iVertState = MOVE_DOWN;
				break;
			}
			m_ptCurPos.y -= m_iVertSpeed;
			break;
		case MOVE_VERTSTATIC:
			if (m_iVertSpeed != 0)
				m_iVertSpeed = 0;
			break;
		}
	}
	return true;
}

bool CSmallZombie::LoseBlood(int iHurt)
{
	PlayDeadShootenSound();
	return CDead::LoseBlood(iHurt);
}