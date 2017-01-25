#ifndef AK47_H_
#define AK47_H_

#include "weapon.h"

class CAK47:public CWeapon
{
public:
	CAK47();
	virtual ~CAK47();
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