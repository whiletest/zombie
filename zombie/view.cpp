#include "stdafx.h"
#include "resource.h"


CZombieView::CZombieView():
						   m_bIsInitData(false),
						   m_pSelectBKG(NULL),
						   m_pTemSceneObj(NULL),
						   m_iMssg(MSG_END_SHOW),
						   m_iGameState(GAMESTATE_SELECT)
{
}

CZombieView::CZombieView(HINSTANCE hInstance,HWND hWnd):
									m_hInstance(hInstance),
									
									m_hWnd(hWnd),
									m_bIsInitData(false),
									m_pSelectBKG(NULL),
									m_pTemSceneObj(NULL),
									m_iMssg(MSG_END_SHOW),
									m_iGameState(GAMESTATE_SELECT)
{
}

CZombieView::~CZombieView()
{
	if (m_hMemDc)
		DeleteDC(m_hMemDc);
	if (m_hBmpBKG)
		DeleteObject(m_hBmpBKG);
}


void CZombieView::SetMemDc(HDC hdc)
{
	if (m_hMemDc)
		DeleteDC(m_hMemDc);
	m_hMemDc = CreateCompatibleDC(hdc);
}

//void CZombieView::SelectBkgBmpToScreen(HDC hdc)
//{
//	BitBlt(hdc,0,0,m_rcClient.right,m_rcClient.bottom,
//		m_hMemDc,0,0,SRCCOPY);
//	DeleteDC(m_hMemDc);
//	DeleteObject(m_hBmpBKG);
//}

//void CZombieView::AddStartBmp(HINSTANCE hInatance,bool flag)
//{
//	int iStartID;
//	if (flag)
//		iStartID = IDB_START;
//	else 
//		iStartID = IDB_STARTSMALL;
//	HDC hMemDc = CreateCompatibleDC(m_hMemDc);
//	HBITMAP hbmpStart = LoadBitmap(hInatance,MAKEINTRESOURCE(iStartID));
//	SelectObject(hMemDc,hbmpStart);
//	TransparentBlt(m_hMemDc,m_rcClient.right/2-100,m_rcClient.bottom-66,
//		200,56,hMemDc,0,0,200,56,RGB(255,255,255));
//	DeleteDC(hMemDc);
//	DeleteObject(hbmpStart);
//}

//void CZombieView::AddOperateBmp(HINSTANCE hInstance,bool flag)
//{
//	int iOperateID;
//	if (flag)
//		iOperateID = IDB_OPERATE;
//	else 
//		iOperateID = IDB_OPERATESMALL;
//	HDC hMemDc = CreateCompatibleDC(m_hMemDc);
//	HBITMAP hbmpStart = LoadBitmap(hInstance,MAKEINTRESOURCE(iOperateID));
//	SelectObject(hMemDc,hbmpStart);
//	TransparentBlt(m_hMemDc,100,m_rcClient.bottom-66,
//		200,56,hMemDc,0,0,200,56,RGB(255,255,255));
//	DeleteDC(hMemDc);
//	DeleteObject(hbmpStart);
//}

//void CZombieView::AddSelectBkgBmp(HINSTANCE hInstance, HDC hdc)
//{
//	if (m_hMemDc)
//		DeleteDC(m_hMemDc);
//	m_hMemDc = CreateCompatibleDC(hdc);
//	if (m_hBmpBKG)
//		DeleteObject(m_hBmpBKG);
//	m_hBmpBKG = CreateCompatibleBitmap(hdc,m_rcClient.right,m_rcClient.bottom);
//	SelectObject(m_hMemDc,m_hBmpBKG);
//
//	HDC hMemDc = CreateCompatibleDC(hdc);
//	HBITMAP hbmpBkg = LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_INITIALIZE));
//	SelectObject(hMemDc,hbmpBkg);
//	StretchBlt(m_hMemDc,0,0,m_rcClient.right,m_rcClient.bottom,
//		hMemDc,0,0,500,650,SRCCOPY);
//	DeleteDC(hMemDc);
//	DeleteObject(hbmpBkg);
//}

void CZombieView::InitialSelectBKG()
{
	if (!m_pSelectBKG)
	{
		m_pSelectBKG = new CInitialSelectBKG;
		m_pSelectBKG->SetClientSize(m_rcClient);
	}
}

void CZombieView::ShowSelectBKG(HDC hdc)
{
	InitialSelectBKG();

	if (m_hMemDc)
		DeleteDC(m_hMemDc);
	m_hMemDc = CreateCompatibleDC(hdc);
	if (m_hBmpBKG)
		DeleteObject(m_hBmpBKG);
	m_hBmpBKG = CreateCompatibleBitmap(hdc,m_rcClient.right,m_rcClient.bottom);
	SelectObject(m_hMemDc,m_hBmpBKG);

	m_pSelectBKG->ShowSelectBKG(m_hInstance,m_hMemDc);
	
	BitBlt(hdc,0,0,m_rcClient.right,m_rcClient.bottom,
		m_hMemDc,0,0,SRCCOPY);

	DeleteDC(m_hMemDc);
	DeleteObject(m_hBmpBKG);
}

void CZombieView::IsMouseOnBtnBKG(POINT &ptMouse)
{
	m_pSelectBKG->IsOnBtn(ptMouse);
}

