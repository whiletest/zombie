#ifndef USP_H_
#define USP_H_

#include "weapon.h"

class CUSP:public CWeapon
{
public:
	CUSP();
	virtual ~CUSP();
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