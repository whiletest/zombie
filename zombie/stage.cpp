#include "stdafx.h"
#include <fstream>

extern std::ifstream& operator >> (std::ifstream &infile,DOORPARAM &DoorParam);
extern std::ifstream &operator >> (std::ifstream &in,BLOODSUPPLYPARAM &bsParam);

CStage::CStage():m_iStage(0),m_iMapNodeNum(-1),m_iCurIndex(0),m_iDoorNum(0)
{
}

CStage::~CStage()
{
	ClearAllDead();
	ClearAllSceneObj();
	ClearAllWeapon();

	for (MAPITER iter = m_vecMap.begin();
		iter != m_vecMap.end();++iter)
		delete *iter;
	m_vecMap.clear();
}

void CStage::ReInitialStage()
{
	m_iMapNodeNum = -1;
	m_iCurIndex = 0;
	m_iDoorNum = 0;

	ClearAllDead();
	ClearAllSceneObj();
	ClearAllWeapon();

	for (MAPITER iter = m_vecMap.begin();
		iter != m_vecMap.end();++iter)
		delete *iter;
	m_vecMap.clear();
}

void CStage::EraseObjFromCurMap(CSceneObject *pObj)
{
	m_vecMap[m_iCurIndex]->EraseObjFromMap(pObj);
}

void CStage::EraseWeaponFromCurMap(CWeapon *pWeapon)
{
	m_vecMap[m_iCurIndex]->EraseWeaponFromMap(pWeapon);
}

void CStage::AddObjToCurMap(CSceneObject *pObj)
{
	m_vecMap[m_iCurIndex]->AddSceneObj(pObj);
}

void CStage::AddWeaponToCurMap(CWeapon *pWeapon)
{
	m_vecMap[m_iCurIndex]->AddWeapon(pWeapon);
}

void CStage::AddDeadToCurMap(CDead *pDead)
{
	m_vecMap[m_iCurIndex]->AddDead(pDead);
}

