#include "stdafx.h"
#include "resource.h"
#include "time.h"

bool CBird::m_bHearFire = false;

CBird::CBird():CDead(ID_BIRD,50,50,10,10,100),
			   m_iChangeRateCount(0),
			   m_iChangeTimesCount(0),
			   m_iVertDirection(0)
{
	m_soundHuntId = _sound_bird;

	//设置攻击范围
	m_rcAttack.left = m_rcAttack.top = 0;
	m_rcAttack.right = m_iWidth;
	m_rcAttack.bottom = m_iHeigth + 5;
	
	m_rcHunt.left = m_rcHunt.right = 0;
	m_rcHunt.top = m_rcHunt.bottom = 0;

	m_rcHear.left = m_rcHear.right = 0;
	m_rcHear.top = m_rcHear.bottom = 0;

	m_iChangeTimes = rand()%10 + 5;

	if (CBird::m_bHearFire)
		CBird::m_bHearFire = false;
}


CBird::~CBird()
{

}

void CBird::SetHuntRect(const RECT &rcClient)
{
	m_rcHunt.right = rcClient.right;
	m_rcHunt.bottom =  550; 
}

void CBird::DrawDiedZombie(HINSTANCE hInstance,HDC hdc)
{
	static int ibmp;
	HDC hMemDc = CreateCompatibleDC(hdc);
	HBITMAP hbmp;
	switch (m_iDirection)
	{
	case FACE_LEFT:
		ibmp = IDB_DEADBIRD;
		break;
	case FACE_RIGHT:
		ibmp = IDB_DEADBIRDR;
		break;
	}
	hbmp = LoadBitmap(hInstance,MAKEINTRESOURCE(ibmp));
	SelectObject(hMemDc,hbmp);
	TransparentBlt(hdc,m_ptCurPos.x,m_ptCurPos.y-m_iWidth,m_iHeigth,m_iWidth,
		hMemDc,0,0,m_iHeigth,m_iWidth,RGB(255,255,255));
	DeleteDC(hMemDc);
	DeleteObject(hbmp);
}

bool CBird::IsHearFire(CBullet *pBullet)
{
	if (CBird::m_bHearFire)
	{
		if (m_rcHunt.right == 0)
		{
			//设置追踪区域
			m_rcHunt.right = 1000;
			m_rcHunt.bottom = 550; 

			PlayDeadHuntSound();
		}
		return true;
	}
	POINT ptPos = pBullet->GetPosition();
	if (PtInRect(&m_rcHear,ptPos))
	{
		CBird::m_bHearFire = true;

		//设置追踪区域
		//m_rcHunt.right = 1000;
		//m_rcHunt.bottom = 550; 
	}
	return CBird::m_bHearFire;
}

void CBird::SetHearRect(RECT &rcHear)
{
	m_rcHear.left = m_ptCurPos.x - rcHear.right;
	m_rcHear.right = m_ptCurPos.x + rcHear.right;
	m_rcHear.top = m_ptCurPos.y - rcHear.bottom;
	m_rcHear.bottom = m_ptCurPos.y + rcHear.bottom;
}

void CBird::Draw(HINSTANCE hInstance,HDC hdc)
{
	if (m_bDied)
	{
		DrawDiedZombie(hInstance,hdc);
		return;
	}

	static int ibmpZombieID;

	if (!CBird::m_bHearFire)
		ibmpZombieID = IDB_BIRDONTREE;
	else
	{
		switch (m_iDirection)
		{
		case FACE_RIGHT:
			m_iStepRate = (m_iStepRate+1)%6;
			if (m_iStepRate < 3)
				ibmpZombieID = IDB_BIRDFLYR;
			else
				ibmpZombieID = IDB_BIRDFLYR1;
			break;
		case FACE_LEFT:
			m_iStepRate = (m_iStepRate+1)%6;
			if (m_iStepRate < 3)
				ibmpZombieID = IDB_BIRDFLYL;
			else
				ibmpZombieID = IDB_BIRDFLYL1;
			break;
		}
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
	{
		if (!CBird::m_bHearFire)
		{
			CBird::m_bHearFire = true;

			//设置追踪区域
			m_rcHunt.right = 1000;
			m_rcHunt.bottom = 550; 
		}
		BloodOut(hInstance,hdc);
	}
}

bool CBird::Move(CPlayer &player,const RECT &rc)
{
	POINT ptPos = player.GetCurPos();
	//在攻击区域
	if ( IsInAttackRect(ptPos)
		&& !m_bDied )
	{
		player.LoseBlood(m_iHurt);
		player.SetBloodOutFlag(true);
	}
	//在追捕区域
	else if ( IsInHuntRect(ptPos) )
	{
		if (!m_bDied)
		{
			if ( m_iChangeRateCount == 0
				&& m_iChangeTimesCount < m_iChangeTimes )
			{
				m_iDirection = rand()%2 + 1;
	
				m_iVertDirection = rand()%3;
				
				++m_iChangeTimesCount;
			}

			if ( m_iChangeTimesCount < m_iChangeTimes )
				m_iChangeRateCount = (m_iChangeRateCount+1)%10;
			else 
			{
				m_iVertDirection = 0;
				ChangeDirection(ptPos.x);
			}

			switch (m_iVertDirection)
			{
			case 0:
				if (m_ptCurPos.y < ptPos.y - 30)
					m_ptCurPos.y += 8;
				break;
			case 1:
				if (m_ptCurPos.y > ptPos.y-400)
					m_ptCurPos.y -= 8;
				break;
			case 2:
				break;
			}

			switch (m_iDirection)
			{
			case FACE_LEFT:
				if (m_ptCurPos.x > 0)
					m_ptCurPos.x -= m_iSpeed;
				break;
			case FACE_RIGHT:
				m_ptCurPos.x += m_iSpeed;
				break;
			default:
				break;
			}
		}
		else
		{
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
	}
	return false;
}