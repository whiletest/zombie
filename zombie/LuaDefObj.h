#pragma once

#include "SceneObject.h"
#include "inc\\lua.hpp"
#include "inc\lauxlib.h"
#include "inc\lualib.h"

class CLuaDefObj:public CSceneObject
{
public:
	CLuaDefObj(const char *name = "box",int iWidth = 0,int iHeigth = 0);
	virtual ~CLuaDefObj();
	//
	virtual int OnObjectWhere(POINT &ptPos);
	virtual void Move();
	virtual int IsOnObject(POINT ptPos);
	virtual bool IsBulletOn(CBullet *pBullet);
	virtual void Draw(HINSTANCE hInstance,HDC hdc);
protected:
	void PushThis(lua_State *L);
protected:
	string m_name;
	HBITMAP m_hbmp;
	lua_State *m_L;
};
