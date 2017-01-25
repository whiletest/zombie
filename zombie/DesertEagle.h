#ifndef DESERT_EAGLE_H_
#define DESERT_EAGLE_H_

#include "weapon.h"

class CDesertEagle:public CWeapon
{
public:
	CDesertEagle();
	virtual ~CDesertEagle();
public: //virtual function
	void Draw(HINSTANCE hInstance,
		HDC hdc, 
		int iFace,
		POINT ptPos,
		double sinA,
		double cosA
		);
	void Fire(const POINT &ptPos,double sinA,double cosA);
	void DrawOnGround(HINSTANCE hInstance,HDC hdc);
};

#endif