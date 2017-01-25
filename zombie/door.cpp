#include "stdafx.h"
#include <fstream>

extern DWORD WINAPI DoorOpenSoundThread(LPVOID lpParameter);

std::ifstream& operator >> (std::ifstream &infile,DOORPARAM &DoorParam)
{
	infile >> DoorParam.iDoorIndex;
	infile >> DoorParam.iKey;
	infile >> DoorParam.iToMapIndex;
	infile >> DoorParam.iDoorType;
	return infile;
}

CDoor::CDoor(int id /* = 0 */,
			 int iWidth /* = 0 */,
			 int iHeigth /* = 0 */)
			 :CSceneObject(id,iWidth,iHeigth),
			 m_iToMapIndex(0),
			 m_iKey(0),
			 m_iDoorType(IDB_ROOMDOOR)
{

}

CDoor::~CDoor()
{
}


int CDoor::Open()
{
	m_iKey = 0;
	return m_iToMapIndex;
}

POINT CDoor::GetPlayerPos()
{
	POINT ptPlayerPos;
	ptPlayerPos.x = m_ptPosition.x + m_iWidth/2;
	ptPlayerPos.y = m_ptPosition.y + m_iHeigth;
	return ptPlayerPos;
}

void CDoor::GetClientOrgPosOnMap(POINT &ptClientOrgOnMap,RECT &rcClient)
{
	ptClientOrgOnMap.x = m_ptPosition.x - rcClient.right/2;
	ptClientOrgOnMap.y = m_ptPosition.y + m_iHeigth - rcClient.bottom;
}

void CDoor::PlayDoorOpenSound()
{
	static int iSoundId;
	switch (m_iObjectId)
	{
	case OBJECT_ROOM_DOOR:
		iSoundId = SOUNDE_ROOMDOOR_OPEN;
		break;
	case OBJECT_ROADDIRECTLIGHT:
		iSoundId = SOUNDE_ROADDIRECTLIGHT;
		break;
	default:
		break;
	}
	HANDLE hSoundThread;
	hSoundThread = CreateThread(NULL,0,
		DoorOpenSoundThread,
		(LPVOID)&iSoundId,0,NULL);
	CloseHandle(hSoundThread);
}