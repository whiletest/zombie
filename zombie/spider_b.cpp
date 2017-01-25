#include "stdafx.h"
#include "resource.h"
#include <cmath>

const int CSpider_b::m_maxJumpSpeed = 20;

CSpider_b::CSpider_b():CDead(ID_SPIDER_B,152,88,3,10,1000),
					   m_sinA(0.0f),
					   m_cosA(0.0f),
					   m_cs(cs_notOnWall),
					   m_curBuiding(-1),
					   m_cJump(0),
					   m_jumpTimes(0),
					   m_bmpId(IDB_SPIDER_B_GL),
					   m_speedOnAir(10),
					   m_bLoseReward(false)
{
	m_soundHuntId = _sound_smallZombie;
	m_soundShootenId = _sound_smallZombie;
	//有自定动作
	m_bSelfAction = true;

	//存活时设置为向上移动状态，避免检测是否在物体上
	m_iVertState = MOVE_UP;

	//设置攻击范围
	m_rcAttack.left = m_rcAttack.top = 0;
	m_rcAttack.right = (long)(m_iWidth * 0.8f);
	m_rcAttack.bottom = (long)(m_iHeigth * 0.8f);

	//设置追捕范围
	m_rcHunt.left = m_rcHunt.top = 0;
	m_rcHunt.right = (long)(6.5f * m_iWidth);
	m_rcHunt.bottom = (long)(6.5f * m_iHeigth);

	//设置第一次起跳时间间隔
	srand((unsigned int)time(0));
	m_jumpTimes = rand()%100 + 50;
}

CSpider_b::~CSpider_b()
{

}

void CSpider_b::SetHuntRect(const RECT &rcClient)
{
	m_rcHunt.right = rcClient.right;
	m_rcHunt.bottom = rcClient.bottom; 
}

void CSpider_b::DrawDiedZombie(HINSTANCE hInstance,HDC hdc)
{
	HDC hMemDc = CreateCompatibleDC(hdc);
	HBITMAP hbmp = LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_BIGSPIDERDEAD));
	SelectObject(hMemDc,hbmp);
	TransparentBlt(hdc,m_ptCurPos.x,m_ptCurPos.y-m_iHeigth,m_iWidth,m_iHeigth,
		hMemDc,0,0,m_iWidth,m_iHeigth,RGB(255,255,255));
	DeleteDC(hMemDc);
	DeleteObject(hbmp);
}

void CSpider_b::Draw(HINSTANCE hInstance,HDC hdc)
{
	if (m_bDied)
	{
		DrawDiedZombie(hInstance,hdc);
		return;
	}

	HBITMAP hbmpZombie = LoadBitmap(hInstance,MAKEINTRESOURCE(m_bmpId));
	HDC hMemdc = CreateCompatibleDC(hdc);
	SelectObject(hMemdc,hbmpZombie);

	//spider的位置为其图片的下边缘正中
	TransparentBlt(hdc,m_ptCurPos.x-m_iWidth/2,m_ptCurPos.y-m_iHeigth,m_iWidth,m_iHeigth,
		hMemdc,0,0,m_iWidth,m_iHeigth,RGB(255,255,255));

	DeleteDC(hMemdc);
	DeleteObject(hbmpZombie);

	//被击中时出血
	if (m_bBulletHitOn)
		BloodOut(hInstance,hdc);
}

bool CSpider_b::Move(CPlayer &player,const RECT &rc)
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
	//在蜘蛛追捕区域
	else if ( IsInHuntRect(ptPos)  && !m_bDied)
	{
		//动作
		Action(ptPos);

		if (m_cs == cs_onWall)
		{
			ChangeDirection(ptPos.x);
			getDirection(ptPos);

			m_ptCurPos.x += (long)(m_iSpeed * m_sinA);
			m_ptCurPos.y += (long)(m_iSpeed * m_cosA);
			if (IsOutofCurBuidingArea())
			{
				int speed = rand()%m_maxJumpSpeed + 15; //获得起跳速度
				Jump(speed);
				ClimbStateChange();
			}
		}
	}

	if (m_cs == cs_notOnWall)
	{
		switch (m_iVertState)
		{
		case MOVE_DOWN:
			m_iVertSpeed += CDead::m_iGravity;
			m_ptCurPos.y += m_iVertSpeed;

			if (m_iDirection == FACE_LEFT)
			{
				m_ptCurPos.x -= m_speedOnAir;
				m_bmpId = IDB_SPIDER_B_GL;
			}
			else
			{
				m_ptCurPos.x += m_speedOnAir;
				m_bmpId = IDB_SPIDER_B_GR;
			}

			//下落过程中检测是否跳到墙上
			if (CheckBuidingArea())
			{
				m_iVertState = MOVE_VERTSTATIC;
				ClimbStateChange();
			}
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

			if (m_iDirection == FACE_LEFT)
			{
				m_ptCurPos.x -= m_speedOnAir;
				m_bmpId = IDB_SPIDER_B_GL;
			}
			else
			{
				m_ptCurPos.x += m_speedOnAir;
				m_bmpId = IDB_SPIDER_B_GR;
			}
			break;
		case MOVE_VERTSTATIC:
			ChangeDirection(ptPos.x);

			if (m_iDirection == FACE_LEFT)
			{
				m_ptCurPos.x -= m_iSpeed;
				m_bmpId = IDB_SPIDER_B_GL;
			}
			else
			{
				m_ptCurPos.x += m_iSpeed;
				m_bmpId = IDB_SPIDER_B_GR;
			}

			if (m_iVertSpeed != 0)
				m_iVertSpeed = 0;
			break;
		}

		IsInMapRect(rc);
	}

	return true;
}

