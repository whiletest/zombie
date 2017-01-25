#include "stdafx.h"
#include "resource.h"

extern DWORD WINAPI SocketSoundThread(LPVOID lpParameter);

CSocket::CSocket():CSceneObject(OBJECT_SOCKET,46,25),
				   m_bPowerOn(false),
				   m_pTv(NULL)
{

}

CSocket::~CSocket()
{

}

void CSocket::Draw(HINSTANCE hInstance,HDC hdc)
{
	int bmpID;
	if (m_bPowerOn)
		bmpID = IDB_SOCKET2;
	else
		bmpID = IDB_SOCKET1;

	HDC hMemDc = CreateCompatibleDC(hdc);
	HBITMAP hbmpTree = LoadBitmap(hInstance,MAKEINTRESOURCE(bmpID));
	SelectObject(hMemDc,hbmpTree);
	BitBlt(hdc,m_ptPosition.x,m_ptPosition.y,m_iWidth,m_iHeigth,
		hMemDc,0,0,SRCCOPY);
	DeleteDC(hMemDc);
	DeleteObject(hbmpTree);
}

int CSocket::IsOnObject(POINT ptPos)
{
	return ON_NOTHING;
}

bool CSocket::IsBulletOn(CBullet *pBullet)
{
	return false;
}

void CSocket::UseSocket()
{
	m_bPowerOn = !m_bPowerOn;
	if (m_pTv)
	{
		if (m_bPowerOn)
			m_pTv->PowerOn();
		else
			m_pTv->PowerOff();
	}
	PlaySocketSound();
}

void CSocket::PlaySocketSound()
{
	HANDLE hSoundThread = 
		CreateThread(NULL,0,
		SocketSoundThread,
		NULL,0,NULL);
	CloseHandle(hSoundThread);
}