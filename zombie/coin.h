#ifndef _coinH_
#define _coinH_

#include "SceneObject.h"

class CCoin:public CSceneObject
{
public:
	CCoin();
	virtual ~CCoin();
public://virtual function
	virtual void Draw(HINSTANCE hInstance,HDC hdc);
};

#endif