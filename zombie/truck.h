#ifndef _truckH_
#define _truckH_

#include "car.h"

class CTruck:public CCar
{
public:
	CTruck();
	~CTruck();
	void SetTruckKind(_objectIdentify id,int iWidth,int iHeight);
public: //virtual function
	void Draw(HINSTANCE hInstance,HDC hdc);
	int IsOnObject(POINT ptPos);
};

#endif