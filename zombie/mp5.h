#ifndef MP5_H_
#define MP5_H_

#include "weapon.h"

class CMP5:public CWeapon
{
public:
	CMP5();
	~CMP5();
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