bool CStage::InitializeStage(CPlayer &player,POINT &ptClientOrgOnMap)
{
	std::ifstream infile(".\\res\\MAP.DAT");
	if (!infile)
		return false;
	char cMssgInfo;
	int iStage = 0;
	int id;
	POINT ptPos;
	int iWidth, iHeigth;
	LPVOID pVoid = NULL;

	static DOORPARAM DoorParam;
	static int intParam; //1个特别参数
	static POINT ptParam; //2个特别参数
	static RECT rcParam; //3-4个特别参数

	while (true)
	{
		infile >> cMssgInfo;
		if (cMssgInfo == '/')
		{
			char szNoUse[100];
			infile.getline(szNoUse,100,'\n');
			continue;
		}
		if (cMssgInfo == 'B')
		{
			infile >> iStage;
			if (iStage == m_iStage)
				break;
		}
	}
	while (cMssgInfo != 'E')
	{
		infile >> cMssgInfo;
		if ( isdigit(cMssgInfo) )
			infile.putback(cMssgInfo);
		else 
		{
			if (cMssgInfo == '/')
			{
				char szNoUse[100];
				infile.getline(szNoUse,100,'\n');
			}
			continue;
		}
			
		infile >> id;
		infile >> ptPos.x >> ptPos.y;
		infile >> iWidth >> iHeigth;

		switch (id)
		{
		case ID_DOOR_INDEX_TABLE:
			m_iDoorNum = iHeigth;
			for (int i = 0;i != m_iDoorNum;++i)
				infile >> m_iDoorIndexTable[i];
			break;
		case ID_MAP:
		case ID_PLAYER:
		case ID_CLIENT_ORGPOS_ON_MAP:
			InitializeMap(id,ptPos,iWidth,iHeigth,player,ptClientOrgOnMap);
			break;
		case OBJECT_GROUND:
		case OBJECT_TREE:
		case OBJECT_CLOUD:
		case OBJECT_GRASS:
		case OBJECT_CUTDOWNTREE:
		case OBJECT_DEADTREE:
		case OBJECT_SMALLCAR:
		case OBJECT_KEY:
		case OBJECT_PAPER:
		case OBJECT_WALL:
		case OBJECT_WINDOW1:
		case OBJECT_CABINET:
		case OBJECT_BULLETSUPPLY:
		case OBJECT_ROADSIGN:
		case OBJECT_BUS:
		case OBJECT_CLOSESTOOL:
		case OBJECT_BED:
		case OBJECT_TV:
		case OBJECT_SOCKET:
		case OBJECT_DISK:
		case OBJECT_WASHPOT:
		case OBJECT_SAFEBOX:
		case OBJECT_SOFA:
		case OBJECT_DESK:
		case OBJECT_FOOTBALL:
		case OBJECT_MESSIPAPER:
		case OBJECT_HOMEGATE:
		case OBJECT_STICK:
		case OBJECT_BUSSET:
		case OBJECT_TRUCK:
		case OBJECT_TRUCK1:
		case OBJECT_BIKE:
		case OBJECT_GAMEMACHINE:
		case OBJECT_GAMEMACHINE1:
		case OBJECT_GAMEMACHINE2:
		case OBJECT_COIN:
		case OBJECT_LADDER:
		case OBJECT_MASK1:
		case OBJECT_MASK2:
			CreateSceneObject(id,ptPos,iWidth,iHeigth,pVoid);
			break;
		case OBJECT_LUADEF:
			{
				char objname[32];
				infile.getline(objname, ' ');
				CreateSceneObject(id,ptPos,iWidth,iHeigth,(void*)(objname+1));
			}
			break;
		case OBJECT_BLOODSUPPLY:
			{
				BLOODSUPPLYPARAM bsParam;
				infile >> bsParam;
				pVoid = (LPVOID)&bsParam;
				CreateSceneObject(id,ptPos,iWidth,iHeigth,pVoid);
				break;
			}
		case OBJECT_HOUSE1:
			infile >> intParam;
			pVoid = (LPVOID)&intParam;
			CreateSceneObject(id,ptPos,iWidth,iHeigth,pVoid);
			break;
		case OBJECT_ROOM_DOOR:
		case OBJECT_ROADDIRECTLIGHT:
			infile >> DoorParam;
			pVoid = (LPVOID)&DoorParam;
			CreateSceneObject(id,ptPos,iWidth,iHeigth,pVoid);
			break;
		case OBJECT_NONINTERACTIVE:
			infile >> intParam;
			CreateSceneObject(id,ptPos,iWidth,iHeigth,(LPVOID)&intParam);
			break;
		case OBJECT_LADDEREX:
			infile >> rcParam.left >> rcParam.top >> rcParam.right;
			CreateSceneObject(id,ptPos,iWidth,iHeigth,(LPVOID)&rcParam);
			break;
		case ID_SMALLZOMBIE:
		case ID_BIRD:
		case ID_HUNTER:
		case ID_SPIDER_B:
			CreateZombie(id,ptPos,iWidth,iHeigth,pVoid);
			break;
		case ID_DOG:
			infile >> intParam;
			pVoid = (LPVOID)&intParam;
			CreateZombie(id,ptPos,iWidth,iHeigth,pVoid);
			break;
		case ID_DEADMAN:
			infile >> intParam;
			pVoid = (LPVOID)&intParam;
			CreateZombie(id,ptPos,iWidth,iHeigth,pVoid);
			break;
		case ID_SPIDER_S:
			infile >> rcParam.left >> rcParam.top;
			infile >> rcParam.right >> rcParam.bottom;
			CreateZombie(id,ptPos,iWidth,iHeigth,(LPVOID)&rcParam);
			break;
		case ID_DESERT_EAGLE:
		case ID_FIVESEVEN:
		case ID_USP:
		case ID_MP5:
		case ID_AK47:
		case ID_M4A1:
		case ID_AWP:
		case ID_BOW:
			CreateWeaponOnGround(id,ptPos);
			break;
		default:
			break;
		}		
	}
	infile.close();
	infile.clear();
	return true;
}