void CZombieView::IsClickOnBtnBKG()
{
	int iBkgBtnId = m_pSelectBKG->IsClickOnBtn();
	int iBkgId = m_pSelectBKG->GetBKGId();
	switch (iBkgBtnId)
	{
	case FALSE:
			break;
	case IDB_EQUIPBIG:
		if (iBkgId == IDB_PLAYERBAGBKG)
		{
			((CSelectPlayerBagBkg*)m_pSelectBKG)->EquipPlayer();
		}
		break;
	case IDB_GETBIG:
		if (iBkgId == IDB_MP5BKG)
		{
			CMP5 *pMp5 = new CMP5;
			POINT ptPos = m_Player.GetCurPos();
			ptPos.y -= pMp5->GetHeigth();
			pMp5->SetPosOnGround(ptPos);
			m_vecWeaponOnGround.push_back(pMp5);
			m_Stage.AddWeaponToCurMap(pMp5);
		}

		m_iGameState = GAMESTATE_PLAY;
		if (m_pSelectBKG)
			delete m_pSelectBKG;
		m_pSelectBKG = NULL;
		SendMessage(m_hWnd,WM_SIZE,SIZE_RESTORED,0);
		break;
	case IDB_DROPBIG:
		if (iBkgId == IDB_PLAYERBAGBKG)
		{
			CSceneObject *pObjDroped;
			pObjDroped = ((CSelectPlayerBagBkg*)m_pSelectBKG)->DropObjFromPlayerBag();
			m_vecSceneObj.push_back(pObjDroped);
			m_Stage.AddObjToCurMap(pObjDroped);
		}
		break;
	case IDB_START:
		if (iBkgId == IDB_GAMEMACHINEBKG)
		{
			SetTimer(m_hWnd,TIMER_GMAEMACHINEROLL,1000,NULL);
		}
		else
		{
			m_iGameState = GAMESTATE_PLAY;
			PassStage();
			delete m_pSelectBKG;
			m_pSelectBKG = NULL;
			SendMessage(m_hWnd,WM_SIZE,SIZE_RESTORED,0);
		}
		break;
	case IDB_OPERATE:
		m_iGameState = GAMESTATE_SELECT;
		if (m_pSelectBKG)
			delete m_pSelectBKG;
		m_pSelectBKG = new CSelectBKG1;
		m_pSelectBKG->SetBKGId(IDB_OPERATEBKG);
		InvalidateRect(m_hWnd,&m_rcClient,FALSE);
		break;
	case IDB_OK:
		if ( iBkgId== IDB_OPERATEBKG )
			m_iGameState = GAMESTATE_SELECT;
		else
			m_iGameState = GAMESTATE_PLAY;

		if (   iBkgId == IDB_TVSNOWBKG1
			|| iBkgId == IDB_TVSNOWBKG2)
			KillTimer(m_hWnd,TIMER_TVSNOWRATE);

		if (   iBkgId == IDB_SELECTBKG4 
			|| iBkgId == IDB_PASSSTAGE1BKG
			|| iBkgId == IDB_PASSSTAGE3BKG)
		{
			delete m_pSelectBKG;
			m_pSelectBKG = NULL;
			PassStage();
		}

		if (m_pSelectBKG)
			delete m_pSelectBKG;
		m_pSelectBKG = NULL;
		SendMessage(m_hWnd,WM_SIZE,SIZE_RESTORED,0);
		break;
	case IDB_BIGEXITBKG:
		if (iBkgId == IDB_GAMEMACHINEBKG)
		{
			KillTimer(m_hWnd,TIMER_GMAEMACHINEROLL);
		}

		m_iGameState = GAMESTATE_PLAY;
		if (m_pSelectBKG)
			delete m_pSelectBKG;
		m_pSelectBKG = NULL;
		SendMessage(m_hWnd,WM_SIZE,SIZE_RESTORED,0);
		break;
	case PASSWORD_RIGHT: ///through down 密码正确时
		if (m_pTemSceneObj)
			((CSafeBox*)m_pTemSceneObj)->OpenSafeBox();
		m_pTemSceneObj = NULL;
	case PASSWORD_ERROR:
		m_iGameState = GAMESTATE_PLAY;
		if (m_pSelectBKG)
			delete m_pSelectBKG;
		m_pSelectBKG = NULL;
		SendMessage(m_hWnd,WM_SIZE,SIZE_RESTORED,0);
		break;
	default:
		break;
	}
}

int CZombieView::SelBkg4_MoveToNextItem()
{
	return ((CSelectBKG4*)m_pSelectBKG)->GameMachineMoveToNextItem();
}

void CZombieView::DrawPlyerMessage()
{
	m_Player.DrawMessage(m_hInstance,m_hMemDc,m_ptClientOrgOnMap);
}

void CZombieView::InitialBackGround(HDC hdc)
{
	if (m_hMemDc)
		DeleteDC(m_hMemDc);
	m_hMemDc = CreateCompatibleDC(hdc);
	
	if (!m_bIsInitData)
	{
		InitializeBKGObject(); //加载所有数据

		m_bIsInitData = true; //标识数据已初始化
	}

	if (m_hBmpBKG)
		DeleteObject(m_hBmpBKG);
	m_hBmpBKG = CreateCompatibleBitmap(hdc,m_rcMap.right,m_rcMap.bottom);
	SelectObject(m_hMemDc,m_hBmpBKG);
	FillRect(m_hMemDc,&m_rcMap,(HBRUSH)GetStockObject(WHITE_BRUSH));
	//先画出物品
	DrawSceneObject();
	//画出武器
	DrawWeaponOnGround();
}

bool CZombieView::InitializeBKGObject()
{
	m_rcMap = m_Stage.GetCurMapSize();
	m_Stage.GetCurMapDead(m_vecDead);
	m_Stage.GetCurMapSceneObj(m_vecSceneObj);
	m_Stage.GetCurMapWeapon(m_vecWeaponOnGround);
	return true;
}

