#ifndef M4A1_H_
#define M4A1_H_

#include "weapon.h"

class CM4A1:public CWeapon
{
public:
	CM4A1();
	virtual ~CM4A1();
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