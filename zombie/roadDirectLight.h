#ifndef _roadDirectLightH_
#define _roadDirectLightH_

#include "door.h"

class CRoadDirectLight:public CDoor
{
public:
	CRoadDirectLight();
	virtual ~CRoadDirectLight();
public://virtual function
	void Draw(HINSTANCE hInstance,HDC hdc);
};

#endif