void CStage::InitializeMap(int id, //in
						   POINT &ptPos, //in
						   int iWidth, //in
						   int iHeigth, //in
						   CPlayer &player, //out
						   POINT &ptClientOrgOnMap /*out*/)
{
	CMap *pMap = NULL;
	switch (id)
	{
	case ID_MAP:
		++m_iMapNodeNum; //从-1开始
		pMap = new CMap;
		pMap->InitializeMapSize(ptPos,iWidth,iHeigth);
		pMap->SetIndex(m_iMapNodeNum);
		m_vecMap.push_back(pMap);
		break;
	case ID_PLAYER:
		player.SetHoriPos(ptPos.x);
		player.SetVertPos(ptPos.y);
		break;
	case ID_CLIENT_ORGPOS_ON_MAP:
		ptClientOrgOnMap = ptPos;
		break;
	}
}

void CStage::CreateWeaponOnGround(int id,POINT &ptPos)
{
	CWeapon *pWeapon = NULL;

	switch (id)
	{
	case ID_DESERT_EAGLE:
		pWeapon = new CDesertEagle;
		break;
	case ID_AK47:
		pWeapon = new CAK47;
		break;
	case ID_M4A1:
		pWeapon = new CM4A1;
		break;
	case ID_AWP:
		pWeapon = new CAWP;
		break;
	case ID_FIVESEVEN:
		pWeapon = new CFiveSeven;
		pWeapon->SetBulletNum(0);
		break;
	case ID_USP:
		pWeapon = new CUSP;
		break;
	case ID_MP5:
		pWeapon = new CMP5;
		break;
	case ID_BOW:
		pWeapon = new CBow;
		break;
	default:
		break;
	}

	POINT ptWeaponPos = 
	      {ptPos.x,ptPos.y-pWeapon->GetHeigth()/2};
	pWeapon->SetPosOnGround(ptWeaponPos);
	m_vecMap[m_iMapNodeNum]->AddWeapon(pWeapon);
	pWeapon = NULL;
}

void CStage::CreateZombie(int id,POINT &ptPos,int iWidth,int iHeigth,LPVOID pVoid)
{
	CDead *pDead = NULL;
	static RECT rcHunt = {0,0,1024,600};
	static RECT rcHear = {0,0,500,250};

	switch (id)
	{
	case ID_SMALLZOMBIE:
		pDead = new CSmallZombie;
		//设置位置
		pDead->SetCurPos(ptPos);
		//设置追踪区域
		pDead->SetHuntRect(rcHunt);
		break;
	case ID_HUNTER:
		pDead = new CHunter;
		pDead->SetCurPos(ptPos);
		pDead->SetHuntRect(rcHunt);
		break;
	case ID_DOG:
		pDead = new CDog;
		pDead->SetCurPos(ptPos);
		pDead->SetHuntRect(rcHunt);
		((CDog*)pDead)->SetTieFlag(*((int*)pVoid));
		break;
	case ID_BIRD:
		pDead = new CBird;
		pDead->SetCurPos(ptPos);
		//鸟类追踪区默认为0
		((CBird*)pDead)->SetHearRect(rcHear);
		break;
	case ID_DEADMAN:
		pDead = new CDeadMan;
		pDead->SetCurPos(ptPos);
		pDead->SetWidth(iWidth);
		pDead->SetHeight(iHeigth);
		((CDeadMan*)pDead)->SetIndex(*((int*)pVoid));
		break;
	case ID_SPIDER_S:
		{
			RECT rcMove = *((RECT*)pVoid);
			pDead = new CSpider_s;
			pDead->SetCurPos(ptPos);
			((CSpider_s*)pDead)->setMoveAbleRect(rcMove);
		}
		break;
	case ID_SPIDER_B:
		{
			pDead = new CSpider_b;
			pDead->SetCurPos(ptPos);
			std::vector<CSceneObject*> vecSceneObj;
			m_vecMap[m_iMapNodeNum]->GetSceneObj(vecSceneObj);
			RECT rcObj;
			for (SCENEOBJITER iter = vecSceneObj.begin();
				iter != vecSceneObj.end();++iter)
			{
				(*iter)->GetObjRect(rcObj);
				if (   rcObj.right - rcObj.left > pDead->GetWidth()
					&& rcObj.bottom - rcObj.top > pDead->GetHeigth() )
					((CSpider_b*)pDead)->setBuidingRectClimbAble(rcObj);
			}
		}
		break;
	default:
		break;
	}

	m_vecMap[m_iMapNodeNum]->AddDead(pDead);
	pDead = NULL;
}

