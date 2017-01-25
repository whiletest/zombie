#ifndef DEADMAN_H_
#define DEADMAN_H_

#include "dead.h"

class CDeadMan:public CDead
{
public:
	CDeadMan();
	~CDeadMan();
	void SetIndex(int index) {m_iIndex = index;}
public: //virtual function
	virtual void Draw(HINSTANCE hInstance,HDC hdc);
	virtual void SetHuntRect(const RECT &rcClient);
protected: //virtual function
	virtual void DrawDiedZombie(HINSTANCE hInstance,HDC hdc); //绘制挂掉丧尸
	virtual bool Move(CPlayer &player,const RECT &rc);
protected:
	int m_iIndex; //死人的索引号
};


#endif