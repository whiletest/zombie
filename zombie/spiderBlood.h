#pragma once

#include "SceneObject.h"

class CSpiderBlood:public CSceneObject
{
public:
	CSpiderBlood();
public:
	virtual void Draw(HINSTANCE hInstance,HDC hdc);
};