#include "stdafx.h"
#include "resource.h"
#include <cmath>

POINT GetCompHandePoint(HDC hdc,POINT &ptMouse,double*,double*);
DWORD WINAPI PlayerSoundThread(LPVOID lpParameter);


CPlayer::CPlayer(): m_uiLife(1),
					m_iBlood(300),
					m_uiGravity(1),
					m_uiHorizontalCurSpeed(5),
					m_uiVerticalCurSpeed(0),
					m_uiHoriDirection(MOVE_HORISTATIC),
					m_uiVertDirection(MOVE_VERTSTATIC),
					m_iWidth(24),
					m_iHeight(46),
					m_iFace(FACE_RIGHT),
					m_iWeaponSelection(KIND_HANDGUN),
					m_dCurSinA(0.0),
					m_dCurCosA(0.0),
					m_pObjEquipHead(0)
{
	m_ptCurPos.x = m_ptCurPos.y = 0;
	lstrcpy(m_szPlayerName,TEXT("zcx"));

	for (int i = 0;i != WEAPON_KIND_NUM;++i)
	{
		if (m_pTemWeaponBag[i])
			delete m_pTemWeaponBag[i];
		m_pTemWeaponBag[i] = NULL;
	}
}

CPlayer::~CPlayer()
{
	for (int i = 0;i != WEAPON_KIND_NUM;++i)
	{
		if (!m_pWeaponBag[i])
			delete m_pWeaponBag[i];
	}
	ClearObjBag();
}

void CPlayer::ReInitialize()
{
	//m_uiLife = 1;
	m_iBlood = 300;
	m_uiVerticalCurSpeed = 0;
	m_uiHoriDirection = MOVE_HORISTATIC;
	m_uiVertDirection = MOVE_VERTSTATIC;
	m_iFace = FACE_RIGHT;
	m_iWeaponSelection = KIND_HANDGUN;
	m_dCurSinA = 0.0f;
	m_dCurCosA = 0.0f;

	InitWeaponBag();
}

bool CPlayer::GetBulletSupply(int iWeaponKind,int iBulletNum)
{
	if (m_pWeaponBag[iWeaponKind])
	{
		m_pWeaponBag[iWeaponKind]->GetBulletSupply(iBulletNum);
		return true;
	}
	return false;
}

bool CPlayer::LoseBlood(int iHurt)
{
	static int count = 0;

	m_iBlood -= iHurt;
	if (m_iBlood <= 0)
	{
		m_iBlood = 0;
		playSound(_sound_player_dead);
		return false;
	}

	if (count == 0)
		playSound(_sound_player_hurt);

	count = (count+1)%2;
	
	return true;
}

void CPlayer::ChangeWeapon()
{
	m_iWeaponSelection = 
		(m_iWeaponSelection+1)%WEAPON_KIND_NUM;
	if (m_pWeaponBag[m_iWeaponSelection])
		m_pWeaponBag[m_iWeaponSelection]->PlayPullSound();
}

bool CPlayer::IncreaseBlood(int iBlood)
{
	m_iBlood += iBlood;
	if (m_iBlood > 300)
	{
		m_iBlood = 300;
		return false;
	}
	return true;
}

void CPlayer::Jump(UINT uiInitSpeed)
{
	m_uiVerticalCurSpeed = uiInitSpeed; //竖直起跳速度
	m_uiVertDirection = MOVE_UP;
}

bool CPlayer::ChangeDirection(UINT uiDirection)
{
	switch (uiDirection)
	{
	//case MOVE_UP:
	case MOVE_DOWN:
	case MOVE_VERTSTATIC:
		if (m_uiVertDirection != uiDirection)
		{
			m_uiVertDirection = uiDirection;
			return true;
		}
		break;
	case MOVE_LEFT:
	case MOVE_RIGHT:
	case MOVE_HORISTATIC:
		if (m_uiHoriDirection != uiDirection)
		{
			m_uiHoriDirection = uiDirection;
			return true;
		}
		break;
	default:
		break;
	}
	return false;
}

