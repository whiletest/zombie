#ifndef DOG_H_
#define DOG_H_

#include "dead.h"

class CDog:public CDead
{
public:
	CDog();
	~CDog();
	void SetTieFlag(bool bTied);
public: //virtual function
	virtual void Draw(HINSTANCE hInstance,HDC hdc);
	virtual void SetHuntRect(const RECT &rcClient);
	virtual bool Move(CPlayer &player,const RECT &rc);
protected: //virtual function
	virtual void DrawDiedZombie(HINSTANCE hInstance,HDC hdc); //
	virtual bool LoseBlood(int iHurt);
protected:
	int m_iRightID;
	int m_iLeftID;
	POINT m_ptOrgPos; //被栓住的位置
	bool m_bTied;
	int m_iBarkTime; //狗叫持续时间
};

#endif