void CZombieView::SomethingHappen()
{
	int id;
	int iMapIndexTo;
	POINT ptPlayerPos = m_Player.GetCurPos();
	ptPlayerPos.y -= m_Player.GetHeight()/2;
	POINT ptObjPos;
	RECT rcObject;
	RECT rcPlayer;
	vector<CSceneObject*> vecTemDynamicObj;
	static vector<CSceneObject*> vecPrevDynamicObj;
	for (SCENEOBJITER iter = m_vecSceneObj.begin();
		iter != m_vecSceneObj.end();++iter)
	{
		id = (*iter)->GetId();
		switch (id)
		{
		case OBJECT_ROOM_DOOR:
		case OBJECT_ROADDIRECTLIGHT:
			(*iter)->GetObjRect(rcObject);
			if (PtInRect(&rcObject,ptPlayerPos))
			{
				if ( !m_Player.IsUseObject(OBJECT_KEY,((CDoor*)(*iter))->GetKey()) )
				{
					m_iMssg = MSG_NO_KEY;
					SetTimer(m_hWnd,TIMER_ENDSHOWMSSG,1000,NULL);
					return;
				}
				iMapIndexTo = ((CDoor*)(*iter))->Open();
				m_Stage.SetCurMapIndex(iMapIndexTo);
				int iDoorIndex = ((CDoor*)(*iter))->GetDoorIndex();
				CDoor *pDoor = m_Stage.FoundRelativeDoor(m_Stage.GetDoorIndexTable(iDoorIndex));
				if (pDoor)
				{
					ptPlayerPos = pDoor->GetPlayerPos();
					m_Player.SetHoriPos(ptPlayerPos.x);
					m_Player.SetVertPos(ptPlayerPos.y);
					pDoor->GetClientOrgPosOnMap(m_ptClientOrgOnMap,m_rcClient);
					pDoor->PlayDoorOpenSound();
				}

				//删除动态产生的物体
				for (SCENEOBJITER iter = m_vecDynamicObj.begin();
					iter != m_vecDynamicObj.end();++iter)
					delete *iter;
				m_vecDynamicObj.clear();

				m_bIsInitData = false; //初始化数据标识设置为0，重新载入地图
			}
			break;
		case OBJECT_KEY:
		case OBJECT_COIN:
		case OBJECT_MASK1:
		case OBJECT_MASK2:
		case OBJECT_BLOODSUPPLY:
		case OBJECT_SPIDERBLOOD:
			ptObjPos = (*iter)->GetPosition();
			ptObjPos.x += (*iter)->GetWidth()/2;
			m_Player.GetPlayerRect(rcPlayer);
			if (PtInRect(&rcPlayer,ptObjPos))
			{
				m_Player.GetUsefulObject(*iter);
				m_Stage.EraseObjFromCurMap(*iter);
				m_vecSceneObj.erase(iter);

				if (id == OBJECT_KEY)
					m_iMssg = MSG_GET_KEY;
				else if (id == OBJECT_COIN)
					m_iMssg = MSG_GET_COIN;
				else if (id == OBJECT_MASK1
					   ||id == OBJECT_MASK2)
					m_iMssg = MSG_GET_MASK;
				else
					m_iMssg = MSG_GET_OBJ;

				SetTimer(m_hWnd,TIMER_ENDSHOWMSSG,1000,NULL);

				return;
			}
			break;
		case OBJECT_DISK:
			ptObjPos = (*iter)->GetPosition();
			ptObjPos.x += (*iter)->GetWidth()/2;
			m_Player.GetPlayerRect(rcPlayer);
			if (PtInRect(&rcPlayer,ptObjPos))
			{
				m_Player.GetUsefulObject(*iter);
				m_Stage.EraseObjFromCurMap(*iter);
				m_vecSceneObj.erase(iter);

				m_iMssg = MSG_GET_DISK;
				SetTimer(m_hWnd,TIMER_ENDSHOWMSSG,1000,NULL);

				return;
			}
			break;
		case OBJECT_STICK:
			ptObjPos = (*iter)->GetPosition();
			ptObjPos.x += (*iter)->GetWidth()/2;
			m_Player.GetPlayerRect(rcPlayer);
			if (PtInRect(&rcPlayer,ptObjPos))
			{
				m_Player.GetUsefulObject(*iter);
				m_Stage.EraseObjFromCurMap(*iter);
				m_vecSceneObj.erase(iter);

				m_iMssg = MSG_GET_STICK;
				SetTimer(m_hWnd,TIMER_ENDSHOWMSSG,1000,NULL);

				return;
			}
			break;
		case OBJECT_SMALLCAR:
			(*iter)->GetObjRect(rcObject);
			if ( PtInRect(&rcObject,ptPlayerPos) )
			{
				if ( !m_Player.IsUseObject(OBJECT_KEY,
					  ((CCar*)(*iter))->GetKeyIndex()) )
				{
					m_iMssg = MSG_NO_KEY;
					SetTimer(m_hWnd,TIMER_ENDSHOWMSSG,1000,NULL);
					return;
				}
				else
				{
					m_iGameState = GAMESTATE_SELECT;

					if (m_pSelectBKG)
						delete m_pSelectBKG;
					m_pSelectBKG = new CSelectBKG1;
					m_pSelectBKG->SetBKGId(IDB_SELECTBKG4);

					KillTimer(m_hWnd,GAME_UPDATE);
					InvalidateRect(m_hWnd,&m_rcClient,FALSE);
				}
			}
			break;
		case OBJECT_GAMEMACHINE:
			ptPlayerPos = m_Player.GetCurPos();
			ptPlayerPos.y -= m_Player.GetHeight()/2;
			(*iter)->GetObjRect(rcObject);
			if (PtInRect(&rcObject,ptPlayerPos))
			{
				m_iGameState = GAMESTATE_SELECT;
				KillTimer(m_hWnd,GAME_UPDATE);
				InvalidateRect(m_hWnd,NULL,FALSE);

				if (m_pSelectBKG)
					delete m_pSelectBKG;
				m_pSelectBKG = new CSelectBKG4(&m_Player);
				m_pSelectBKG->PlaySelectBkgSound();
			}
			break;
		case OBJECT_GAMEMACHINE1:
		case OBJECT_GAMEMACHINE2:
			ptPlayerPos = m_Player.GetCurPos();
			ptPlayerPos.y -= m_Player.GetHeight()/2;
			(*iter)->GetObjRect(rcObject);
			if (PtInRect(&rcObject,ptPlayerPos))
			{
				m_iMssg = MSG_MACHINE_BROKEN;
				SetTimer(m_hWnd,TIMER_ENDSHOWMSSG,1000,NULL);
			}
			break;
		case OBJECT_PAPER:
			ptObjPos = (*iter)->GetPosition();
			ptObjPos.x += (*iter)->GetWidth()/2;
			m_Player.GetPlayerRect(rcPlayer);
			if ( PtInRect(&rcPlayer,ptObjPos) )
			{
				m_iGameState = GAMESTATE_SELECT;
				KillTimer(m_hWnd,GAME_UPDATE);
				InvalidateRect(m_hWnd,&m_rcClient,FALSE);

				if (m_pSelectBKG)
					delete m_pSelectBKG;
				m_pSelectBKG = new CSelectBKG1;
				m_pSelectBKG->PlaySelectBkgSound();
				switch ( ((CPaper*)(*iter))->GetIndex() )
				{
				case 1:
					m_pSelectBKG->SetBKGId(IDB_SELECTBKG1);
					break;
				case 2:
					m_pSelectBKG->SetBKGId(IDB_SELECTBKG2);
					break;
				case 3:
					m_pSelectBKG->SetBKGId(IDB_SELECTBKG3);
					break;
				case 4:
					m_pSelectBKG->SetBKGId(IDB_SELECTBKG5);
					break;
				case 5:
					m_pSelectBKG->SetBKGId(IDB_STAGE3_PAPER1);
					break;
				case 6:
					m_pSelectBKG->SetBKGId(IDB_CALENDAR);
					break;
				case 7:
					m_pSelectBKG->SetBKGId(IDB_PAPERBKG2);
					break;
				case 8:
					m_pSelectBKG->SetBKGId(IDB_PAPERBKG3);
					break;
				case 9:
					delete m_pSelectBKG;
					m_pSelectBKG = new CSelectBKG5(&m_Player);
					break;
				case 10:
					m_pSelectBKG->SetBKGId(IDB_STAGE3_PAPER2);
					break;
				default:
					break;
				}
				
				return;
			}
			break;
		case OBJECT_CABINET:
			(*iter)->GetObjRect(rcObject);
			if (PtInRect(&rcObject,ptPlayerPos))
			{
				CWeapon *pBow = 0;
				if ( ((CCabinet*)(*iter))->UseCabinet(&pBow) ) 
				{
					m_vecWeaponOnGround.push_back(pBow);
					m_Stage.AddWeaponToCurMap(pBow);
				}
			}
			break;
		case OBJECT_BULLETSUPPLY:
			ptObjPos = (*iter)->GetPosition();
			m_Player.GetPlayerRect(rcPlayer);
			if ( PtInRect(&rcPlayer,ptObjPos) )
			{
				int WeaponKind = ((CBulletSupply*)(*iter))->GetWeaponKind();
				int BulletNum = ((CBulletSupply*)(*iter))->GetBulletNum();
				if ( m_Player.GetBulletSupply(WeaponKind,BulletNum) )
				{
					m_Stage.EraseObjFromCurMap(*iter);
					delete *iter;
					m_vecSceneObj.erase(iter);
					m_iMssg = MSG_GET_BULLETSUPPLY;
					SetTimer(m_hWnd,TIMER_ENDSHOWMSSG,1000,NULL);
					return;
				}
				m_iMssg = MSG_NO_WEAPON;
				SetTimer(m_hWnd,TIMER_ENDSHOWMSSG,1000,NULL);
				return;
			}
			break;
		case OBJECT_CLOSESTOOL:
			(*iter)->GetObjRect(rcObject);
			if ( PtInRect(&rcObject,ptPlayerPos) )
			{
				//already find disk
				if ( ((CClosestool*)(*iter))->IsDiskFinded() )
				{
					m_iMssg = MSG_NO_NEED_USE_CLOSESTOOL;
					SetTimer(m_hWnd,TIMER_ENDSHOWMSSG,1000,NULL);
					return;
				}

				//not find disk
				if ( m_Player.IsUseObject(OBJECT_STICK,-1) )
					((CClosestool*)(*iter))->FindDisk();
				else
				{
					m_iGameState = GAMESTATE_SELECT;
					KillTimer(m_hWnd,GAME_UPDATE);
					InvalidateRect(m_hWnd,&m_rcClient,FALSE);

					if(m_pSelectBKG)
						delete m_pSelectBKG;
					m_pSelectBKG = new CSelectBKG1;
					m_pSelectBKG->SetBKGId(IDB_CLOSESTOOLBKG);
				}

				return;
			}
			break;
		case OBJECT_BED:
			(*iter)->GetObjRect(rcObject);
			if ( PtInRect(&rcObject,ptPlayerPos) )
			{
				m_iMssg = MSG_BED;
				SetTimer(m_hWnd,TIMER_ENDSHOWMSSG,1000,NULL);
				return;
			}
			break;
		case OBJECT_TV:
			(*iter)->GetObjRect(rcObject);
			if ( PtInRect(&rcObject,ptPlayerPos) )
			{
				if ( !((CTv*)(*iter))->GetPowerState() )
				{
					m_iMssg = MSG_NO_POWER;
					SetTimer(m_hWnd,TIMER_ENDSHOWMSSG,1000,NULL);
					return;
				}

				if ( ((CTv*)(*iter))->GetDiskState() )
				{
					m_iGameState = GAMESTATE_SELECT;
					KillTimer(m_hWnd,GAME_UPDATE);
					InvalidateRect(m_hWnd,&m_rcClient,FALSE);

					if(m_pSelectBKG)
						delete m_pSelectBKG;
					m_pSelectBKG = new CSelectBKG1;
					m_pSelectBKG->SetBKGId(IDB_PAPERBKG1);
				}
				else
				{
					if ( m_Player.IsUseObject(OBJECT_DISK,-1) )
						((CTv*)(*iter))->PutInDisk();
					else
					{
						m_iGameState = GAMESTATE_SELECT;
						KillTimer(m_hWnd,GAME_UPDATE);
						InvalidateRect(m_hWnd,&m_rcClient,FALSE);

						if(m_pSelectBKG)
							delete m_pSelectBKG;
						m_pSelectBKG = new CSelectBKG1;
						m_pSelectBKG->SetBKGId(IDB_TVSNOWBKG1);
						SetTimer(m_hWnd,TIMER_TVSNOWRATE,100,NULL);
					}
				}
				return;
			}
			break;
		case OBJECT_SOCKET:
			(*iter)->GetObjRect(rcObject);
			if ( PtInRect(&rcObject,ptPlayerPos) )
			{
				((CSocket*)(*iter))->UseSocket();
			}
			break;
		case OBJECT_SAFEBOX:
			ptObjPos = (*iter)->GetPosition();
			ptObjPos.x += (*iter)->GetWidth()/2;
			m_Player.GetPlayerRect(rcPlayer);
			if (PtInRect(&rcPlayer,ptObjPos))
			{
				if ( ((CSafeBox*)(*iter))->GetSate() )
				{
					m_iMssg = MSG_OPENED;
					SetTimer(m_hWnd,TIMER_ENDSHOWMSSG,1000,NULL);
					return;
				}

				m_pTemSceneObj = *iter;

				m_iGameState = GAMESTATE_SELECT;
				KillTimer(m_hWnd,GAME_UPDATE);
				InvalidateRect(m_hWnd,&m_rcClient,FALSE);

				if (m_pSelectBKG)
					delete m_pSelectBKG;
				m_pSelectBKG = new CSelectBKG2;
			}
			break;
		case OBJECT_MESSIPAPER:
			ptObjPos = (*iter)->GetPosition();
			ptObjPos.x += (*iter)->GetWidth()/2;
			ptObjPos.y += (*iter)->GetHeigth()/2;
			m_Player.GetPlayerRect(rcPlayer);
			if ( PtInRect(&rcPlayer,ptObjPos) )
			{
				m_iGameState = GAMESTATE_SELECT;
				KillTimer(m_hWnd,GAME_UPDATE);
				InvalidateRect(m_hWnd,&m_rcClient,FALSE);

				if (m_pSelectBKG)
					delete m_pSelectBKG;
				m_pSelectBKG = new CSelectBKG1;
				m_pSelectBKG->SetBKGId(IDB_MESSIBKG);
				m_pSelectBKG->PlaySelectBkgSound();
			}
			break;
		case OBJECT_FOOTBALL:
			ptObjPos = (*iter)->GetPosition();
			m_Player.GetPlayerRect(rcPlayer);
			if ( PtInRect(&rcPlayer,ptObjPos) )
			{
				m_iMssg = MSG_FOOTBALL;
				SetTimer(m_hWnd,TIMER_ENDSHOWMSSG,1000,NULL);
				return;
			}
			break;
		case OBJECT_HOMEGATE:
			(*iter)->GetObjRect(rcObject);
			if (PtInRect(&rcObject,ptPlayerPos))
			{
				m_iGameState = GAMESTATE_SELECT;
				KillTimer(m_hWnd,GAME_UPDATE);
				InvalidateRect(m_hWnd,&m_rcClient,FALSE);

				if (m_pSelectBKG)
					delete m_pSelectBKG;
				m_pSelectBKG = new CSelectBKG1;
				m_pSelectBKG->SetBKGId(IDB_PASSSTAGE1BKG);
			}
			break;
		case OBJECT_WINDOW1:
			(*iter)->GetObjRect(rcObject);
			if (PtInRect(&rcObject,ptPlayerPos))
			{
				int ws;
				ws = ((CWindow1*)(*iter))->getWindowState();
				if (ws == CWindow1::ws_ok)
				{
					if (m_Player.IsUseObject(OBJECT_SPIDERBLOOD))
						((CWindow1*)(*iter))->WindowCrack();
				}
				else if (ws == CWindow1::ws_broken)
				{
					m_iGameState = GAMESTATE_SELECT;

					if (m_pSelectBKG)
						delete m_pSelectBKG;
					m_pSelectBKG = new CSelectBKG1;
					m_pSelectBKG->SetBKGId(IDB_PASSSTAGE3BKG);

					KillTimer(m_hWnd,GAME_UPDATE);
					InvalidateRect(m_hWnd,&m_rcClient,FALSE);
				}
			}
			break;
		default:
			break;
		}
	}
}