bool CSpider_b::LoseBlood(int iHurt)
{
	PlayDeadShootenSound();
	bool bLoseBlood = CDead::LoseBlood(iHurt);
	if (m_bDied)
	{
		if (m_cs == cs_onWall)
			ClimbStateChange();
		m_iVertState = MOVE_DOWN;
	}
	return bLoseBlood;
}

THING CSpider_b::SelfAction()
{
	if (m_bDied)
	{
		if (!m_bLoseReward)
		{
			m_bLoseReward = true;
			m_bSelfAction = false;

			THING thing;
			thing.tpye = tt_sceneObj;

			CSpiderBlood *pSpiderBlood = new CSpiderBlood;
			POINT pos;
			pos.x = m_ptCurPos.x - m_iWidth/2 - pSpiderBlood->GetWidth();
			pos.y = 596;
			pSpiderBlood->SetPosition(pos);
			thing.pThing = (void*)pSpiderBlood;

			return thing;
		}
	}
	else if (m_cs == cs_onWall)
	{
		if( rand()%120 == 0 ) //120分之一的机会产生蜘蛛
		{
		//	srand((unsigned int)time(0));

			THING thing;
			thing.tpye = tt_dead;
			CSpider_s *pSpider = new CSpider_s;
			pSpider->SetCurPos(m_ptCurPos);
			RECT rcMove = m_vecBuiding[m_curBuiding];
			rcMove.bottom += 5;
			pSpider->setMoveAbleRect(rcMove);
			thing.pThing = (void*)pSpider;
			return thing;
		}
	}
	return CDead::SelfAction();
}

void CSpider_b::getDirection(const POINT &pos)
{
	if (m_cs == cs_onWall)
	{
		float vec_x = (float)(pos.x - m_ptCurPos.x);//x分向量
		float vec_y = (float)(pos.y - m_ptCurPos.y);//y分向量

		float vec_len = sqrtf(vec_x*vec_x + vec_y*vec_y);//向量的模

		//求出向量与y轴的正余玄值
		m_sinA = vec_x/vec_len;
		m_cosA = vec_y/vec_len;
	}
}

void CSpider_b::Action(const POINT &pos)
{
	if (m_cJump == m_jumpTimes)
	{
		m_cJump = 0;
		m_jumpTimes = rand()%200 + 100; //随机获得下一次起跳间隔

		//随机获得方向
		int value = rand()%5;
		if (value > 2) // 2/5的几率改变方向
		{
			if (m_iDirection == FACE_LEFT)
				m_iDirection = FACE_RIGHT;
			else
				m_iDirection = FACE_LEFT;
		}

		int speed = rand()%m_maxJumpSpeed + 15; //获得起跳速度
		Jump(speed);
		if (m_cs != cs_notOnWall)
			ClimbStateChange();
	}
	++m_cJump;
}

void CSpider_b::Jump(int speed)
{
	m_iVertSpeed = speed;
	m_iVertState = MOVE_UP;
}

void CSpider_b::ClimbStateChange()
{
	//交换宽、高
	int temp = m_iWidth;
	m_iWidth = m_iHeigth;
	m_iHeigth = temp;

	if (m_cs == cs_notOnWall)
	{
		m_cs = cs_onWall;
		m_bmpId = IDB_SPIDER_B;
	}
	else
	{
		m_cs = cs_notOnWall;
		if (m_iDirection == FACE_LEFT)
			m_bmpId = IDB_SPIDER_B_GL;
		else
			m_bmpId = IDB_SPIDER_B_GR;
	}
}

bool CSpider_b::CheckBuidingArea()
{
	for (BUIDING_ITER iter = m_vecBuiding.begin();
		iter != m_vecBuiding.end();++iter)
	{
		if (PtInRect(&*iter,m_ptCurPos))
		{
			m_curBuiding = iter - m_vecBuiding.begin();
			return true;
		}
	}

	m_curBuiding = -1;
	return false;
}

bool CSpider_b::IsOutofCurBuidingArea()
{
	if (PtInRect(&m_vecBuiding[m_curBuiding],m_ptCurPos))
	{return false;}
	else
	{
		m_curBuiding = -1;
		return true;
	}
}