void CPlayer::Move(std::vector<CDead*> &vecDead, 
				   std::vector<CSceneObject*> &vecSceneObj)
{
	//水平方向
	switch (m_uiHoriDirection)
	{
	case MOVE_LEFT:
			m_ptCurPos.x -= m_uiHorizontalCurSpeed;
			if (m_ptCurPos.x < 0)
				m_ptCurPos.x = 0;
		break;
	case MOVE_RIGHT:
			m_ptCurPos.x += m_uiHorizontalCurSpeed;
		break;
	case MOVE_HORISTATIC:
	default:
		break;
	}

	//竖直方向
	switch (m_uiVertDirection)
	{
	case MOVE_VERTSTATIC:
		if (m_uiVerticalCurSpeed != 0)
			m_uiVerticalCurSpeed = 0;
		break;
	case MOVE_UP:
		m_uiVerticalCurSpeed -= m_uiGravity;
		if (m_uiVerticalCurSpeed <= 0)
		{
			m_uiVerticalCurSpeed = 0;
			m_uiVertDirection = MOVE_DOWN;
			break;
		}
		m_ptCurPos.y -= m_uiVerticalCurSpeed;
		break;
	case MOVE_DOWN:
		m_uiVerticalCurSpeed += m_uiGravity;
		m_ptCurPos.y += m_uiVerticalCurSpeed;
		break;
	}

	//子弹打到物体上的处理
	for (int i = 0;i != WEAPON_KIND_NUM;++i)
	{
		if (m_pWeaponBag[i])
		{
			if (m_pWeaponBag[i]->IsExistBullet())
			{
				m_pWeaponBag[i]->ShootOn(vecDead,vecSceneObj);
			}
		}
	}
}


void CPlayer::GetWeaponOnGround(CWeapon *&pWeapon)
{
	POINT ptWeaponOnGround;
	CWeapon *pTemWeapon;
	int iWeaponKind = pWeapon->GetKind();
	ptWeaponOnGround = pWeapon->GetPosOnGround();
	pTemWeapon = m_pWeaponBag[iWeaponKind];
	m_pWeaponBag[iWeaponKind] = pWeapon;
	pWeapon = pTemWeapon;
	if (pWeapon)
		pWeapon->SetPosOnGround(ptWeaponOnGround);

	
	m_iWeaponSelection = iWeaponKind; //跳转到捡抢类型背包
	m_pWeaponBag[m_iWeaponSelection]->PlayPullSound();

}

void CPlayer::WeaponReload()
{
	if (m_pWeaponBag[m_iWeaponSelection])
		m_pWeaponBag[m_iWeaponSelection]->Reload();
}

void CPlayer::GetPlayerRect(RECT &rcRect)
{
	rcRect.left = m_ptCurPos.x - m_iWidth/2;
	rcRect.top = m_ptCurPos.y - m_iHeight;
	rcRect.right = m_ptCurPos.x + m_iWidth/2;
	rcRect.bottom = m_ptCurPos.y;
}

void CPlayer::GetUsefulObject(CSceneObject *pSceneObj)
{
	m_vecObjBag.push_back(pSceneObj);
}

void CPlayer::dropObjFromBag(CSceneObject *pSceneObj)
{
	for (SCENEOBJITER iter = m_vecObjBag.begin();
		iter != m_vecObjBag.end();++iter)
	{
		if (*iter == pSceneObj)
		{
			if (m_pObjEquipHead == pSceneObj)
				m_pObjEquipHead = 0;

			m_vecObjBag.erase(iter);
			break;
		}
	}
}

void CPlayer::ClearObjBag()
{
	for (SCENEOBJITER iter = m_vecObjBag.begin();
		iter != m_vecObjBag.end();++iter)
	{
		delete *iter;
	}
	m_vecObjBag.clear();
}

BOOL CPlayer::IsUseObject(int iObjID,int index /* = -1 */)
{
	if ( index == 0 )
		return TRUE;

	for (SCENEOBJITER iter = m_vecObjBag.begin();
		iter != m_vecObjBag.end();++iter)
	{
		if ( iObjID == (*iter)->GetId() )
		{
			if ( iObjID == OBJECT_KEY )	
			{
				if ( index == ((CKey*)(*iter))->GetKeyIndex() )
				{
					delete *iter;
					m_vecObjBag.erase(iter);
					return TRUE;
				}
			}
			else 
			{
				delete *iter;
				m_vecObjBag.erase(iter);
				return TRUE;
			}
		}
	}
	return FALSE;
}

BOOL CPlayer::IsUseObject(CSceneObject *pObj)
{
	for (SCENEOBJITER iter = m_vecObjBag.begin();
		iter != m_vecObjBag.end();++iter)
	{
		if (*iter == pObj)
		{
			delete pObj;
			m_vecObjBag.erase(iter);
			return TRUE;
		}
	}

	return FALSE;
}

