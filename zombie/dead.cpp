#include "stdafx.h"
#include "resource.h"

DWORD WINAPI DeadHuntSoundThread(LPVOID lpParameter);
DWORD WINAPI DeadShootenSoundThread(LPVOID lpParameter);

CDead::CDead( int iId,
			  int iWidth, 
			  int iHeigth,
			  int iSpeed,
			  int iHurt,
			  int iBlood
			 ):m_iId(iId),
			   m_iWidth(iWidth),
			   m_iHeigth(iHeigth),
			   m_iSpeed(iSpeed),
			   m_iHurt(iHurt),
			   m_iBlood(iBlood),
			   m_bBulletHitOn(false),
			   m_bDied(false),
			   m_iVertSpeed(0),
			   m_iStepRate(0),
			   m_soundHuntId(_sound_none),
			   m_soundShootenId(_sound_none),
			   m_iVertState(MOVE_VERTSTATIC),
			   m_iDirection(FACE_LEFT),
			   m_bSelfAction(false)
{

}

int CDead::m_iGravity = 1; //重力加速度

CDead::~CDead()
{

}

bool CDead::IsDied() const
{
	return m_bDied;
}

POINT CDead::GetCurPos() const
{
	return m_ptCurPos;
}

void CDead::SetCurPos(POINT ptPos)
{
	m_ptCurPos = ptPos;
}

int CDead::GetVertState() const
{
	return m_iVertState;
}

void CDead::SetVertPos(int iy)
{
	m_ptCurPos.y = iy;
}

void CDead::SetHoriPos(int ix)
{
	m_ptCurPos.x = ix;
}

bool CDead::ChangeVertState(int iState)
{
	if (m_iVertState != iState)
	{
		m_iVertState = iState;
		return true;
	}
	return false;
}

bool CDead::ChangeDirection(int ix)
{
	if (m_ptCurPos.x + m_iWidth/2 > ix)
	{
		if (m_iDirection != FACE_LEFT)
		{
			m_iDirection = FACE_LEFT;
			return true;
		}
	}
	else
	{
		if (m_iDirection != FACE_RIGHT)
		{
			m_iDirection = FACE_RIGHT;
			return true;
		}
	}
	return false;
}

BOOL CDead::IsInHuntRect(POINT ptpos)
{
	RECT rcHunt;
	rcHunt.left = m_ptCurPos.x - m_rcHunt.right;
	rcHunt.top = m_ptCurPos.y - m_iHeigth/2 - m_rcHunt.bottom;
	rcHunt.right = m_ptCurPos.x + m_rcHunt.right;
	rcHunt.bottom = m_ptCurPos.y - m_iHeigth/2 + m_rcHunt.bottom;
	return PtInRect(&rcHunt,ptpos);
}

BOOL CDead::IsInAttackRect(POINT ptPos)
{
	RECT rcRect;
	rcRect.left = m_ptCurPos.x - m_rcAttack.right;
	rcRect.top = m_ptCurPos.y - m_iHeigth/2 - m_rcAttack.bottom;
	rcRect.right = m_ptCurPos.x + m_rcAttack.right;
	rcRect.bottom = m_ptCurPos.y - m_iHeigth/2 + m_rcAttack.bottom;
	return PtInRect(&rcRect,ptPos);
}

int CDead::GetWidth() const
{
	return m_iWidth;
}

int CDead::GetHeigth() const
{
	return m_iHeigth;
}

bool CDead::LoseBlood(int iHurt)
{
	m_iBlood -= iHurt;
	if (m_iBlood <= 0)
	{
		m_iBlood = 0;
		m_bDied = true;

		return false;
	}
	return true;
}

bool CDead::IsInMapRect(const RECT &rc)
{
	if (   m_ptCurPos.x <= rc.left
		|| m_ptCurPos.x >= rc.right)
	{
		if (m_iDirection == FACE_LEFT)
			m_iDirection = FACE_RIGHT;
		else
			m_iDirection = FACE_LEFT;

		return false;
	}
	return true;
}