void CZombieView::ShowMssg()
{
	static POINT ptPos; 
	TCHAR szContent[20]; 
	switch (m_iMssg)
	{
	case 0:
		break;
	case MSG_NO_KEY:
	case MSG_GET_KEY:
	case MSG_GET_COIN:
	case MSG_GET_BULLETSUPPLY:
	case MSG_MACHINE_BROKEN:
	case MSG_GET_MASK:
	case MSG_GET_OBJ:
		ptPos = m_Player.GetCurPos();
		ptPos.y -= (m_Player.GetHeight()+15);
		ptPos.x -= m_Player.GetWidth();

		if (m_iMssg == MSG_GET_KEY)
			lstrcpy(szContent,TEXT("得到了钥匙"));
		else if (m_iMssg == MSG_NO_KEY)
			lstrcpy(szContent,TEXT("没有钥匙，不能打开"));
		else if (m_iMssg == MSG_GET_COIN)
			lstrcpy(szContent,TEXT("得到了游戏币"));
		else if (m_iMssg == MSG_GET_BULLETSUPPLY)
			lstrcpy(szContent,TEXT("得到了子弹"));
		else if (m_iMssg == MSG_MACHINE_BROKEN)
			lstrcpy(szContent,TEXT("机器坏了,无法使用"));
		else if (m_iMssg == MSG_GET_MASK)
			lstrcpy(szContent,TEXT("获得了面具"));
		else if (m_iMssg == MSG_GET_OBJ)
			lstrcpy(szContent,TEXT("您拾取了物品,可在背包查看!"));

		TextOut(m_hMemDc,ptPos.x,ptPos.y,szContent,lstrlen(szContent));
		break;
	case MSG_NO_NEED_USE_CLOSESTOOL:
		ptPos = m_Player.GetCurPos();
		ptPos.y -= (m_Player.GetHeight()+15);
		ptPos.x -= m_Player.GetWidth();
		TextOut(m_hMemDc,ptPos.x,ptPos.y,TEXT("现在没有时间上大号"),9);
		break;
	case MSG_BED:
		ptPos = m_Player.GetCurPos();
		ptPos.y -= (m_Player.GetHeight()+15);
		ptPos.x -= m_Player.GetWidth();
		TextOut(m_hMemDc,ptPos.x,ptPos.y,TEXT("现在睡不着"),5);
		break;
	case MSG_NO_POWER:
		ptPos = m_Player.GetCurPos();
		ptPos.y -= (m_Player.GetHeight()+15);
		ptPos.x -= m_Player.GetWidth();
		TextOut(m_hMemDc,ptPos.x,ptPos.y,TEXT("没有电，打不开"),7);
		break;
	case MSG_NO_DISK:
		ptPos = m_Player.GetCurPos();
		ptPos.y -= (m_Player.GetHeight()+15);
		ptPos.x -= m_Player.GetWidth();
		TextOut(m_hMemDc,ptPos.x,ptPos.y,TEXT("请放入录像带"),6);
		break;
	case MSG_GET_DISK:
		ptPos = m_Player.GetCurPos();
		ptPos.y -= (m_Player.GetHeight()+15);
		ptPos.x -= m_Player.GetWidth();
		TextOut(m_hMemDc,ptPos.x,ptPos.y,TEXT("获得了录像带"),6);
		break;
	case MSG_OPENED:
		ptPos = m_Player.GetCurPos();
		ptPos.y -= (m_Player.GetHeight()+15);
		ptPos.x -= m_Player.GetWidth();
		TextOut(m_hMemDc,ptPos.x,ptPos.y,TEXT("已经打开了!"),6);
		break;
	case MSG_NO_WEAPON:
		ptPos = m_Player.GetCurPos();
		ptPos.y -= (m_Player.GetHeight()+15);
		ptPos.x -= m_Player.GetWidth();
		TextOut(m_hMemDc,ptPos.x,ptPos.y,TEXT("你还没有手枪"),6);
		break;
	case MSG_FOOTBALL:
		ptPos = m_Player.GetCurPos();
		ptPos.y -= (m_Player.GetHeight()+15);
		ptPos.x -= m_Player.GetWidth();
		TextOut(m_hMemDc,ptPos.x,ptPos.y,TEXT("等会儿回来再踢球吧"),9);
		break;
	case MSG_GET_STICK:
		ptPos = m_Player.GetCurPos();
		ptPos.y -= (m_Player.GetHeight()+15);
		ptPos.x -= m_Player.GetWidth();
		TextOut(m_hMemDc,ptPos.x,ptPos.y,TEXT("获得了棍子"),5);
		break;
	default:
		break;
	}
}

