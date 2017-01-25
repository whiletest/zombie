#include "stdafx.h"

extern DWORD WINAPI WeaponFireSoundThread(LPVOID lpParameter);
extern DWORD WINAPI WeaponPullSoundThread(LPVOID lpParameter);
extern DWORD WINAPI WeaponNoBulletFireSoundThread(LPVOID lpParameter);
extern DWORD WINAPI WeaponReloadSoundThread(LPVOID lpParameter);

CWeapon::CWeapon(int id /* = 0 */,
				 int iKind,
				 int iWidth,
				 int iHeigth,
				 int iBulletNum /* = 0 */,
				 int iRestBulletNum,
				 int iShootRate /* = 0 */
				 ):m_iWeaponId(id),
				 m_iWeaponKind(iKind),
				 m_iWidth(iWidth),
				 m_iHeigth(iHeigth),
				 m_iBulletNum(iBulletNum),
				 m_iRestBulletNum(iRestBulletNum),
				 m_iShootRate(iShootRate)
{
	m_iBulletPerCartridge = iBulletNum;
}

CWeapon::~CWeapon()
{
	ClearBullet();
}

void CWeapon::ClearBullet()
{
	for (vector<CBullet*>::iterator iter = m_vecBullet.begin();
		iter != m_vecBullet.end();++iter)
	{
		delete *iter;
	}
	m_vecBullet.clear();
}


void CWeapon::Reload()
{
	if (m_iRestBulletNum)
	{
		int iTem;
		iTem = m_iBulletPerCartridge - m_iBulletNum;
		if (iTem <= m_iRestBulletNum)
		{
			m_iRestBulletNum -= iTem;
			m_iBulletNum = m_iBulletPerCartridge;
		}
		else
		{
			m_iBulletNum += m_iRestBulletNum;
			m_iRestBulletNum = 0;
		}
		PlayReloadSound();
	}
}


void CWeapon::PlayFireSound()
{
	static int iSoundId;
	switch (m_iWeaponId)
	{
	case ID_AK47:
		iSoundId = SOUND_AK_FIRE;
		break;
	case ID_DESERT_EAGLE:
	case ID_FIVESEVEN:
		iSoundId = SOUND_DESERTEAGLE_FIRE;
		break;
	case ID_AWP:
		iSoundId = SOUND_AWP_FIRE;
		break;
	case ID_USP:
		iSoundId = SOUND_USP_FIRE;
		break;
	case ID_MP5:
		iSoundId = SOUND_MP5_FIRE;
		break;
	default:
		break;
	}
	HANDLE hSoundThread;
	hSoundThread = CreateThread(NULL,0,
		WeaponFireSoundThread,
		(LPVOID)&iSoundId,0,NULL);
	CloseHandle(hSoundThread);
}

void CWeapon::PlayNoBulletFireSound()
{
	static int iSoundId;
	switch (m_iWeaponId)
	{
	case ID_AK47:
	case ID_FIVESEVEN:
	case ID_USP:
	case ID_MP5:
	case ID_DESERT_EAGLE:
		iSoundId = SOUND_AK_FIRE;
		break;
	case ID_AWP:
		break;
	default:
		break;
	}
	HANDLE hSoundThread;
	hSoundThread = CreateThread(NULL,0,
		WeaponNoBulletFireSoundThread,
		(LPVOID)&iSoundId,0,NULL);
	CloseHandle(hSoundThread);
}

void CWeapon::PlayPullSound()
{
	static int iSoundId;
	switch (m_iWeaponId)
	{
	case ID_AK47:
		iSoundId = SOUND_AK_PULL;
		break;
	case ID_DESERT_EAGLE:
	case ID_USP:
		break;
	case ID_AWP:
		break;
	case ID_MP5:
		break;
	default:
		break;
	}
	HANDLE hSoundThread = 
		CreateThread(NULL,0,WeaponPullSoundThread,
		(LPVOID)&iSoundId,0,NULL);
	CloseHandle(hSoundThread);
}

void CWeapon::PlayReloadSound()
{
	HANDLE hSoundThread = 
		CreateThread(NULL,0,WeaponReloadSoundThread,
		NULL,0,NULL);
	CloseHandle(hSoundThread);
}

void CWeapon::DrawBullet(HINSTANCE hInstance,HDC hdc)
{
	for (vector<CBullet*>::iterator iter = m_vecBullet.begin();
		iter != m_vecBullet.end();)
	{
		(*iter)->Draw(hInstance,hdc);
		if ( !(*iter)->Move() )
		{
			delete *iter;
			if (iter != m_vecBullet.begin())
			{
				vector<CBullet*>::iterator TemIter;
				TemIter = iter - 1;
				m_vecBullet.erase(iter);
				iter = TemIter;
			}
			else
			{
				m_vecBullet.erase(iter);
				iter = m_vecBullet.begin();
			}
			continue;
		}
	    ++iter;
	}
}

