#pragma once

#include "multipleObj.h"

class CNonInteractiveObj:public CMultipleObj //非交互式物品类
{
public:
	CNonInteractiveObj(int width,int height);
public:
	virtual int IsOnObject(POINT ptPos);
	virtual int OnObjectWhere(POINT &ptPos);
};