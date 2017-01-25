#ifndef AWP_H_
#define AWP_H_

#include "weapon.h"

class CAWP:public CWeapon
{
public:
	CAWP();
	~CAWP();
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