#include "stdafx.h"
#include "resource.h"
#include <cmath>

extern void RotateBitmap(HDC,int,int,double,double,HDC,POINT*);

CSpider_s::CSpider_s():CDead(ID_SPIDER_S,15,13,8,5,20),
					   m_sinA(1.0f),
					   m_cosA(0.0f)
{
	m_soundHuntId = _sound_smallZombie;
	m_soundShootenId = _sound_smallZombie;

	//存活时设置为向上移动状态，避免检测是否在物体上
	m_iVertState = MOVE_UP;

	//设置攻击范围
	m_rcAttack.left = m_rcAttack.top = 0;
	m_rcAttack.right = (long)(2.0f*m_iWidth);
	m_rcAttack.bottom = (long)(2.0f*m_iHeigth);
}

CSpider_s::~CSpider_s()
{

}

void CSpider_s::SetHuntRect(const RECT &rcClient)
{
	m_rcHunt.right = rcClient.right;
	m_rcHunt.bottom = rcClient.bottom; 
}

void CSpider_s::DrawDiedZombie(HINSTANCE hInstance,HDC hdc)
{
	HDC hMemDc = CreateCompatibleDC(hdc);
	HBITMAP hbmp = LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_SPIDER_SD));
	SelectObject(hMemDc,hbmp);
	TransparentBlt(hdc,m_ptCurPos.x,m_ptCurPos.y-m_iHeigth,m_iWidth,m_iHeigth,
		hMemDc,0,0,m_iWidth,m_iHeigth,RGB(255,255,255));
	DeleteDC(hMemDc);
	DeleteObject(hbmp);
}

void CSpider_s::Draw(HINSTANCE hInstance,HDC hdc)
{
	if (m_bDied)
	{
		DrawDiedZombie(hInstance,hdc);
		return;
	}

	int ibmpZombieID;
	m_iStepRate = (m_iStepRate+1)%4;
	if (m_iStepRate < 2)
		ibmpZombieID = IDB_SPIDER_S1;
	else
		ibmpZombieID = IDB_SPIDER_S2;
		
	HBITMAP hbmpZombie = LoadBitmap(hInstance,MAKEINTRESOURCE(ibmpZombieID));
	HDC hMemdc = CreateCompatibleDC(hdc);
	SelectObject(hMemdc,hbmpZombie);

	//spider的位置为其图片的下边缘正中
	POINT pos = {m_ptCurPos.x-m_iWidth/2,m_ptCurPos.y-m_iHeigth};
	RotateBitmap(hMemdc,m_iWidth,m_iHeigth,-m_sinA,m_cosA,hdc,&pos);

	DeleteDC(hMemdc);
	DeleteObject(hbmpZombie);

	//被击中时出血
	if (m_bBulletHitOn)
		BloodOut(hInstance,hdc);
}

bool CSpider_s::Move(CPlayer &player,const RECT &rc)
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
	//在蜘蛛可移动区域
	else if ( IsInMoveAbleRect(ptPos)  && !m_bDied)
	{
		getDirection(ptPos);
		//移动
		Action();
	}

	//死掉时下落
	if (m_bDied)
	{
		switch (m_iVertState)
		{
		case MOVE_DOWN:
			m_iVertSpeed += CDead::m_iGravity;
			m_ptCurPos.y += m_iVertSpeed;
			return false;
		case MOVE_VERTSTATIC:
			if (m_iVertSpeed != 0)
				m_iVertSpeed = 0;
			return false;
		}
	}

	return true;
}

bool CSpider_s::LoseBlood(int iHurt)
{
	PlayDeadShootenSound();
	bool bLoseBlood = CDead::LoseBlood(iHurt);
	if (m_bDied)
		m_iVertState = MOVE_DOWN;
	return bLoseBlood;
}

void CSpider_s::getDirection(const POINT &pos)
{
	float vec_x = pos.x - m_ptCurPos.x;//x分向量
	float vec_y = pos.y - m_ptCurPos.y;//y分向量

	float vec_len = sqrtf(vec_x*vec_x + vec_y*vec_y);//向量的模

	//求出向量与y轴的正余玄值
	m_sinA = vec_x/vec_len;
	m_cosA = vec_y/vec_len;
}

void CSpider_s::Action()
{
	m_ptCurPos.x += m_iSpeed * m_sinA;
	m_ptCurPos.y += m_iSpeed * m_cosA;
}