void CStage::CreateSceneObject(int id,POINT &ptPos,int iWidth,int iHeigth,LPVOID pVoid)
{
	CSceneObject *pSceneObj = NULL;
	static DOORPARAM DoorParam;
	static CTv *pTv = NULL;
	static CBulletSupply *pBS = NULL;
	static CDisk *pDisk = NULL;

	switch (id)
	{
	case OBJECT_GROUND:
		pSceneObj = new CGround;
		pSceneObj->SetPosition(ptPos);
		pSceneObj->SetWidth(iWidth);
		break;
	case OBJECT_WALL:
		pSceneObj = new CWall;
		pSceneObj->SetPosition(ptPos);
		pSceneObj->SetHeigth(iHeigth);
		((CWall*)pSceneObj)->SetType(iWidth);
		break;
	case OBJECT_WINDOW1:
		pSceneObj = new CWindow1;
		pSceneObj->SetPosition(ptPos);
		break;
	case OBJECT_MESSIPAPER:
		pSceneObj = new CMessiPaper;
		pSceneObj->SetPosition(ptPos);
		break;
	case OBJECT_HOMEGATE:
		pSceneObj = new CHomeGate;
		pSceneObj->SetPosition(ptPos);
		break;
	case OBJECT_CABINET:
		pSceneObj = new CCabinet;
		pSceneObj->SetPosition(ptPos);
		break;
	case OBJECT_STICK:
		pSceneObj = new CStick;
		pSceneObj->SetPosition(ptPos);
		break;
	case OBJECT_BUSSET:
		pSceneObj = new CBusSet;
		pSceneObj->SetPosition(ptPos);
		break;
	case OBJECT_BULLETSUPPLY:
		pSceneObj = new CBulletSupply;
		pSceneObj->SetPosition(ptPos);
		((CBulletSupply*)pSceneObj)->SetWeaponKind(iWidth);
		((CBulletSupply*)pSceneObj)->SetBulletNum(iHeigth);
		pBS = (CBulletSupply*)pSceneObj;
		break;
	case OBJECT_BUS:
		pSceneObj = new CBus;
		pSceneObj->SetPosition(ptPos);
		break;
	case OBJECT_TRUCK:
		pSceneObj = new CTruck;
		pSceneObj->SetPosition(ptPos);
		((CTruck*)pSceneObj)->SetTruckKind(OBJECT_TRUCK,iWidth,iHeigth);
		break;
	case OBJECT_TRUCK1:
		pSceneObj = new CTruck;
		pSceneObj->SetPosition(ptPos);
		((CTruck*)pSceneObj)->SetTruckKind(OBJECT_TRUCK1,iWidth,iHeigth);
		break;
	case OBJECT_GAMEMACHINE1:
	case OBJECT_GAMEMACHINE:
	case OBJECT_GAMEMACHINE2:
		pSceneObj = new CGameMachine(id,iWidth,iHeigth);
		pSceneObj->SetPosition(ptPos);
		break;
	case OBJECT_COIN:
		pSceneObj = new CCoin;
		pSceneObj->SetPosition(ptPos);
		break;
	case OBJECT_LADDER:
		pSceneObj = new CLadder;
		pSceneObj->SetPosition(ptPos);
		break;
	case OBJECT_LADDEREX:
		pSceneObj = new CLadderEx(iWidth,iHeigth);
		pSceneObj->SetPosition(ptPos);
		((CLadderEx*)pSceneObj)->setLadderStyle(
			((RECT*)pVoid)->left, //每隔宽
			((RECT*)pVoid)->top, //每隔高
			((RECT*)pVoid)->right); //类型
		break;
	case OBJECT_MASK1:
	case OBJECT_MASK2:
		pSceneObj = new CMask(id,iWidth,iHeigth);
		pSceneObj->SetPosition(ptPos);
		break;
	case OBJECT_NONINTERACTIVE:
		pSceneObj = new CNonInteractiveObj(iWidth,iHeigth);
		pSceneObj->SetPosition(ptPos);
		((CNonInteractiveObj*)pSceneObj)->setObjKind(*(int*)pVoid);
		break;
	case OBJECT_BLOODSUPPLY:
		{
			BLOODSUPPLYPARAM *pbsParam = (BLOODSUPPLYPARAM*)pVoid;
			pSceneObj = new CBloodSupply(pbsParam->bloodIncrease);
			((CBloodSupply*)pSceneObj)->setObjKind(iWidth,iHeigth,pbsParam->bmpIndex);
			pSceneObj->SetPosition(ptPos);
			break;
		}
	case OBJECT_TV:
		pSceneObj = new CTv;
		pSceneObj->SetPosition(ptPos);
		pTv = (CTv*)pSceneObj;
		break;
	case OBJECT_SOFA:
		pSceneObj = new CSofa;
		pSceneObj->SetPosition(ptPos);
		break;
	case OBJECT_FOOTBALL:
		pSceneObj = new CFootball;
		pSceneObj->SetPosition(ptPos);
		break;
	case OBJECT_SOCKET:
		pSceneObj = new CSocket;
		pSceneObj->SetPosition(ptPos);
		((CSocket*)pSceneObj)->SetRelativeTv(pTv);
		break;
	case OBJECT_WASHPOT:
		pSceneObj = new CWashPot;
		pSceneObj->SetPosition(ptPos);
		break;
	case OBJECT_SAFEBOX:
		pSceneObj = new CSafeBox;
		pSceneObj->SetPosition(ptPos);
		((CSafeBox*)pSceneObj)->SetRelativeBulletSupply(pBS);
		break;
	case OBJECT_DESK:
		pSceneObj = new CDesk;
		pSceneObj->SetPosition(ptPos);
		break;
	case OBJECT_DISK:
		pSceneObj = new CDisk;
		pSceneObj->SetPosition(ptPos);
		pDisk = (CDisk*)pSceneObj;
		break;
	case OBJECT_CLOSESTOOL:
		pSceneObj = new CClosestool;
		pSceneObj->SetPosition(ptPos);
		((CClosestool*)pSceneObj)->SetRelativeDisk(pDisk);
		break;
	case OBJECT_BED:
		pSceneObj = new CBed;
		pSceneObj->SetPosition(ptPos);
		break;
	case OBJECT_ROADSIGN:
		pSceneObj = new CRoadSign;
		pSceneObj->SetPosition(ptPos);
		break;
	case OBJECT_TREE:
		pSceneObj = new CTree;
		pSceneObj->SetPosition(ptPos);
		break;
	case OBJECT_CLOUD:
		pSceneObj = new CCloud;
		pSceneObj->SetPosition(ptPos);
		((CCloud*)pSceneObj)->SetRainFlag(iWidth);
		break;
	case OBJECT_GRASS:
		pSceneObj = new CGrass;
		pSceneObj->SetPosition(ptPos);
		break;
	case OBJECT_CUTDOWNTREE:
		pSceneObj = new CCutDownTree;
		pSceneObj->SetPosition(ptPos);
		break;
	case OBJECT_DEADTREE:
		pSceneObj = new CDeadTree;
		pSceneObj->SetPosition(ptPos);
		break;
	case OBJECT_SMALLCAR:
		pSceneObj = new CSmallCar;
		pSceneObj->SetPosition(ptPos);
		((CCar*)pSceneObj)->SetKey(iWidth);
		break;
	case OBJECT_KEY:
		pSceneObj = new CKey;
		pSceneObj->SetPosition(ptPos);
		((CKey*)pSceneObj)->SetKey(iWidth);
		((CKey*)pSceneObj)->SetAbleToShootOnFlag((bool)iHeigth);
		break;
	case OBJECT_PAPER:
		pSceneObj = new CPaper;
		pSceneObj->SetPosition(ptPos);
		((CPaper*)pSceneObj)->SetIndex(iWidth);
		break;
	case OBJECT_HOUSE1:
		pSceneObj = new CHouse1;
		pSceneObj->SetPosition(ptPos);
		pSceneObj->SetWidth(iWidth);
		pSceneObj->SetHeigth(iHeigth);
		((CHouse1*)pSceneObj)->SetHouseIndex(*((int*)pVoid));
		break;
	case OBJECT_BIKE:
		pSceneObj = new CBike;
		pSceneObj->SetPosition(ptPos);
		((CBike*)pSceneObj)->SetBikeKind(OBJECT_BIKE,iWidth,iHeigth);
		break;
	case OBJECT_BUIDING:
		pSceneObj = new CBuiding;
		pSceneObj->SetPosition(ptPos);
		break;
	case OBJECT_ROOM_DOOR:
	case OBJECT_ROADDIRECTLIGHT:
		if (id == OBJECT_ROOM_DOOR)
			pSceneObj = new CRoomDoor;
		else
			pSceneObj = new CRoadDirectLight;
		pSceneObj->SetPosition(ptPos);
		pSceneObj->SetWidth(iWidth);
		pSceneObj->SetHeigth(iHeigth);
		DoorParam = *((DOORPARAM*)pVoid);
		((CDoor*)pSceneObj)->SetDoorIndex(DoorParam.iDoorIndex);
		((CDoor*)pSceneObj)->SetKey(DoorParam.iKey);
		((CDoor*)pSceneObj)->SetMapIndexTo(DoorParam.iToMapIndex);
		((CDoor*)pSceneObj)->SetDoorType(DoorParam.iDoorType);
		break;
	case OBJECT_LUADEF:
		pSceneObj = new CLuaDefObj((char*)pVoid, iWidth, iHeigth);
		pSceneObj->SetPosition(ptPos);
		break;
	default:
		break;
	}

	m_vecMap[m_iMapNodeNum]->AddSceneObj(pSceneObj);
}

