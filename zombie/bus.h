#ifndef BUS_H_
#define BUS_H_

#include "car.h"

class CBus:public CCar
{
public:
	CBus();
	~CBus();
public: //virtual function
	void Draw(HINSTANCE hInstance,HDC hdc);
	int IsOnObject(POINT ptPos);
	bool IsBulletOn(CBullet *pBullet);
};

#endif