#ifndef _rainH_
#define _rainH_

#include "SceneObject.h"

class CRain:public CSceneObject
{
public:
	CRain();
	virtual ~CRain();
public://virtual function
	void Draw(HINSTANCE hInstance,HDC hdc);
	void Move();
protected:
	int m_iVertSpeed; //ÊúÖ±ËÙ¶È
};

#endif