void CZombieView::EndShowMssg()
{
	static bool bEndShow = false;
	if (bEndShow)
	{
		m_iMssg = MSG_END_SHOW;
		KillTimer(m_hWnd,TIMER_ENDSHOWMSSG);
	}
	bEndShow = !bEndShow;
}

void CZombieView::DrawPlayer()
{
	m_Player.DrawPerson(m_ptMousePosOnMap.x,m_ptMousePosOnMap.y,
		m_hMemDc,m_hInstance);
}

POINT CZombieView::GetPlayerPos() const
{
	return m_Player.GetCurPos();
}

void CZombieView::MemToScreen(HDC hdc)
{
	POINT ptPlayerPos = m_Player.GetCurPos(); 
	//背景水平移动
	MoveHoriBkg(ptPlayerPos);
	//背景竖直移动
	MoveVertBkg(ptPlayerPos);

	BitBlt(hdc,0,0,m_rcClient.right,m_rcClient.bottom,
		m_hMemDc,m_ptClientOrgOnMap.x,m_ptClientOrgOnMap.y,SRCCOPY);
}

bool CZombieView::MoveVertBkg(const POINT &ptPos)
{
	int iSubOnMap = ptPos.y - m_ptClientOrgOnMap.y;
	int iSubOnClient = m_rcClient.bottom - 80;
	int iSpeed = iSubOnMap - iSubOnClient;
	if (iSpeed != 0)
	{
		m_ptClientOrgOnMap.y += iSpeed;
		return true;
	}

	return false;
}

