#include "stdafx.h"

CMap::CMap():m_iMapIndex(0)
{

}

CMap::~CMap()
{
	ClearAllDead();
	ClearAllSceneObj();
}

void CMap::InitializeMapSize(POINT &ptPos,int iWidth,int iHeigth)
{
	m_rcMap.left = ptPos.x;
	m_rcMap.top = ptPos.y;
	m_rcMap.right = iWidth;
	m_rcMap.bottom = iHeigth;
}

void CMap::AddDead(CDead *pDead)
{
	m_vecDead.push_back(pDead);
}

void CMap::AddSceneObj(CSceneObject *pSceneObj)
{
	m_vecSceneObj.push_back(pSceneObj);
}

void CMap::AddWeapon(CWeapon* pWeapon)
{
	m_vecWeaponOnGround.push_back(pWeapon);
}

CDoor* CMap::FoundRelativeDoor(int iDoorIndex)
{
	int id;
	for (SCENEOBJITER iter = m_vecSceneObj.begin();
		iter != m_vecSceneObj.end();++iter)
	{
		id = (*iter)->GetId();
		if (   id == OBJECT_ROOM_DOOR
			|| id == OBJECT_ROADDIRECTLIGHT )
		{
			if ( ((CDoor*)(*iter))->GetDoorIndex() == iDoorIndex )
				return ((CDoor*)(*iter));
		}
	}
	return NULL;
}


void CMap::SetNewWeapon(CWeapon *pOldWeapon,CWeapon *pNewWeapon)
{
	for (WEAPONITER iter = m_vecWeaponOnGround.begin();
		iter != m_vecWeaponOnGround.end();++iter)
	{
		if (pOldWeapon == *iter)
		{
			if (pNewWeapon)
				*iter = pNewWeapon;
			else
				m_vecWeaponOnGround.erase(iter);
			break;
		}
	}
}

void CMap::GetDead(std::vector<CDead*> &vecDead)
{
	vecDead.assign(m_vecDead.begin(),m_vecDead.end());
}

void CMap::GetSceneObj(std::vector<CSceneObject*> &vecSceneObj)
{
	vecSceneObj.assign(m_vecSceneObj.begin(),m_vecSceneObj.end());
}

void CMap::GetWeapon(std::vector<CWeapon*> &vecWeapon)
{
	vecWeapon.assign(m_vecWeaponOnGround.begin(),m_vecWeaponOnGround.end());
}

void CMap::EraseObjFromMap(CSceneObject *pObj)
{
	for (SCENEOBJITER iter = m_vecSceneObj.begin();
		iter != m_vecSceneObj.end();++iter)
	{
		if ( pObj == *iter )
		{
			m_vecSceneObj.erase(iter);
			break;
		}
	}
}

void CMap::EraseWeaponFromMap(CWeapon *pWeapon)
{
	for (WEAPONITER iter = m_vecWeaponOnGround.begin();
		iter != m_vecWeaponOnGround.end();++iter)
	{
		if (*iter == pWeapon)
		{
			m_vecWeaponOnGround.erase(iter);
			break;
		}
	}
}

void CMap::ClearAllDead()
{
//	typedef std::vector<CDead*>::iterator DEADITER;
	for (DEADITER iter = m_vecDead.begin();
		iter != m_vecDead.end();++iter)
	{
		delete *iter;
	}
	m_vecDead.clear();
}

void CMap::ClearAllSceneObj()
{
//	typedef std::vector<CSceneObject*>::iterator SCENEOBJITER;
	for (SCENEOBJITER iter = m_vecSceneObj.begin();
		iter != m_vecSceneObj.end();++iter)
	{
		delete *iter;
	}
	m_vecSceneObj.clear();
}

void CMap::ClearAllWeapon()
{
	for (WEAPONITER iter = m_vecWeaponOnGround.begin();
		iter != m_vecWeaponOnGround.end();++iter)
	{
		delete *iter;
	}
	m_vecWeaponOnGround.clear();
}