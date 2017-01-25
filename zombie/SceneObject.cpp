#include "stdafx.h"

DWORD WINAPI ObjectSoundThread(LPVOID lpParameter);

CSceneObject::CSceneObject(int id,
						   int iWidth /* = 0 */,
						   int iHeight /* = 0 */
						   ):m_iWidth(iWidth),
						   m_iHeigth(iHeight),
						   m_iObjectId(id),
						   m_bMouseOnObj(false),
						   m_iSoundId(_sound_none)
{
	m_ptPosition.x = 0;
	m_ptPosition.y = 0;
}

CSceneObject::~CSceneObject()
{

}

void CSceneObject::SetPosition(POINT pt)
{
	m_ptPosition = pt;
}

POINT CSceneObject::GetPosition() const
{
	return m_ptPosition;
}

void CSceneObject::SetHeigth(int iHeigth)
{
	m_iHeigth = iHeigth;
}

void CSceneObject::SetWidth(int iWidth)
{
	m_iWidth = iWidth;
}

int CSceneObject::GetHeigth() const
{
	return m_iHeigth;
}

int CSceneObject::GetWidth() const
{
	return m_iWidth;
}

void CSceneObject::GetObjRect(RECT &rcRect)
{
	rcRect.left = m_ptPosition.x;
	rcRect.top = m_ptPosition.y;
	rcRect.right = m_ptPosition.x + m_iWidth;
	rcRect.bottom = m_ptPosition.y + m_iHeigth;
}

bool CSceneObject::IsMouseOnObj(POINT &ptMouse)
{
	RECT rcObj;
	GetObjRect(rcObj);
	if (PtInRect(&rcObj,ptMouse))
		m_bMouseOnObj = true;
	else
		m_bMouseOnObj = false;

	return m_bMouseOnObj;
}

int CSceneObject::OnObjectWhere(POINT &ptPos)
{
	return m_ptPosition.y;
}

void CSceneObject::Move()
{

}

void CSceneObject::PlayObjSound()
{
	HANDLE hSoundThread;
	hSoundThread = CreateThread(NULL,0,
		ObjectSoundThread,
		(LPVOID)&m_iSoundId,0,NULL);
	CloseHandle(hSoundThread);
}

bool CSceneObject::IsBulletOn(CBullet *pBullet)
{
	return false;
}

int CSceneObject::IsOnObject(POINT ptPos)
{
	return ON_NOTHING;
}
