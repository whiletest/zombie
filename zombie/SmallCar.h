#ifndef SMALL_CAR_H_
#define SMALL_CAR_H_

#include "car.h"

class CSmallCar:public CCar
{
public:
	CSmallCar();
	~CSmallCar();
public: //virtual function
	void Draw(HINSTANCE hInstance,HDC hdc);
	int IsOnObject(POINT ptPos);
	bool IsBulletOn(CBullet *pBullet);
	int OnObjectWhere(POINT &ptPos);
};

#endif