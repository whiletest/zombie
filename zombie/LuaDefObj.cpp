#include "stdafx.h"
#include <string>
using std::string;

static inline void assert_die(int cond)
{
	if (!cond) {
		char tips[32];
		sprintf(tips, "FILE:%d LINE:%d assert_die failed.abort!!", __FILE__, __LINE__);
		MessageBoxA(NULL, tips, NULL, 0);
		exit(-1);
	}
}

CLuaDefObj::CLuaDefObj(const char *name,
		   int iWidth /* = 0 */,
		   int iHeight /* = 0 */
		   ):CSceneObject(OBJECT_LUADEF,iWidth,iHeight),m_name(name),m_L(NULL)
{
	lua_State *L = lua_open();
	luaL_openlibs(L);

	string fname = string(".\\luaobj\\") + m_name + ".lua";
	assert_die(luaL_dofile(L, fname.c_str()) == 0);
	lua_getglobal(L, "construct");
	assert_die(!lua_isnil(L, -1));
	PushThis(L);
	assert_die(lua_pcall(L, 1, 1, 0) == 0);
	assert_die(lua_istable(L, -1));
	
	lua_pushstring(L, "bmp");
	lua_gettable(L, -2);
	assert_die(lua_isstring(L, -1));
	string bmppath = lua_tostring(L, -1);
	lua_pop(L, 1);

	lua_pop(L, 1);
	m_L = L;

	m_hbmp = (HBITMAP)LoadImageA(NULL, bmppath.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	assert_die(m_hbmp != NULL);
	if (iWidth == 0 || iHeight == 0) {
		BITMAP bmp;
		GetObject(m_hbmp, sizeof(BITMAP), &bmp);
		m_iWidth = bmp.bmWidth;
		m_iHeigth = bmp.bmHeight;
	}
}

CLuaDefObj::~CLuaDefObj()
{
	lua_close(m_L);
	DeleteObject(m_hbmp);	
}

void CLuaDefObj::PushThis(lua_State *L)
{
	lua_newtable(L);

	lua_pushstring(L, "name");
	lua_pushstring(L, m_name.c_str());
	lua_settable(L, -3);

	lua_pushstring(L, "width");
	lua_pushnumber(L, m_iWidth);
	lua_settable(L, -3);

	lua_pushstring(L, "height");
	lua_pushnumber(L, m_iHeigth);
	lua_settable(L, -3);

	lua_pushstring(L, "xpos");
	lua_pushnumber(L, m_ptPosition.x);
	lua_settable(L, -3);

	lua_pushstring(L, "ypos");
	lua_pushnumber(L, m_ptPosition.y);
	lua_settable(L, -3);
}

void CLuaDefObj::Draw(HINSTANCE hInstance, HDC hdc)
{
	HDC hMemDc = CreateCompatibleDC(hdc);
	SelectObject(hMemDc, m_hbmp);
	BitBlt(hdc, m_ptPosition.x, m_ptPosition.y, 
		m_iWidth, m_iHeigth, hMemDc, 0, 0, SRCCOPY);
	DeleteDC(hMemDc);
}

int CLuaDefObj::IsOnObject(POINT ptPos)
{
	lua_getglobal(m_L, "isOnObject");
	if (lua_isnil(m_L, -1)) {
		lua_pop(m_L, 1);
		if (ptPos.y >= m_ptPosition.y
			&& ptPos.y < m_ptPosition.y + m_iHeigth
			&& ptPos.x >= m_ptPosition.x
			&& ptPos.x < m_ptPosition.x + m_iWidth)
			return ON_BOTTOMFLOOR;
		return ON_NOTHING;
	}

	//arg1->this
	PushThis(m_L);
	//arg2->pt
	lua_newtable(m_L);
	lua_pushstring(m_L, "x");
	lua_pushnumber(m_L, ptPos.x);
	lua_settable(m_L, -3);
	lua_pushstring(m_L, "y");
	lua_pushnumber(m_L, ptPos.y);
	lua_settable(m_L, -3);

	assert_die(lua_pcall(m_L, 2, 1, 0) == 0);
	assert_die(lua_isboolean(m_L, -1));

	int ret = lua_toboolean(m_L, -1);
	lua_pop(m_L, 1);
	return ret?ON_BOTTOMFLOOR:ON_NOTHING;
}

bool CLuaDefObj::IsBulletOn(CBullet *pBullet)
{
	lua_getglobal(m_L, "isBulletOn");
	if (lua_isnil(m_L, -1)) {
		lua_pop(m_L, 1);
		return false;
	}

	//arg1->this
	PushThis(m_L);
	//arg2->pt
	POINT pt = pBullet->GetPosition();
	lua_newtable(m_L);
	lua_pushstring(m_L, "x");
	lua_pushnumber(m_L, pt.x);
	lua_settable(m_L, -3);
	lua_pushstring(m_L, "y");
	lua_pushnumber(m_L, pt.y);
	lua_settable(m_L, -3);

	assert_die(lua_pcall(m_L, 2, 1, 0) == 0);
	assert_die(lua_isboolean(m_L, -1));

	int ret = lua_toboolean(m_L, -1);
	lua_pop(m_L, 1);
	return (bool)ret;
}

int CLuaDefObj::OnObjectWhere(POINT &ptPos)
{
	lua_getglobal(m_L, "onObjectWhere");
	if (lua_isnil(m_L, -1)) {
		lua_pop(m_L, -1);
		return m_ptPosition.y;
	}
	
	//arg1->this
	PushThis(m_L);
	//arg2->pt
	lua_newtable(m_L);
	lua_pushstring(m_L, "x");
	lua_pushnumber(m_L, ptPos.x);
	lua_settable(m_L, -3);
	lua_pushstring(m_L, "y");
	lua_pushnumber(m_L, ptPos.y);
	lua_settable(m_L, -3);

	assert_die(lua_pcall(m_L, 2, 1, 0) == 0);
	assert_die(lua_isnumber(m_L, -1));

	int h = lua_tonumber(m_L, -1);
	lua_pop(m_L, 1);
	return h;
}

void CLuaDefObj::Move()
{
}
