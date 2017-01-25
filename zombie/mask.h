#ifndef _maskH_
#define _maskH_

#include "SceneObject.h"

class CMask:public CSceneObject
{
public:
	CMask(int id = OBJECT_MASK1,int iwidth = 24,int height = 20);
	virtual ~CMask();
public://virtual function
	void Draw(HINSTANCE hInstance,HDC hdc);
};

#endif