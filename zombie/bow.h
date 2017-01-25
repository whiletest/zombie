#ifndef BOW_H_
#define BOW_H_

#include "weapon.h"

class CBow:public CWeapon
{
public:
	CBow();
	virtual ~CBow();
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