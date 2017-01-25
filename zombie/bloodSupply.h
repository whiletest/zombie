#pragma once

#include "multipleObj.h"

struct BLOODSUPPLYPARAM
{
	int bmpIndex;
	int bloodIncrease;
};

class CBloodSupply:public CMultipleObj
{
public:
	CBloodSupply(int bi = 0);
	virtual ~CBloodSupply();
	//////////////////////////////
	int getIncrease()const {return m_bloodIncrease;}
	/////////////////////////////
public: //virtual func
	void Draw(HINSTANCE hInstance,HDC hdc);
protected:
	int m_bloodIncrease; //¼ÓÑªÁ¿
};