bool CZombieView::MoveHoriBkg(const POINT &ptPos)
{
	if (m_ptClientOrgOnMap.x >= 0
		&& m_ptClientOrgOnMap.x+m_rcClient.right <= m_rcMap.right)
	{
		switch (m_Player.GetHoriDirection())
		{
		case MOVE_RIGHT:
			if ( ptPos.x > m_ptClientOrgOnMap.x + m_rcClient.right/2 
				&& m_ptClientOrgOnMap.x != m_rcMap.right - m_rcClient.right)
			{
				m_ptClientOrgOnMap.x += m_Player.GetHoriSpeed();
				return true;
			}
			break;
		case MOVE_LEFT:
			if (m_ptClientOrgOnMap.x != 0
				&& ptPos.x < m_ptClientOrgOnMap.x + m_rcClient.right/2)
			{
				m_ptClientOrgOnMap.x -= m_Player.GetHoriSpeed();
				return true;
			}
			break;
		case MOVE_HORISTATIC:
		default:
			return false;
		}
	}
	else if (m_ptClientOrgOnMap.x < 0)
		m_ptClientOrgOnMap.x = 0;
	else
		m_ptClientOrgOnMap.x = m_rcMap.right - m_rcClient.right;
	return false;
}

void CZombieView::PlayerFire()
{
	m_Player.Fire();
}


int CZombieView::GetPlayerWeaponShootRate() const
{
	return m_Player.GetWeaponShootRate();
}


