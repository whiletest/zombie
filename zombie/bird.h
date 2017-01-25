#ifndef BIRD_H_
#define BIRD_H_

#include "dead.h"

class CBullet;

class CBird:public CDead
{
public:
	CBird();
	~CBird();
	void SetHearRect(RECT &rcHear);
	bool IsHearFire(CBullet *pBullet);
public: //virtual function
	virtual void Draw(HINSTANCE hInstance,HDC hdc);
	virtual void SetHuntRect(const RECT &rcClient);
	virtual bool Move(CPlayer &player,const RECT &rc);
protected: //virtual function
	virtual void DrawDiedZombie(HINSTANCE hInstance,HDC hdc); //绘制挂掉丧尸
protected:
	RECT m_rcHear; //听力区域
	int m_iVertDirection; //竖直方向的状态
	int m_iChangeTimes; //改变方向频率
	int m_iChangeRateCount; //改变方向频率计数
	int m_iChangeTimesCount; //改变次数计数
	static bool m_bHearFire; //听到枪声
};

#endif