#include "stdafx.h"

extern DWORD WINAPI SelectBkgSoundThread(LPVOID lpParameter);
extern DWORD WINAPI GameMachineBkgSoundThread(LPVOID lpParameter);
extern DWORD WINAPI GameMachineWinSoundThread(LPVOID lpParameter);
extern DWORD WINAPI GameMachineLoseSoundThread(LPVOID lpParameter);

CSelectBKG4::CSelectBKG4(CPlayer *pPlayer /* = 0 */):
                           CSelectBKG(IDB_GAMEMACHINEBKG,1017,498),
                           m_bStart(false),
						   m_iRollTotalTimes(0),
						   m_cRollTimes(0),
						   m_pPlayer(pPlayer)
{
	POINT ptOrg = {800,380};
	m_pExitBtn = new CButtonBKG(IDB_SMALLEXITBKG,200,56,IDB_BIGEXITBKG);
	m_pExitBtn->SetOrgPoint(ptOrg);


	ptOrg.y -= 100;
	m_pStartBtn = new CButtonBKG(IDB_STARTSMALL,200,56,IDB_START);
	m_pStartBtn->SetOrgPoint(ptOrg);

	ptOrg.x = 170;
	ptOrg.y = 404;
	CButtonBKGEx *pTempBtn = 0;
	for (int i = 0;i != 8;++i)
	{
		pTempBtn = new CButtonBKGEx(IDB_BTNNOTON,63,29,IDB_BTNON,IDB_BTNON);
		pTempBtn->SetOrgPoint(ptOrg);
		m_vecChoiceBtn.push_back(pTempBtn);
		ptOrg.x += 77;
	}

	ptOrg.y = 106;
	//up side
	m_Rollinfo[0] = ROLLINFO(206,ptOrg.y,_orange);
	m_Rollinfo[1] = ROLLINFO(284,ptOrg.y,_double_bell);
	m_Rollinfo[2] = ROLLINFO(594,ptOrg.y,_apple);
	m_Rollinfo[3] = ROLLINFO(671,ptOrg.y,_mango);

	ptOrg.x = 671;
	//right side
	m_Rollinfo[4] = ROLLINFO(ptOrg.x,146,_double_watermelon);
	m_Rollinfo[5] = ROLLINFO(ptOrg.x,186,_double_watermelon);
	m_Rollinfo[6] = ROLLINFO(ptOrg.x,226,_bar);
	m_Rollinfo[7] = ROLLINFO(ptOrg.x,266,_apple);
	m_Rollinfo[8] = ROLLINFO(ptOrg.x,305,_orange);
	m_Rollinfo[9] = ROLLINFO(ptOrg.x,345,_orange);
	
	ptOrg.y = 345;
	//bottom side
	m_Rollinfo[10] = ROLLINFO(594,ptOrg.y,_double_bell);
	m_Rollinfo[11] = ROLLINFO(516,ptOrg.y,_double_seven);
	m_Rollinfo[12] = ROLLINFO(438,ptOrg.y,_double_seven);
	m_Rollinfo[13] = ROLLINFO(361,ptOrg.y,_apple);
	m_Rollinfo[14] = ROLLINFO(285,ptOrg.y,_mango);
	m_Rollinfo[15] = ROLLINFO(206,ptOrg.y,_mango);

	ptOrg.x = 206;
	//left side
	m_Rollinfo[16] = ROLLINFO(ptOrg.x,306,_double_star);
	m_Rollinfo[17] = ROLLINFO(ptOrg.x,266,_double_star);
	m_Rollinfo[18] = ROLLINFO(ptOrg.x,226,_bar);
	m_Rollinfo[19] = ROLLINFO(ptOrg.x,186,_apple);
	m_Rollinfo[20] = ROLLINFO(ptOrg.x,146,_double_bell);

	m_pRollBtn = new CButtonBKG(0,64,34,0);
	m_pRollBtn->SetOrgPoint(m_Rollinfo[0].ptPos);

	m_numCoinInBag = m_pPlayer->getObjNumInBag(OBJECT_COIN);

	m_ptOrgPos.x = m_ptOrgPos.y = 0;
}

CSelectBKG4::~CSelectBKG4()
{
	if (m_pExitBtn)
		delete m_pExitBtn;
	if (m_pStartBtn)
		delete m_pStartBtn;
	if (m_pRollBtn)
		delete m_pRollBtn;
	for (BTNBKG_ITER iter = m_vecChoiceBtn.begin();
		iter != m_vecChoiceBtn.end();++iter)
		delete *iter;
	m_vecChoiceBtn.clear();
}