int CPlayer::getObjNumInBag(int iObjID)
{
	int cNum = 0;
	for (SCENEOBJITER iter = m_vecObjBag.begin();
		iter != m_vecObjBag.end();++iter)
	{
		if (iObjID == (*iter)->GetId())
			++cNum;
	}
	return cNum;
}

void CPlayer::Fire()
{
	if (m_pWeaponBag[m_iWeaponSelection])
		m_pWeaponBag[m_iWeaponSelection]->Fire(m_ptCurHandePos,m_dCurSinA,m_dCurCosA);
}

//void CPlayer::SetWeaponFireFlag(bool flag)
//{
//	m_pWeaponBag[m_iWeaponSelection]->SetFireFlag(flag);
//}

//bool CPlayer::GetWeaponFireFlag() const
//{
//	return m_pWeaponBag[m_iWeaponSelection]->GetFireFlag();
//}

int CPlayer::GetWeaponShootRate() const
{
	if (m_pWeaponBag[m_iWeaponSelection])
		return m_pWeaponBag[m_iWeaponSelection]->GetShootRate();
	return 0;
}

void CPlayer::BloodOut(HINSTANCE hInstance,HDC hdc)
{
	HBITMAP hbmpBlood = LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_BLOODOUTUP));
	HDC hMemDc = CreateCompatibleDC(hdc);
	SelectObject(hMemDc,hbmpBlood);
	BitBlt(hdc,m_ptCurPos.x-10,m_ptCurPos.y-m_iHeight-20,
		24,25,hMemDc,0,0,SRCCOPY);
	DeleteDC(hMemDc);
	DeleteObject(hbmpBlood);
	m_bBloodOut = false;
}

void CPlayer::DrawMessage(HINSTANCE hInstance,HDC hdc,POINT &ptPos)
{
	static BITMAP bitmap;
	bitmap.bmWidth = bitmap.bmHeight = 0;

	HDC hMemDc = CreateCompatibleDC(hdc);
	HBITMAP hbmp = NULL;


	if (m_pWeaponBag[m_iWeaponSelection])
	{
		//绘制武器图片
		int iWeaponID = 
			m_pWeaponBag[m_iWeaponSelection]->GetWeaponID();
		hbmp = LoadBitmap(hInstance,MAKEINTRESOURCE(iWeaponID));
		GetObject(hbmp,sizeof(BITMAP),(LPBYTE)&bitmap);
		SelectObject(hMemDc,hbmp);
		TransparentBlt(hdc,ptPos.x+20,ptPos.y+20,bitmap.bmWidth,bitmap.bmHeight,
			hMemDc,0,0,bitmap.bmWidth,bitmap.bmHeight,RGB(255,255,255));

		//绘制武器详细信息
		int iBulletNum = 
			m_pWeaponBag[m_iWeaponSelection]->GetBulletNum();
		int iRestBulletNum = 
			m_pWeaponBag[m_iWeaponSelection]->GetRestBulletNum();
		float fShootRate = 
			1000.0f/(float)m_pWeaponBag[m_iWeaponSelection]->GetShootRate();
		TCHAR szWeaponName[20];
		m_pWeaponBag[m_iWeaponSelection]->GetWeaponName(szWeaponName);
		int iHurt = m_pWeaponBag[m_iWeaponSelection]->GetWeaponHurt();
		TEXTMETRIC tm;
		GetTextMetrics(hdc,&tm);
		static TCHAR szText[4][15];
		_stprintf(szText[0],TEXT("%s%s"),TEXT("武器--"),szWeaponName);
		swprintf(szText[1],TEXT("%s%d%c%d"),TEXT("容弹量--"),iBulletNum,TEXT('/'),iRestBulletNum);
		swprintf(szText[2],TEXT("%s%d"),TEXT("伤害--"),iHurt);
		swprintf(szText[3],TEXT("%s%0.2f%s"),TEXT("射速--"),fShootRate,TEXT("发/秒"));

		for (int i = 0;i != 4;++i)
			TextOut(hdc,ptPos.x+20,ptPos.y+bitmap.bmHeight+(i+1)*tm.tmHeight,
			szText[i],lstrlen(szText[i]));
	}
	
	//绘制生命数
	if (hbmp)
		DeleteObject(hbmp);
	hbmp = LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_HEADRIGHT));
	SelectObject(hMemDc,hbmp);
	BitBlt(hdc,ptPos.x+bitmap.bmWidth+40,ptPos.y+20,24,18,
		hMemDc,0,0,SRCCOPY);
	DeleteDC(hMemDc);
	DeleteObject(hbmp);
	TextOut(hdc,ptPos.x+bitmap.bmWidth+70,ptPos.y+20,TEXT("x   1"),5);

	//绘制血量
	static int iFullBlood = m_iBlood/3;
	Rectangle(hdc,ptPos.x+bitmap.bmWidth+40,ptPos.y+bitmap.bmHeight+8,
		ptPos.x+bitmap.bmWidth+40+iFullBlood,ptPos.y+bitmap.bmHeight+12);
	HPEN hPen = CreatePen(PS_SOLID,4,RGB(255,0,0));
	HPEN hOldPen = (HPEN)SelectObject(hdc,hPen);
	MoveToEx(hdc,ptPos.x+bitmap.bmWidth+40,ptPos.y+bitmap.bmHeight+10,NULL);
	LineTo(hdc,ptPos.x+bitmap.bmWidth+40+m_iBlood/3,ptPos.y+bitmap.bmHeight+10);
	SelectObject(hdc,hOldPen);
	DeleteObject(hPen);	
}

