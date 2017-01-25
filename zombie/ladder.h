#ifndef _ladderH_
#define _ladderH_

#include "SceneObject.h"

class CLadder:public CSceneObject
{
public:
	CLadder();
	virtual ~CLadder();
public: //virtual function
	virtual void Draw(HINSTANCE hInstance,HDC hdc);
	virtual int IsOnObject(POINT ptPos);
	virtual int OnObjectWhere(POINT &ptPos);
protected:
	POINT m_keyPoint[11];
};

#endif