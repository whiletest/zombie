#include "stdafx.h"
#include "resource.h"

CCloud::CCloud():CSceneObject(OBJECT_CLOUD,155,72),
                 m_bRain(false),
				 m_bGetCountGap(false),
				 m_bmpRainId(IDB_CLOUD),
				 m_count(0),
				 m_countGap(0)
{
	m_iSoundId = _soude_thunder;
}

CCloud::~CCloud()
{

}

void CCloud::Draw(HINSTANCE hInstance,HDC hdc)
{
	if (m_bRain)
	{
		++m_count;

		if (!m_bGetCountGap)
		{
			m_countGap = (rand()%800)+50;
			m_bGetCountGap = true;
			m_bmpRainId = IDB_CLOUD1;
		}
		else if (m_count == m_countGap)
		{
			m_bGetCountGap = false;
			m_count = 0;
			PlayObjSound();
			m_bmpRainId = IDB_CLOUD;
		}
	}

	HDC hMemDc = CreateCompatibleDC(hdc);
	HBITMAP hbmp = LoadBitmap(hInstance,MAKEINTRESOURCE(m_bmpRainId));
	SelectObject(hMemDc,hbmp);
	BitBlt(hdc,m_ptPosition.x,m_ptPosition.y,m_iWidth,m_iHeigth,
		hMemDc,0,0,SRCCOPY);
	DeleteDC(hMemDc);
	DeleteObject(hbmp);
}

void CCloud::GenerateRain(vector<CSceneObject*> &vecDynamicObj)
{
	if (m_bRain)
	{
		int xPos = rand()%m_iWidth;
		xPos += m_ptPosition.x; 
		POINT ptRain = {xPos,m_ptPosition.y};
		CRain *pRain = new CRain;
		pRain->SetPosition(ptRain);
		vecDynamicObj.push_back(pRain);
		pRain = NULL;
	}
}

int CCloud::IsOnObject(POINT ptPos)
{
	return ON_NOTHING;
}

bool CCloud::IsBulletOn(CBullet *pBullet)
{
	return false;
}