void CPlayer::DrawPerson(int ix, int iy,HDC hdc,HINSTANCE hInstance)
{
	DrawBody(hInstance,hdc);
	DrawHead(ix,iy,hdc,hInstance);
	DrawObjEquipHead(hdc,hInstance);
	//ptOrg->手的起始点
	POINT ptOrg = {m_ptCurPos.x,m_ptCurPos.y-m_iHeight/2-4};
	POINT ptMouse = {ix,iy};
	POINT ptOldOrg;
	//以ptOrg为原点
	SetViewportOrgEx(hdc,ptOrg.x,ptOrg.y,&ptOldOrg);
	//将ptMouse转换为以ptOrg为原点的逻辑坐标
	DPtoLP(hdc,&ptMouse,1);
	//m_ptCurHandePos->以ptOrg为原点的逻辑坐标
	//m_dCurSinA,m_dCurCosA->以ptOrg为原点的逻辑角度正余玄值
	m_ptCurHandePos = GetCompHandePoint(hdc,ptMouse,&m_dCurSinA,&m_dCurCosA);
	//画子弹
	for (int i = 0;i != WEAPON_KIND_NUM;++i)
	{
		if (m_pWeaponBag[i])
		{
			if (m_pWeaponBag[i]->IsExistBullet())
				m_pWeaponBag[i]->DrawBullet(hInstance,hdc);
		}
	}
	//画武器
	if (m_pWeaponBag[m_iWeaponSelection])
		m_pWeaponBag[m_iWeaponSelection]->Draw(hInstance,hdc,m_iFace,
			m_ptCurHandePos,m_dCurSinA,m_dCurCosA);
	//画手
	DrawHande(m_ptCurHandePos.x,m_ptCurHandePos.y,hdc);
	//将m_ptCurHandePos转换为地图上的设备坐标
	LPtoDP(hdc,&m_ptCurHandePos,1);
	//还原逻辑原点
	SetViewportOrgEx(hdc,ptOldOrg.x,ptOldOrg.y,NULL);
	//出血
	if (m_bBloodOut)
		BloodOut(hInstance,hdc);
}

void CPlayer::DrawBody(HINSTANCE hInstance,HDC hdc)
{
	static int ibmpPeronID = IDB_PERSON1;
	static int iStepRate = 0;
	switch (m_uiHoriDirection)
	{
	case MOVE_HORISTATIC:
		if (m_iFace == FACE_RIGHT)
			ibmpPeronID = IDB_PERSON1;
		else
			ibmpPeronID = IDB_PERSONLEFT1;
		break;
	case MOVE_RIGHT:
		iStepRate = (iStepRate+1)%6;
		if (iStepRate < 3)
			ibmpPeronID = IDB_PERSON1;
		else
			ibmpPeronID = IDB_PERSON2;
		break;
	case MOVE_LEFT:
		iStepRate = (iStepRate+1)%6;
		if (iStepRate < 3)
			ibmpPeronID = IDB_PERSONLEFT1;
		else
			ibmpPeronID = IDB_PERSONLEFT2;
		break;
	}

	HBITMAP hbmpPerson = LoadBitmap(hInstance,MAKEINTRESOURCE(ibmpPeronID));
	HDC hMemdc = CreateCompatibleDC(hdc);
	SelectObject(hMemdc,hbmpPerson);
	TransparentBlt(hdc,m_ptCurPos.x-m_iWidth/2,m_ptCurPos.y-m_iHeight,
		m_iWidth,m_iHeight,
		hMemdc,0,0,m_iWidth,m_iHeight,RGB(255,255,255));
	DeleteDC(hMemdc);
	DeleteObject(hbmpPerson);
}

