#pragma once

#include "SceneObject.h"

/************************************************************************/
/* 用于一个类表示多个物体                                                 
/************************************************************************/
class CMultipleObj:public CSceneObject
{
public:
	CMultipleObj(int objId = 0,int width = 0,int height = 0);
	virtual ~CMultipleObj();
	///////////////////////////
	void setObjKind(int bmpIndex) {m_bmpIndex = bmpIndex;}
	void setObjKind(int width,int height,int bmpIndex);
	void getObjkind(int *pIndex,int *pwidth = 0,int *pheight = 0);
	///////////////////////////
public:
	void Draw(HINSTANCE hInstance,HDC hdc);
protected:
	int m_bmpIndex;//图片id
};