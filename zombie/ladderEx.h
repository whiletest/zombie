#pragma once

#include "SceneObject.h"

//灵活性更强的ladder
class CLadderEx:public CSceneObject
{
	enum LADDER_STYLE
	{
		ls_normalL = 1, //向左上楼的普通梯子
		ls_normalR, //向右上楼的普通梯子
	};
public:
	CLadderEx(int width,int height);
	//////////////////////////////////////////////////////////////////////////
	void setLadderStyle(int eachWidth,int eachHeight,int style);
public: //virtual function
	virtual void Draw(HINSTANCE hInstance,HDC hdc);
	virtual int IsOnObject(POINT ptPos);
	virtual int OnObjectWhere(POINT &ptPos);
protected:
	int m_eachWidth; //每隔宽度
	int m_eachHeight; //每隔高度
	int m_style; //梯子风格
	int m_yOnWhere; //返回玩家在梯子上的位置纵坐标(如果在的话)
};