POINT GetCompHandePoint(HDC hdc,
						POINT &ptMouse,
						double *psinA,
						double *pcosA
						)
{
	//手的半径长度
	static const float fHandeLength = 16.0f;
	
	float fVectorLength =
		sqrt(float(ptMouse.x*ptMouse.x + ptMouse.y*ptMouse.y));
	*psinA = ptMouse.y/fVectorLength;
	*pcosA = ptMouse.x/fVectorLength;
	POINT ptTem;
	ptTem.x = (LONG)(fHandeLength*(*pcosA));
	ptTem.y = (LONG)(fHandeLength*(*psinA));
	return ptTem;
}

void CPlayer::DrawHande(int ix,int iy,HDC hdc)
{
	HPEN hPen = CreatePen(PS_SOLID,2,RGB(0,0,0));
	HPEN hOldPen = (HPEN)SelectObject(hdc,hPen);
	MoveToEx(hdc,0,0,NULL);
	LineTo(hdc,ix,iy);
	Ellipse(hdc,ix-5,iy-5,ix+5,iy+5);
	SelectObject(hdc,hOldPen);
	DeleteObject(hPen);
}

void CPlayer::DrawHead(int ix,int iy,HDC hdc,HINSTANCE hInstance)
{
	HBITMAP hbmpHead;
	HDC hMemDc = CreateCompatibleDC(hdc);
	if (m_ptCurPos.x < ix)
	{
		if (m_iFace != FACE_RIGHT)
			m_iFace = FACE_RIGHT;
		hbmpHead = LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_HEADRIGHT));
	}
	else
	{
		if (m_iFace != FACE_LEFT)
			m_iFace = FACE_LEFT;
		hbmpHead = LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_HEADLEFT));
	}
	SelectObject(hMemDc,hbmpHead);
	TransparentBlt(hdc,m_ptCurPos.x-m_iWidth/2,m_ptCurPos.y-m_iHeight,
		24,18,hMemDc,0,0,24,18,RGB(255,255,255));
	DeleteDC(hMemDc);
	DeleteObject(hbmpHead);
}

void CPlayer::DrawObjEquipHead(HDC hdc,HINSTANCE hInstance)
{
	if (m_pObjEquipHead)
	{
		int bmpId;
		HBITMAP hbmpHead;
		HDC hMemDc = CreateCompatibleDC(hdc);
		int objId = m_pObjEquipHead->GetId();
		switch (m_iFace)
		{
		case FACE_LEFT:
			if (objId == OBJECT_MASK1)
				bmpId = IDB_MASK1;
			else if (objId == OBJECT_MASK2)
				bmpId = IDB_MASK2;
			break;
		case FACE_RIGHT:
			if (objId == OBJECT_MASK1)
				bmpId = IDB_MASK1;
			else if (objId == OBJECT_MASK2)
				bmpId = IDB_MASK2;
			break;
		}
		hbmpHead = LoadBitmap(hInstance,MAKEINTRESOURCE(bmpId));
		SelectObject(hMemDc,hbmpHead);
		TransparentBlt(hdc,m_ptCurPos.x-m_iWidth/2,m_ptCurPos.y-m_iHeight,
			24,20,hMemDc,0,0,24,20,RGB(255,255,255));
		DeleteDC(hMemDc);
		DeleteObject(hbmpHead);
	}
}

void CPlayer::InitWeaponBag()
{
	for (int i = 0;i != WEAPON_KIND_NUM;++i)
	{
		m_pWeaponBag[i] = m_pTemWeaponBag[i];
	}
}

void CPlayer::RememberInitilaWeaponBag()
{
	for (int i = 0;i != WEAPON_KIND_NUM;++i)
	{
		m_pTemWeaponBag[i] = m_pWeaponBag[i];
	}
}

void CPlayer::playSound(_sound_PLAYER sound)
{
	m_sound = sound;
	HANDLE hSoundThread;
	hSoundThread = CreateThread(NULL,0,
		PlayerSoundThread,
		(LPVOID)&m_sound,0,0);
	CloseHandle(hSoundThread);
}

void CPlayer::getAllObjInBag(std::vector<CSceneObject*> &vecBagObj)
{
	vecBagObj.assign(m_vecObjBag.begin(),m_vecObjBag.end());
}

void CPlayer::EquipHead(CSceneObject *pObj)
{
	m_pObjEquipHead = pObj;
}