#pragma once

#include "dead.h"
#include <vector>

class CSpider_b:public CDead
{
	enum CLIMB_STATE
	{
		cs_notOnWall,
		cs_onWall
	};
	typedef std::vector<RECT>::iterator BUIDING_ITER;
	typedef std::vector<RECT>::size_type BUIDING_ST;
public:
	CSpider_b();
	virtual ~CSpider_b();
public:
	void setBuidingRectClimbAble(const RECT &rc) {m_vecBuiding.push_back(rc);}//设置可附着的建筑物范围
public: //virtual function
	virtual void Draw(HINSTANCE hInstance,HDC hdc);
	virtual void SetHuntRect(const RECT &rcClient);
protected: //virtual function
	virtual void DrawDiedZombie(HINSTANCE hInstance,HDC hdc); //绘制挂掉丧尸
	virtual bool Move(CPlayer &player,const RECT &rc);//rc一般传入得是当前地图的大小
	virtual bool LoseBlood(int iHurt);
	virtual THING SelfAction(); //产生小蜘蛛
protected:
	void ClimbStateChange(); //爬行状态发生改变
	void Jump(int speed); //跳跃
	void Action(const POINT &pos); //spider反应
	void getDirection(const POINT &pos); //获取蜘蛛向人攻击的方向(图片太大，只是求得方向，不旋转图片)
	bool CheckBuidingArea(); //当m_cs == cs_notOnWall并跳起时，使用此函数检测
	bool IsOutofCurBuidingArea(); //当m_cs == cs_onWall时，使用此函数检测
protected:
	float m_sinA; //
	float m_cosA; //
	CLIMB_STATE m_cs; //爬行状态
	std::vector<RECT> m_vecBuiding; //记录可以爬行的建筑物范围
	BUIDING_ST m_curBuiding; //记录蜘蛛当前附着的建筑(-1没在建筑上)
	int m_jumpTimes; //跳跃时间间隔
	int m_cJump; //跳跃时间间隔计数
	int m_speedOnAir; //在空中的水平速度
	unsigned int m_bmpId; //图片id
	bool m_bLoseReward; //在死的时刻落下奖励物品标识
	static const int m_maxJumpSpeed;//最大起跳速度
};