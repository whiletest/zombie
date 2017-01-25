#pragma once

#include "dead.h"

class CHunter:public CDead
{
public:
	CHunter();
	virtual ~CHunter();
public:
public: //virtual function
	virtual void Draw(HINSTANCE hInstance,HDC hdc);
	virtual void SetHuntRect(const RECT &rcClient);
protected: //virtual function
	virtual void DrawDiedZombie(HINSTANCE hInstance,HDC hdc); //绘制挂掉丧尸
	virtual bool Move(CPlayer &player,const RECT &rc);
	virtual bool LoseBlood(int iHurt);
protected:
	int CheckDistance(const POINT &pos); //检测和给定点的距离,返回攻击的起跳初速度
	void Jump(int speed); //跳起
	void Action(const POINT *pos); //hunter反应
protected:
	int m_jumpTimes; //跳跃时间间隔
	int m_cJump; //跳跃时间间隔计数
	static const int m_maxJumpSpeed;//最大起跳速度
};