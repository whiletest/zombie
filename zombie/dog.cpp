#include "stdafx.h"
#include "resource.h"

extern DWORD WINAPI DogBarkSoundThread(LPVOID lpParameter);
extern DWORD WINAPI DogShootenSoundThread(LPVOID lpParameter);

CDog::CDog():CDead(ID_DOG,47,50,8,20,200),
			m_iRightID(IDB_DOGRIGHT1),
			m_iLeftID(IDB_DOGLEFT1),
			m_iBarkTime(0)
{
	m_soundHuntId = _sound_dog;
	m_soundShootenId = _sound_dog;

	//设置攻击范围
	m_rcAttack.left = m_rcAttack.top = 0;
	m_rcAttack.right = m_iWidth;
	m_rcAttack.bottom = m_iHeigth + 5;
}

CDog::~CDog()
{

}

void CDog::SetHuntRect(const RECT &rcClient)
{
	m_rcHunt.right = rcClient.right;
	m_rcHunt.bottom = 3*m_iHeigth; 
}

void CDog::DrawDiedZombie(HINSTANCE hInstance,HDC hdc)
{
	static int ibmp;
	HDC hMemDc = CreateCompatibleDC(hdc);
	HBITMAP hbmp;
	switch (m_iDirection)
	{
	case FACE_LEFT:
		ibmp = IDB_DOGDEADL;
		break;
	case FACE_RIGHT:
		ibmp = IDB_DOGDEADR;
		break;
	}
	hbmp = LoadBitmap(hInstance,MAKEINTRESOURCE(ibmp));
	SelectObject(hMemDc,hbmp);
	TransparentBlt(hdc,m_ptCurPos.x,m_ptCurPos.y-41,50,41,
		hMemDc,0,0,50,41,RGB(255,255,255));
	DeleteDC(hMemDc);
	DeleteObject(hbmp);
}

void CDog::Draw(HINSTANCE hInstance,HDC hdc)
{
	if (m_bDied)
	{
		DrawDiedZombie(hInstance,hdc);
		return;
	}

	int bmpID;
	switch (m_iDirection)
	{
	case FACE_LEFT:
		++m_iLeftID;
		if (m_iLeftID == IDB_DOGLEFT7 + 1)
			m_iLeftID = IDB_DOGLEFT1;
		bmpID = m_iLeftID;
		break;
	case FACE_RIGHT:
		++m_iRightID;
		if (m_iRightID == IDB_DOGRIGHT7 + 1)
			m_iRightID = IDB_DOGRIGHT1;
		bmpID = m_iRightID;
		break;
	}

	HBITMAP hbmpZombie = LoadBitmap(hInstance,MAKEINTRESOURCE(bmpID));
	HDC hMemdc = CreateCompatibleDC(hdc);
	SelectObject(hMemdc,hbmpZombie);
	TransparentBlt(hdc,m_ptCurPos.x-m_iWidth/2,m_ptCurPos.y-m_iHeigth,
		m_iWidth,m_iHeigth,hMemdc,0,0,
		m_iWidth,m_iHeigth,RGB(255,255,255));
	DeleteDC(hMemdc);
	DeleteObject(hbmpZombie);

	if (m_bTied)
	{
		MoveToEx(hdc,m_ptOrgPos.x,m_ptOrgPos.y,NULL);
		LineTo(hdc,m_ptCurPos.x,m_ptCurPos.y);
	}

	//被击中时出血
	if (m_bBulletHitOn)
		BloodOut(hInstance,hdc);
}

bool CDog::Move(CPlayer &player,const RECT &rc)
{
	if (m_bDied)
		return false;

	if (!m_iBarkTime)
		PlayDeadHuntSound();

	m_iBarkTime = (m_iBarkTime+1)%250;

	POINT ptPos = player.GetCurPos();
	//在攻击区域
	if ( IsInAttackRect(ptPos) )
	{
		player.LoseBlood(m_iHurt);
		player.SetBloodOutFlag(true);
		return false;
	}

	//在追捕区域
	if ( IsInHuntRect(ptPos) )
	{
		ChangeDirection(ptPos.x);

		switch (m_iDirection)
		{
		case FACE_LEFT:
			if (   m_bTied 
				&& m_ptOrgPos.x - m_ptCurPos.x > 350 )
				return false;

			m_ptCurPos.x -= m_iSpeed;
			break;
		case FACE_RIGHT:
			if (   m_bTied 
				&& m_ptCurPos.x - m_ptOrgPos.x > 350 )
				return false;

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

void CDog::SetTieFlag(bool bTied)
{
	m_bTied = bTied;
	m_ptOrgPos = m_ptCurPos;
}

bool CDog::LoseBlood(int iHurt)
{
	PlayDeadShootenSound();

	m_iBlood -= iHurt;
	if (m_iBlood <= 0)
	{
		m_iBlood = 0;
		m_bDied = true;
		return false;
	}
	return true;
}