void CSelectBKG4::ShowSelectBKG(HINSTANCE hInstance,HDC hdc)
{
	LoadBKG(hInstance,hdc);

	m_pExitBtn->LoadBKG(hInstance,hdc);
	m_pExitBtn->BltBKG(m_hMemDc,FLAGE_TRANSBLT);

	if (!m_bStart)
	{
		m_pStartBtn->LoadBKG(hInstance,hdc);
		m_pStartBtn->BltBKG(m_hMemDc,FLAGE_TRANSBLT);
	}
	
	m_pRollBtn->SrcInvert(m_hMemDc);
	m_pRollBtn->BltBKG(m_hMemDc,FLAG_BITBLT);

	for (BTNBKG_ITER iter = m_vecChoiceBtn.begin();
		iter != m_vecChoiceBtn.end();++iter)
	{
		(*iter)->LoadBKG(hInstance,hdc);
		(*iter)->BltBKG(m_hMemDc,FLAGE_TRANSBLT);
	}

	TCHAR szContent[20];
	wsprintf(szContent,TEXT("您现在拥有%d个游戏币"),m_numCoinInBag);
	TextOut(m_hMemDc,825,248,szContent,lstrlen(szContent));

	BltBKG(hdc,FLAG_STRECHBLT);
}

void CSelectBKG4::IsOnBtn(POINT &ptMouse)
{
	m_pExitBtn->IsOnBtn(ptMouse);

	if (!m_bStart)
		m_pStartBtn->IsOnBtn(ptMouse);

	for (BTNBKG_ITER iter = m_vecChoiceBtn.begin();
		iter != m_vecChoiceBtn.end();++iter)
	{
		(*iter)->IsOnBtn(ptMouse);
	}
}

int CSelectBKG4::IsClickOnBtn()
{
	static int numUse = 0;
	if (!m_bStart)
	{
		for (int i = 0;i != 8;++i)
		{
			if (m_vecChoiceBtn[i]->IsClickOnBtn())
			{
				if (m_vecChoiceBtn[i]->getSelectedState())
				{
					m_vecChoiceBtn[i]->CancelSelect();
					m_gameMachineOper.CancelSeleted(i);
					--numUse;
				}
				else if( (m_numCoinInBag-numUse) > 0 )
				{
					if ( m_gameMachineOper.Select(i) )
					{
						m_vecChoiceBtn[i]->Select();
						++numUse;
					}
				}
				return FALSE;
			}
		}
	}

	int btnId = FALSE;
	if (btnId = m_pExitBtn->IsClickOnBtn())
		return btnId;

	if (!m_bStart)
	{
		if (btnId = m_pStartBtn->IsClickOnBtn())
		{
			if (!m_gameMachineOper.Run())
				return FALSE;
			
			mciSendString(TEXT("close all"),0,0,0);

			while (numUse--)
			{
				m_pPlayer->IsUseObject(OBJECT_COIN);
			}
			m_numCoinInBag = m_pPlayer->getObjNumInBag(OBJECT_COIN);

			m_bStart = true;
			numUse = 0;

			srand(time(NULL));
			m_iRollTotalTimes = (rand()%300)+50;

			return btnId;
		}
	}
	
	return FALSE;
}

void CSelectBKG4::PlaySelectBkgSound()
{
	HANDLE hSoundThread = 
		CreateThread(NULL,0,
		GameMachineBkgSoundThread,0,0,0);
	CloseHandle(hSoundThread);
}

void CSelectBKG4::PlayWinSound()
{
	HANDLE hSoundThread = 
		CreateThread(NULL,0,
		GameMachineWinSoundThread,0,0,0);
	CloseHandle(hSoundThread);
}

void CSelectBKG4::PlayLoseSound()
{
	HANDLE hSoundThread = 
		CreateThread(NULL,0,
		GameMachineLoseSoundThread,0,0,0);
	CloseHandle(hSoundThread);
}

int CSelectBKG4::GameMachineMoveToNextItem()
{
	++m_cRollTimes;

	int iCurItem;
	iCurItem = m_gameMachineOper.MoveToNextItem();
	m_pRollBtn->SetOrgPoint(m_Rollinfo[iCurItem].ptPos);
	
	static int elapse = 500;
	if (m_cRollTimes < 5)
	{
		elapse -= 100;
		if (elapse <= 100)
			elapse = 20;
	}
	else if (m_cRollTimes > m_iRollTotalTimes)
	{
		m_bStart = false;
		elapse = 500;
		m_cRollTimes = 0;

		if (m_gameMachineOper.IsWin(m_Rollinfo[iCurItem].name))
		{
			PlayWinSound();

			int iScores = 0;
			switch (m_Rollinfo[iCurItem].name)
			{
			case _apple:
				iScores = 5;
				break;
			case _double_bell:
			case _mango:
			case _orange:
				iScores = 10;
				break;
			case _bar:
			case _double_seven:
			case _double_star:
			case _double_watermelon:
				iScores = 15;
				break;
			}
			for (int i =0;i != iScores;++i)
				m_pPlayer->GetUsefulObject(new CCoin);
			m_numCoinInBag = m_pPlayer->getObjNumInBag(OBJECT_COIN);
		}
		else
		{
			PlayLoseSound();
		}

		for (int i = 0;i != m_vecChoiceBtn.size();++i)
			m_vecChoiceBtn[i]->CancelSelect();
		m_gameMachineOper.CanCelAll();

		return 0;
	}
	else if (m_cRollTimes > m_iRollTotalTimes-5)
	{
		elapse += 100;
		if (elapse > 500)
			elapse = 500;
	}

	return elapse;
}