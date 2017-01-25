#ifndef FIVE_SEVEN_H_
#define FIVE_SEVEN_H_

#include "weapon.h"

class CFiveSeven:public CWeapon
{
public:
	CFiveSeven();
	virtual ~CFiveSeven();
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