void CWeapon::ShootOn(vector<CDead*> &vecDead,
					  vector<CSceneObject*> &vecSceneObj)
{
	bool bIsOn  = false;
	typedef std::vector<CDead*>::iterator DeadIter;
	typedef std::vector<CSceneObject*>::iterator ScenneObjIter;
	int iDeadID;

	for (vector<CBullet*>::iterator BulletIter = m_vecBullet.begin();
		BulletIter != m_vecBullet.end();)
	{
		//打中丧尸
		for (DeadIter iter = vecDead.begin();
			iter != vecDead.end();++iter)
		{
			iDeadID = (*iter)->GetDeadID();
			if (iDeadID == ID_BIRD
				&&  (*BulletIter)->GetID() != ID_BOW )
				((CBird*)(*iter))->IsHearFire(*BulletIter);

			bIsOn = (*iter)->IsBulletOn(*BulletIter);
			if ( bIsOn )
			{
				delete *BulletIter;
				if (BulletIter != m_vecBullet.begin())
				{
					vector<CBullet*>::iterator TemIter;
					TemIter = BulletIter - 1;
					m_vecBullet.erase(BulletIter);
					BulletIter = TemIter;
				}
				else
				{
					m_vecBullet.erase(BulletIter);
					BulletIter = m_vecBullet.begin();
				}
				break;
			}
		}

		if (bIsOn)
			continue;

		//打中背景物体		
		for (ScenneObjIter iter = vecSceneObj.begin();
			iter != vecSceneObj.end();++iter)
		{
			bIsOn = (*iter)->IsBulletOn(*BulletIter);
			if ( bIsOn )
			{
				delete *BulletIter;
				if (BulletIter != m_vecBullet.begin())
				{
					vector<CBullet*>::iterator TemIter;
					TemIter = BulletIter - 1;
					m_vecBullet.erase(BulletIter);
					BulletIter = TemIter;
				}
				else
				{
					m_vecBullet.erase(BulletIter);
					BulletIter = m_vecBullet.begin();
				}
				break;
			}
		}

		//没击中任何东西
		if (!bIsOn)
			++BulletIter;
		bIsOn = false;
	}
}

bool CWeapon::IsExistBullet()//不存在子弹返回false
{
	return !m_vecBullet.empty();
}

void RotateBitmap(HDC dcSrc,
				  int SrcWidth,
				  int SrcHeight,
				  double sinA,
				  double cosA,
				  HDC hdc,
				  POINT *pptPos)
{
	double x1,x2,x3;
	double y1,y2,y3;
	double maxWidth,maxHeight,minWidth,minHeight;
	double srcX,srcY;
	double DstWidth;
	double DstHeight;
	HDC dcDst;//旋转后的内存设备环境
	HBITMAP newBitmap;
	x1 = -SrcHeight * sinA;
	y1 = SrcHeight * cosA;
	x2 = SrcWidth * cosA - SrcHeight * sinA;
	y2 = SrcHeight * cosA + SrcWidth * sinA;
	x3 = SrcWidth * cosA;
	y3 = SrcWidth * sinA;
	minWidth = x3>(x1>x2?x2:x1)?(x1>x2?x2:x1):x3;
	minWidth = minWidth>0?0:minWidth;
	minHeight = y3>(y1>y2?y2:y1)?(y1>y2?y2:y1):y3;
	minHeight = minHeight>0?0:minHeight;
	maxWidth = x3>(x1>x2?x1:x2)?x3:(x1>x2?x1:x2);
	maxWidth = maxWidth>0?maxWidth:0;
	maxHeight = y3>(y1>y2?y1:y2)?y3:(y1>y2?y1:y2);
	maxHeight = maxHeight>0?maxHeight:0;
	DstWidth = maxWidth - minWidth;
	DstHeight = maxHeight - minHeight;
	dcDst = CreateCompatibleDC(dcSrc);
	newBitmap = CreateCompatibleBitmap(dcSrc,(int)DstWidth,(int)DstHeight);
	SelectObject(dcDst,newBitmap);
	RECT rcRect = {0,0,(int)DstWidth,(int)DstHeight};
	FillRect(dcDst,&rcRect,(HBRUSH)GetStockObject(WHITE_BRUSH));
	for( int I = 0 ;I<DstHeight;I++)
	{
		for(int J = 0 ;J< DstWidth;J++)
		{
			srcX = (J + minWidth) * cosA + (I + minHeight) * sinA;
			srcY = (I + minHeight) * cosA - (J + minWidth) * sinA;
			if( (srcX >= 0) && (srcX <= SrcWidth) &&(srcY >= 0) && (srcY <= SrcHeight))
			{
				BitBlt(dcDst, J, I, 1, 1, dcSrc,(int)srcX, (int)srcY, SRCCOPY);
			}
		}
	}
	//显示旋转后的位图
	TransparentBlt(hdc,pptPos->x,pptPos->y,(int)DstWidth,(int)DstHeight,
		dcDst,0,0,(int)DstWidth,(int)DstHeight,RGB(255,255,255));
	DeleteDC(dcDst);
	DeleteObject(newBitmap);
}