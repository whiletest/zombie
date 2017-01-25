#include "stdafx.h"

CSelectPlayerBagBkg::CSelectPlayerBagBkg(CPlayer *player /* = 0 */):
                     CSelectBKG(IDB_PLAYERBAGBKG,1017,498),
					 m_pPlayer(player),
					 m_selBtnIndex(-1),
					 m_moveBtnIndex(0)
{
	m_pEquipBtn = new CButtonBKG(IDB_EQUIPSMALL,200,56,IDB_EQUIPBIG);
	POINT ptOrg = {250,150};
	m_pEquipBtn->SetOrgPoint(ptOrg);

	m_pDropBtn = new CButtonBKG(IDB_DROPSMALL,200,56,IDB_DROPBIG);
	ptOrg.y += 100;
	m_pDropBtn->SetOrgPoint(ptOrg);

	m_pExitBtn = new CButtonBKG(IDB_SMALLEXITBKG,200,56,IDB_BIGEXITBKG);
	ptOrg.y += 100;
	m_pExitBtn->SetOrgPoint(ptOrg);

	m_ptKeyPoint[0].x = 520;m_ptKeyPoint[0].y = 44;
	m_ptKeyPoint[1].x = 649;m_ptKeyPoint[1].y = 44;
	m_ptKeyPoint[2].x = 769;m_ptKeyPoint[2].y = 46;
	m_ptKeyPoint[3].x = 883;m_ptKeyPoint[3].y = 46;

	m_ptKeyPoint[4].x = 521;m_ptKeyPoint[4].y = 155;
	m_ptKeyPoint[5].x = 651;m_ptKeyPoint[5].y = 152;
	m_ptKeyPoint[6].x = 769;m_ptKeyPoint[6].y = 152;
	m_ptKeyPoint[7].x = 883;m_ptKeyPoint[7].y = 156;

	m_ptKeyPoint[8].x = 522;m_ptKeyPoint[8].y = 262;
	m_ptKeyPoint[9].x = 652;m_ptKeyPoint[9].y = 262;
	m_ptKeyPoint[10].x = 772;m_ptKeyPoint[10].y = 259;
	m_ptKeyPoint[11].x = 884;m_ptKeyPoint[11].y = 259;

	m_ptKeyPoint[12].x = 523;m_ptKeyPoint[12].y = 367;
	m_ptKeyPoint[13].x = 652;m_ptKeyPoint[13].y = 366;
	m_ptKeyPoint[14].x = 771;m_ptKeyPoint[14].y = 367;
	m_ptKeyPoint[15].x = 885;m_ptKeyPoint[15].y = 367;

	m_pMoveBtn = new CButtonBKGEx(IDB_BAGBKGNOTON,105,102,IDB_BAGBKGON,IDB_BAGBKGNOTON);
	m_pSelectedBtn = new CButtonBKGEx(0,105,102,0,0);

	m_pPlayer->getAllObjInBag(m_vecObjInBag);
	for (int i = 0;i != m_vecObjInBag.size();++i)
		CenterObj(i);

	m_ptOrgPos.x = m_ptOrgPos.y = 0;
}

CSelectPlayerBagBkg::~CSelectPlayerBagBkg()
{
	if (m_pEquipBtn)
		delete m_pEquipBtn;
	if (m_pDropBtn)
		delete m_pDropBtn;
	if (m_pExitBtn)
		delete m_pExitBtn;
	if (m_pMoveBtn)
		delete m_pMoveBtn;
	if (m_pSelectedBtn)
		delete m_pSelectedBtn;
}

void CSelectPlayerBagBkg::ShowSelectBKG(HINSTANCE hInstance,HDC hdc)
{
	LoadBKG(hInstance,hdc);

	for (std::vector<CSceneObject*>::iterator iter = m_vecObjInBag.begin();
		iter != m_vecObjInBag.end();++iter)
	{
		if (*iter)
			(*iter)->Draw(hInstance,m_hMemDc);
	}

	if (IsSelAvailable())
	{
		if (IsObjEquipAble())
		{
			m_pEquipBtn->LoadBKG(hInstance,hdc);
			m_pEquipBtn->BltBKG(m_hMemDc,FLAGE_TRANSBLT);
		}

		m_pDropBtn->LoadBKG(hInstance,hdc);
		m_pDropBtn->BltBKG(m_hMemDc,FLAGE_TRANSBLT);
	}
		
	m_pExitBtn->LoadBKG(hInstance,hdc);
	m_pExitBtn->BltBKG(m_hMemDc,FLAGE_TRANSBLT);

	m_pMoveBtn->LoadBKG(hInstance,hdc);
	m_pMoveBtn->BltBKG(m_hMemDc,FLAGE_TRANSBLT);

	if (m_pSelectedBtn->getSelectedState())
	{
		m_pSelectedBtn->SrcInvert(m_hMemDc);
		m_pSelectedBtn->BltBKG(m_hMemDc,FLAG_BITBLT);
	}

	BltBKG(hdc,FLAG_STRECHBLT);
}

