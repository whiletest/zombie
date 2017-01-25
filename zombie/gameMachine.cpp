#include "stdafx.h"

CGameMachine::CGameMachine(int id /* = OBJECT_GAMEMACHINE */,
						   int width /* = 59 */,
						   int height /* = 70 */):
                           CSceneObject(id,width,height)
{

}

CGameMachine::~CGameMachine()
{

}

void CGameMachine::SetKind(_objectIdentify id,
						  int iWidth,
						  int iHeight)
{
	m_iObjectId = id;
	m_iWidth = iWidth;
	m_iHeigth = iHeight;
}

void CGameMachine::Draw(HINSTANCE hInstance, HDC hdc)
{
	int bmpId;
	switch (m_iObjectId)
	{
	case OBJECT_GAMEMACHINE:
		bmpId = IDB_GAMEMACHINE;
		break;
	case OBJECT_GAMEMACHINE1:
		bmpId = IDB_GAMEMACHINE1;
		break;
	case OBJECT_GAMEMACHINE2:
		bmpId = IDB_GAMEMACHINE2;
		break;
	default:
		return;
	}
	HDC hMemDc = CreateCompatibleDC(hdc);
	HBITMAP hbmp = LoadBitmap(hInstance,MAKEINTRESOURCE(bmpId));
	SelectObject(hMemDc,hbmp);
	
	if (m_bMouseOnObj)
		TextOut(hdc,m_ptPosition.x,m_ptPosition.y-15,TEXT("ÓÎÏ·»ú"),3);

	BitBlt(hdc,m_ptPosition.x,m_ptPosition.y,m_iWidth,m_iHeigth,
		hMemDc,0,0,SRCCOPY);

	DeleteDC(hMemDc);
	DeleteObject(hbmp);
}

int CGameMachine::IsOnObject(POINT ptPos)
{
	return ON_NOTHING;
}