bool CZombieView::ChangePlayerDirection(UINT uiDirection)
{
	//add code here if want player 
	//can not change hori_direction in air
	return m_Player.ChangeDirection(uiDirection);
}

void CZombieView::MovePlayer()
{
	if ( m_Player.IsDead() )
	{
		KillTimer(m_hWnd,GAME_UPDATE);
		MessageBox(m_hWnd,TEXT("你阵亡了!!!"),TEXT("lose"),MB_OK);

		m_iGameState = GAMESTATE_SELECT;
		if (m_pSelectBKG)
			delete m_pSelectBKG;
		m_pSelectBKG = new CInitialSelectBKG;

		m_Stage.ReInitialStage();
		m_Stage.StageReduce();

		m_Player.ReInitialize();

		m_bIsInitData = false;

		SendMessage(m_hWnd,WM_SIZE,0,0);

		return;
	}

	IsPlayerOnGround();
	m_Player.Move(m_vecDead,m_vecSceneObj);
}

int CZombieView::IsPlayerOnGround()
{
	int iPlayerVertState = m_Player.GetVertDirection();
	if (iPlayerVertState != MOVE_UP)
	{
		POINT ptCurPos = m_Player.GetCurPos();
		int iPosState;
		for (vector<CSceneObject*>::iterator iter = m_vecSceneObj.begin();
			iter != m_vecSceneObj.end();++iter)
		{
			iPosState = (*iter)->IsOnObject(ptCurPos);
			if (iPosState != ON_NOTHING)
			{
				//太高落下掉血
				int curVertSpeed = m_Player.GetVertSpeed();
				if (curVertSpeed > 18)
					m_Player.LoseBlood(curVertSpeed*2);
				if ( iPosState != ON_WALL )
				{
					if (m_Player.ChangeDirection(MOVE_VERTSTATIC))
					{
						int iYPos = (*iter)->OnObjectWhere(ptCurPos);
						m_Player.SetVertPos(iYPos);
					}
					return iPosState;
				}
				else
					m_Player.SetHoriPos((*iter)->GetPosition().x);
			}
			else if (iPlayerVertState == MOVE_VERTSTATIC)
			{
				m_Player.ChangeDirection(MOVE_DOWN);
			}
		}
	}
	return ON_NOTHING;
}

int CZombieView::IsDeadOnGround(CDead *pDead)
{
	if (   pDead->GetVertState() == MOVE_VERTSTATIC
		&& pDead->IsDied() )
		return ON_NOTHING;

	typedef vector<CSceneObject*>::iterator SceneObjIter;
	int iVertState;
	iVertState = pDead->GetVertState();
	if (iVertState != MOVE_UP)
	{
		POINT ptPos = pDead->GetCurPos();
		int iOnWhat;
		for (SceneObjIter iter = m_vecSceneObj.begin();
			iter != m_vecSceneObj.end();++iter)
		{
			iOnWhat = (*iter)->IsOnObject(ptPos);
			if (iOnWhat != ON_NOTHING)
			{
				if (pDead->ChangeVertState(MOVE_VERTSTATIC))
					pDead->SetVertPos((*iter)->GetPosition().y);
				return iOnWhat;
			}
			else if (iVertState == MOVE_VERTSTATIC)
			{
				pDead->ChangeVertState(MOVE_DOWN);
			}
		}
	}
	return ON_NOTHING;
}

void CZombieView::IsObjectOnObject()
{
	int iOnWhat = ON_NOTHING;
	POINT ptDynamicObjPos;
	for (SCENEOBJITER DynamicIter = m_vecDynamicObj.begin();
		DynamicIter != m_vecDynamicObj.end();)
	{
		ptDynamicObjPos = (*DynamicIter)->GetPosition();
		for (SCENEOBJITER ObjIter = m_vecSceneObj.begin();
			ObjIter != m_vecSceneObj.end();++ObjIter)
		{
			iOnWhat = (*ObjIter)->IsOnObject(ptDynamicObjPos);
			if (iOnWhat != ON_NOTHING)
			{
				switch ( (*DynamicIter)->GetId() )
				{
				case OBJECT_RAIN:
					delete *DynamicIter;
					DynamicIter = m_vecDynamicObj.erase(DynamicIter);
					break;
				default:
					break;
				}
				break;
			}
		}

		if (iOnWhat == ON_NOTHING)
			++DynamicIter;
	}
}

void CZombieView::IsMouseOnObject()
{
	for (SCENEOBJITER iter = m_vecSceneObj.begin();
		iter != m_vecSceneObj.end();++iter)
	{
		(*iter)->IsMouseOnObj(m_ptMousePosOnMap);
	}

	for (SCENEOBJITER iter = m_vecDynamicObj.begin();
		iter != m_vecDynamicObj.end();++iter)
	{
		if ((*iter)->IsMouseOnObj(m_ptMousePosOnMap))
			return;
	}
}

void CZombieView::ChangePlayerWeapon()
{
	m_Player.ChangeWeapon();
}

void CZombieView::PlayerJump()
{
	if (m_Player.GetVertDirection() == MOVE_VERTSTATIC)
	{
		UINT uiSpeed;
		switch (IsPlayerOnGround())
		{
		case ON_BOTTOMFLOOR:
		case ON_GRASS:
		case OBJECT_CUTDOWNTREE:
		case OBJECT_SMALLCAR:
			uiSpeed = 12;
			break;
		default:
			uiSpeed = 0;
			break;
		}
		m_Player.Jump(uiSpeed);
	}
}

int CZombieView::PassStage()
{
	m_Stage.ReInitialStage(); //
	m_Stage.StagePlus(); //关卡加1

	m_Player.RememberInitilaWeaponBag();

	if ( m_Stage.GetStage() == 4)
		exit(0);

	if ( !m_Stage.InitializeStage(m_Player,m_ptClientOrgOnMap) ) 
	{
		KillTimer(m_hWnd,GAME_UPDATE);
		MessageBox(NULL,TEXT("地图加载失败"),TEXT("error"),MB_OK);
		exit(0);
		return FALSE;
	}

	m_bIsInitData = false;
	return TRUE;
}