void CDead::HitBack(CBullet *pBullet)
{
	int iHurt = pBullet->GetHurt();
	switch (m_iDirection)
	{
	case FACE_LEFT:
		m_ptCurPos.x += iHurt;
		break;
	case FACE_RIGHT:
		m_ptCurPos.x -= iHurt;
		break;
	default:
		break;
	}
}

void CDead::SetAttackRect(const RECT &rcAttack)
{
	m_rcAttack = rcAttack;
}

//bool CDead::Move(CPlayer &player)
//{
//	if (m_bDied)
//		return false;
//
//	POINT ptPos = player.GetCurPos();
//	//在攻击区域
//	if ( IsInAttackRect(ptPos) )
//	{
//		player.LoseBlood(m_iHurt);
//		player.SetBloodOutFlag(true);
//	}
//	//在追捕区域
//	else if ( IsInHuntRect(ptPos) )
//	{
//		ChangeDirection(ptPos.x);
//		switch (m_iDirection)
//		{
//		case FACE_LEFT:
//			m_ptCurPos.x -= m_iSpeed;
//			break;
//		case FACE_RIGHT:
//			m_ptCurPos.x += m_iSpeed;
//			break;
//		default:
//			break;
//		}
//
//		switch (m_iVertState)
//		{
//		case MOVE_DOWN:
//			m_iVertSpeed += CDead::m_iGravity;
//			m_ptCurPos.y += m_iVertSpeed;
//			break;
//		case MOVE_UP:
//			m_iVertSpeed -= CDead::m_iGravity;
//			if (m_iVertSpeed <= 0)
//			{
//				m_iVertSpeed = 0;
//				m_iVertState = MOVE_DOWN;
//				break;
//			}
//			m_ptCurPos.y -= m_iVertSpeed;
//			break;
//		case MOVE_VERTSTATIC:
//			if (m_iVertSpeed != 0)
//				m_iVertSpeed = 0;
//			break;
//		}
//	}
//	return true;
//}

bool CDead::IsBulletOn(CBullet *pBullet)
{
	if (m_bDied)
		return false;

	POINT ptPos = pBullet->GetPosition();
	RECT rcOn = {m_ptCurPos.x-m_iWidth/2,m_ptCurPos.y-m_iHeigth,
		m_ptCurPos.x+m_iWidth/2,m_ptCurPos.y};
	if (PtInRect(&rcOn,ptPos))
	{
		m_bBulletHitOn = true;
		m_ptBulletHitPos = ptPos;
		if ( LoseBlood(pBullet->GetHurt()) )
			HitBack(pBullet);
		return true;
	}
	return false;
}

void CDead::BloodOut(HINSTANCE hInstance, HDC hdc)
{
	int iBloodId;
	switch (m_iDirection)
	{
	case FACE_LEFT:
		iBloodId = IDB_BLOODOUT;
		break;
	case FACE_RIGHT:
		iBloodId = IDB_BLOODOUTR;
		break;
	default:
		break;
	}
	HBITMAP hbmpBlood = LoadBitmap(hInstance,MAKEINTRESOURCE(iBloodId));
	HDC hMemDc = CreateCompatibleDC(hdc);
	SelectObject(hMemDc,hbmpBlood);
	BitBlt(hdc,m_ptBulletHitPos.x,m_ptBulletHitPos.y-5,20,18,
		hMemDc,0,0,SRCCOPY);
	m_bBulletHitOn = false;
	DeleteDC(hMemDc);
	DeleteObject(hbmpBlood);
}

void CDead::PlayDeadHuntSound()
{
	HANDLE hSoundThread;
	hSoundThread = CreateThread(NULL,0,
		DeadHuntSoundThread,
		(LPVOID)&m_soundHuntId,0,NULL);
	CloseHandle(hSoundThread);
}

void CDead::PlayDeadShootenSound()
{
	HANDLE hSoundThread;
	hSoundThread = CreateThread(NULL,0,
		DeadShootenSoundThread,
		(LPVOID)&m_soundShootenId,0,NULL);
	CloseHandle(hSoundThread);
}

THING CDead::SelfAction()
{
	static THING thing = {tt_none,0};

	return thing;
}