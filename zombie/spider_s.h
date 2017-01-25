#pragma once

#include "dead.h"

class CSpider_s:public CDead
{
public:
	CSpider_s();
	virtual ~CSpider_s();
public:
	void setMoveAbleRect(const RECT &rc) {m_rcMove = rc;}
public: //virtual function
	virtual void Draw(HINSTANCE hInstance,HDC hdc);
	virtual void SetHuntRect(const RECT &rcClient);
protected: //virtual function
	virtual void DrawDiedZombie(HINSTANCE hInstance,HDC hdc); //绘制挂掉丧尸
	virtual bool Move(CPlayer &player,const RECT &rc);//rc一般传入得是当前地图的大小
	virtual bool LoseBlood(int iHurt);
protected:
	void Action(); //spider反应
	void getDirection(const POINT &pos); //获取蜘蛛向人攻击的方向(以便旋转位图)
	bool IsInMoveAbleRect(const POINT &pos)const {return (bool)PtInRect(&m_rcMove,pos);} //是否在蜘蛛的可移动区
protected:
	RECT m_rcMove; //只能在此区域移动
	float m_sinA; //
	float m_cosA; //
};