void CZombieView::DrawSceneObject()
{
	for (SCENEOBJITER iterDynamic = m_vecDynamicObj.begin();
		iterDynamic != m_vecDynamicObj.end();++iterDynamic)
	{
		(*iterDynamic)->Move();
		(*iterDynamic)->Draw(m_hInstance,m_hMemDc);
	}

	for (vector<CSceneObject*>::iterator iter = m_vecSceneObj.begin();
		iter != m_vecSceneObj.end();++iter)
	{
		(*iter)->Draw(m_hInstance,m_hMemDc);
		switch ( (*iter)->GetId() )
		{
		case OBJECT_CLOUD:
			((CCloud*)(*iter))->GenerateRain(m_vecDynamicObj);
			break;
		default:
			break;
		}
	}

	IsObjectOnObject();
}

void CZombieView::DrawWeaponOnGround()
{
	typedef vector<CWeapon*>::iterator WeaponIter;
	for (WeaponIter iter = m_vecWeaponOnGround.begin();
		iter != m_vecWeaponOnGround.end();++iter)
	{
		if (*iter) 
			(*iter)->DrawOnGround(m_hInstance,m_hMemDc);
	}
}

void CZombieView::GetWeaponOnGround()
{
	typedef vector<CWeapon*>::iterator WeaponIter;
	POINT ptWeaponPos;
	POINT ptPlayerpos = m_Player.GetCurPos();
	RECT rcPlayer = 
		{ptPlayerpos.x - m_Player.GetWidth(),
		 ptPlayerpos.y - 1.5f*m_Player.GetHeight(),
		 ptPlayerpos.x + m_Player.GetWidth(),
		 ptPlayerpos.y + 5};

	for (WeaponIter iter = m_vecWeaponOnGround.begin();
		iter != m_vecWeaponOnGround.end();++iter)
	{
		ptWeaponPos = (*iter)->GetPosOnGround();
		ptWeaponPos.x += (*iter)->GetWidth()/2;
		if (PtInRect(&rcPlayer,ptWeaponPos))
		{
			CWeapon *pOldWeapon = *iter;
			m_Player.GetWeaponOnGround(*iter);
			m_Stage.SetCurMapNewWeapon(pOldWeapon,*iter);
			if ( !(*iter) )
				m_vecWeaponOnGround.erase(iter);
			break;
		}
	}
}

void CZombieView::PlayerWeaponReload()
{
	m_Player.WeaponReload();
}

void CZombieView::ShowPlayerBag()
{
	m_iGameState = GAMESTATE_SELECT;
	KillTimer(m_hWnd,GAME_UPDATE);

	if (m_pSelectBKG)
		delete m_pSelectBKG;
	m_pSelectBKG = new CSelectPlayerBagBkg(&m_Player);
	m_pSelectBKG->PlaySelectBkgSound();
}

void CZombieView::SetInitDataFlag(bool bFlag)
{
	m_bIsInitData = bFlag;
}

void CZombieView::ClearWeaponOnGround()
{
	m_Stage.ClearAllWeapon();
	m_vecWeaponOnGround.clear();
}

void CZombieView::ClearSceneObject()
{
	m_Stage.ClearAllSceneObj();
	m_vecSceneObj.clear();
}

void CZombieView::ClearZombie()
{
	m_Stage.ClearAllDead();
	m_vecDead.clear();
}

void CZombieView::DrawZombie()
{
	THING thing;
	vector<THING> vecThing;
	for (vector<CDead*>::iterator iter = m_vecDead.begin();
		iter != m_vecDead.end();++iter)
	{
		(*iter)->Draw(m_hInstance,m_hMemDc);
		IsDeadOnGround(*iter);
		(*iter)->Move(m_Player,m_Stage.GetCurMapSize());
		if ( (*iter)->IsSelfActionAble() )
		{
			thing = (*iter)->SelfAction();
			if (thing.tpye != tt_none)
				vecThing.push_back(thing);
		}
	}

	for (vector<THING>::iterator iter1 = vecThing.begin();
		iter1 != vecThing.end();++iter1)
	{
		switch (iter1->tpye)
		{
		case tt_dead:
			m_vecDead.push_back((CDead*)iter1->pThing);
			m_Stage.AddDeadToCurMap((CDead*)iter1->pThing);
			break;
		case tt_sceneObj:
			m_vecSceneObj.push_back((CSceneObject*)iter1->pThing);
			m_Stage.AddObjToCurMap((CSceneObject*)iter1->pThing);
			break;
		case tt_weapon:
			break;
		}
	}
}

void CZombieView::OperateHelp()
{
}

void CZombieView::TvSnow()
{
	if (m_pSelectBKG)
	{
		int BkgID = m_pSelectBKG->GetBKGId();

		if (BkgID == IDB_TVSNOWBKG1)
			BkgID = IDB_TVSNOWBKG2;
		else
			BkgID = IDB_TVSNOWBKG1;

		m_pSelectBKG->SetBKGId(BkgID);
	}
}

extern DWORD WINAPI TvSnowSoundThread(LPVOID lpParameter);

void CZombieView::PlayTvSnowSound()
{
	HANDLE hSoundThread = 
		CreateThread(NULL,0,
		TvSnowSoundThread,
		NULL,0,NULL);
	CloseHandle(hSoundThread);
}


//void CZombieView::SetFloorLevel(int iyFloor)
//{
//	m_iyFloor = iyFloor;
//}

//int CZombieView::IsPassStage()
//{
//	static int iTemStage = 0;
//	if (iTemStage != m_iStage)
//	{
//		iTemStage = m_iStage;
//		if (iTemStage == 2)
//			return WINGAME;
//		return PASSSTAGE;
//	}
//	return STATICSTAGE;
//}