#include "stdafx.h"
#include "resource.h"
#include <cmath>

CHunter::CHunter():CDead(ID_HUNTER,50,25,8,20,500),
				   m_jumpTimes(0),
				   m_cJump(0)
{
	m_soundHuntId = _sound_smallZombie;
	m_soundShootenId = _sound_smallZombie;

	//设置攻击范围
	m_rcAttack.left = m_rcAttack.top = 0;
	m_rcAttack.right = m_iWidth;
	m_rcAttack.bottom = m_iHeigth + 5;
}

CHunter::~CHunter()
{

}

const int CHunter::m_maxJumpSpeed = 25;

//检测和给定点的距离,返回攻击的起跳初速度
int CHunter::CheckDistance(const POINT &pos)
{
	float t = abs(float(m_ptCurPos.x-pos.x))/(float)m_iSpeed;
	return (int)(g_iGravity*t*0.5f);
}

void CHunter::SetHuntRect(const RECT &rcClient)
{
	m_rcHunt.right = rcClient.right;
	m_rcHunt.bottom = rcClient.bottom; 
}

void CHunter::DrawDiedZombie(HINSTANCE hInstance,HDC hdc)
{
	int ibmp;
	HDC hMemDc = CreateCompatibleDC(hdc);
	HBITMAP hbmp;
	switch (m_iDirection)
	{
	case FACE_LEFT:
		ibmp = IDB_HUNTERDIEDR;
		break;
	case FACE_RIGHT:
		ibmp = IDB_HUNTERDIEDR;
		break;
	}
	hbmp = LoadBitmap(hInstance,MAKEINTRESOURCE(ibmp));
	SelectObject(hMemDc,hbmp);
	TransparentBlt(hdc,m_ptCurPos.x,m_ptCurPos.y-m_iHeigth,m_iWidth,m_iHeigth,
		hMemDc,0,0,m_iWidth,m_iHeigth,RGB(255,255,255));
	DeleteDC(hMemDc);
	DeleteObject(hbmp);
}

void CHunter::Draw(HINSTANCE hInstance,HDC hdc)
{
	if (m_bDied)
	{
		DrawDiedZombie(hInstance,hdc);
		return;
	}

	int ibmpZombieID;
	switch (m_iDirection)
	{
	case FACE_LEFT:
		if (m_iVertState == MOVE_VERTSTATIC)
		{
			m_iStepRate = (m_iStepRate+1)%4;
			if (m_iStepRate < 2)
				ibmpZombieID = IDB_HUNTERCLIMBL1;
			else
				ibmpZombieID = IDB_HUNTERCLIMBL2;
		}
		else
			ibmpZombieID = IDB_HUNTERCLIMBL2;
		break;
	case FACE_RIGHT:
		if (m_iVertState == MOVE_VERTSTATIC)
		{
			m_iStepRate = (m_iStepRate+1)%4;
			if (m_iStepRate < 2)
				ibmpZombieID = IDB_HUNTERCLIMBR1;
			else
				ibmpZombieID = IDB_HUNTERCLIMBR2;
		}
		else
			ibmpZombieID = IDB_HUNTERCLIMBR2;
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

bool CHunter::Move(CPlayer &player,const RECT &rc)
{
	if (   m_bDied 
		&& m_iVertState == MOVE_VERTSTATIC)
		return false;

	POINT ptPos = player.GetCurPos();
	//在攻击区域
	if ( IsInAttackRect(ptPos) && !m_bDied)
	{
		player.LoseBlood(m_iHurt);
		player.SetBloodOutFlag(true);
	}
	//在追捕区域
	else if ( IsInHuntRect(ptPos) )
	{
		if (!m_bDied) //没死
		{
			Action(&ptPos);

			switch (m_iDirection)
			{
			case FACE_LEFT:
				m_ptCurPos.x -= m_iSpeed;
				if (m_ptCurPos.x < rc.left)
					m_iDirection = FACE_RIGHT;
				break;
			case FACE_RIGHT:
				m_ptCurPos.x += m_iSpeed;
				if (m_ptCurPos.x > rc.right)
					m_iDirection = FACE_LEFT;
				break;
			default:
				break;
			}
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

bool CHunter::LoseBlood(int iHurt)
{
	PlayDeadShootenSound();
	if (m_iBlood < 20)
	{
		if (m_iDirection == FACE_LEFT)
			m_iDirection = FACE_RIGHT;
		else
			m_iDirection = FACE_LEFT;
		Jump(m_maxJumpSpeed);
	}
	return CDead::LoseBlood(iHurt);
}

void CHunter::Jump(int speed)
{
	m_iVertSpeed = speed;
	m_iVertState = MOVE_UP;
}

void CHunter::Action(const POINT *pos)
{
	if (!m_cJump)
	{
		srand((unsigned int)time(0));
		m_jumpTimes = rand()%50 + 10;

		if (m_iVertState == MOVE_VERTSTATIC)
		{
			int vertSpeed = CheckDistance(*pos);
			if (vertSpeed < m_maxJumpSpeed)
				ChangeDirection(pos->x);
			else
			{
				vertSpeed = rand()%m_maxJumpSpeed;
				m_iDirection = vertSpeed%2 + 1;
			}

			Jump(vertSpeed);
		}
	}

	m_cJump = (m_cJump+1)%m_jumpTimes;
}