void CSelectPlayerBagBkg::IsOnBtn(POINT &ptMouse)
{
	for (int i = 0;i != 16;++i)
	{
		m_pMoveBtn->SetOrgPoint(m_ptKeyPoint[i]);
		m_pMoveBtn->IsOnBtn(ptMouse);
		if (m_pMoveBtn->getIsOnBtn())
		{
			m_moveBtnIndex = i;
			break;
		}
	}

	if (IsSelAvailable())
	{
		if (IsObjEquipAble())
			m_pEquipBtn->IsOnBtn(ptMouse);
		m_pDropBtn->IsOnBtn(ptMouse);
	}
	
	m_pExitBtn->IsOnBtn(ptMouse);

	for (std::vector<CSceneObject*>::iterator iter = m_vecObjInBag.begin();
		iter != m_vecObjInBag.end();++iter)
	{
		if (*iter)
			(*iter)->IsMouseOnObj(ptMouse);
	}
}

int CSelectPlayerBagBkg::IsClickOnBtn()
{
	int btnid;
	
	if (m_pMoveBtn->IsClickOnBtn())
	{
		if (m_selBtnIndex == m_moveBtnIndex)
		{
			m_pSelectedBtn->CancelSelect();
			m_selBtnIndex = -1;
		}
		else
		{
			m_pSelectedBtn->SetOrgPoint(m_pMoveBtn->getOrgPoint());
			m_pSelectedBtn->Select();
			m_selBtnIndex = m_moveBtnIndex;
		}

		return FALSE;
	}

	if (btnid = m_pEquipBtn->IsClickOnBtn())
	{
		POINT ptCancel = {0,0}; //取消对equip按钮选中状态
		m_pEquipBtn->IsOnBtn(ptCancel);
		return btnid;
	}

	if (btnid = m_pDropBtn->IsClickOnBtn())
	{
		POINT ptCancel = {0,0}; //取消对drop按钮选中状态
		m_pDropBtn->IsOnBtn(ptCancel);
		return btnid;
	}

	if (btnid = m_pExitBtn->IsClickOnBtn())
		return btnid;

	return FALSE;
}

CSceneObject* CSelectPlayerBagBkg::EquipPlayer()
{
	CSceneObject *pObjEquiped = m_vecObjInBag[m_selBtnIndex];

	switch (pObjEquiped->GetId())
	{
	case OBJECT_MASK1:
	case OBJECT_MASK2:
		m_pPlayer->EquipHead(pObjEquiped);
		break;
	case OBJECT_BLOODSUPPLY:
		{
			int bloodIncrease = ((CBloodSupply*)pObjEquiped)->getIncrease();
			m_pPlayer->IncreaseBlood(bloodIncrease);
			m_pPlayer->IsUseObject(pObjEquiped);
			m_vecObjInBag[m_selBtnIndex] = 0;
		}
		break;
	}
	

	return pObjEquiped;
}

CSceneObject* CSelectPlayerBagBkg::DropObjFromPlayerBag()
{
	CSceneObject *pObjDroped = m_vecObjInBag[m_selBtnIndex];

	m_pPlayer->dropObjFromBag(pObjDroped);

	POINT ptObjPos = m_pPlayer->GetCurPos();
	ptObjPos.y -= pObjDroped->GetHeigth();
	pObjDroped->SetPosition(ptObjPos);

	m_vecObjInBag[m_selBtnIndex] = 0;
	
	m_pSelectedBtn->CancelSelect();
	m_selBtnIndex = -1;

	return pObjDroped;
}

bool CSelectPlayerBagBkg::IsSelAvailable()
{
	if (   m_selBtnIndex < 0
		|| m_selBtnIndex >= m_vecObjInBag.size() )
	{
		return false;
	}

	if ( m_vecObjInBag[m_selBtnIndex] == 0)
	{
		return false;
	}

	return true;
}

void CSelectPlayerBagBkg::CenterObj(int index)
{
	POINT ptTem;
	ptTem.x = m_ptKeyPoint[index].x + 105/2;
	ptTem.y = m_ptKeyPoint[index].y + 102/2;
	ptTem.x -= m_vecObjInBag[index]->GetWidth()/2;
	ptTem.y -= m_vecObjInBag[index]->GetHeigth()/2;
	m_vecObjInBag[index]->SetPosition(ptTem);
}

bool CSelectPlayerBagBkg::IsObjEquipAble()
{
	int id = m_vecObjInBag[m_selBtnIndex]->GetId();
	if (   id == OBJECT_MASK1
		|| id == OBJECT_MASK2
		|| id == OBJECT_BLOODSUPPLY)
	{
		return true;
	}

	return false;
}