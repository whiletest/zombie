#ifndef _bikeH_
#define _bikeH_

#include "car.h"

class CBike:public CCar
{
public:
	CBike();
	~CBike();
	void SetBikeKind(_objectIdentify id,int iWidth,int iHeight);
public: //virtual function
	void Draw(HINSTANCE hInstance,HDC hdc);
	int IsOnObject(POINT ptPos);
};

#endif