void CStage::GetCurMapDead(std::vector<CDead*> &vecDead)
{
	m_vecMap[m_iCurIndex]->GetDead(vecDead);
}

void CStage::GetCurMapSceneObj(std::vector<CSceneObject*> &vecSceneObj)
{
	m_vecMap[m_iCurIndex]->GetSceneObj(vecSceneObj);
}

void CStage::GetCurMapWeapon(std::vector<CWeapon*> &vecWeapon)
{
	m_vecMap[m_iCurIndex]->GetWeapon(vecWeapon);
}

RECT CStage::GetCurMapSize() const
{
	return m_vecMap[m_iCurIndex]->GetSize();
}

CDoor* CStage::FoundRelativeDoor(int iDoorIndex)
{
	return m_vecMap[m_iCurIndex]->FoundRelativeDoor(iDoorIndex);
}

void CStage::SetCurMapNewWeapon(CWeapon *pOld,CWeapon *pNew)
{
	m_vecMap[m_iCurIndex]->SetNewWeapon(pOld,pNew);
}

void CStage::ClearAllDead()
{
	for (MAPITER iter = m_vecMap.begin();
		iter != m_vecMap.end();++iter)
		(*iter)->ClearAllDead();
}

void CStage::ClearAllSceneObj()
{
	for (MAPITER iter = m_vecMap.begin();
		iter != m_vecMap.end();++iter)
		(*iter)->ClearAllSceneObj();
}

void CStage::ClearAllWeapon()
{
	for (MAPITER iter = m_vecMap.begin();
		iter != m_vecMap.end();++iter)
		(*iter)->ClearAllWeapon();
}