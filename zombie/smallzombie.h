#ifndef SMALL_ZOMBIE_H
#define SMALL_ZOMBIE_H

#include "dead.h"

class CSmallZombie:public CDead
{
public:
	CSmallZombie();
	~CSmallZombie();
public: //virtual function
	virtual void Draw(HINSTANCE hInstance,HDC hdc);
	virtual void SetHuntRect(const RECT &rcClient);
protected: //virtual function
	virtual void DrawDiedZombie(HINSTANCE hInstance,HDC hdc); //ªÊ÷∆π“µÙ…• ¨
	virtual bool Move(CPlayer &player,const RECT &rc);
	virtual bool LoseBlood(int iHurt);
};

#endif