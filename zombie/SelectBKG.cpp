#include "stdafx.h"

CSelectBKG::CSelectBKG(int id /* = 0 */,
					   int iWidth /* = 0 */, 
					   int iHeight /* = 0 */)
					   :m_iBKGCurId(id),
					   m_iBKGWidth(iWidth),
					   m_iBKGHeight(iHeight)
{

}

RECT CSelectBKG::m_rcClient = {0,0,0,0};

CSelectBKG::~CSelectBKG()
{
	if (m_hMemDc)
		DeleteDC(m_hMemDc);
	if (m_hBitmap)
		DeleteObject(m_hBitmap);
}

void CSelectBKG::LoadBKG(HINSTANCE hInstance,HDC hdc)
{
	if (m_hBitmap)
		DeleteObject(m_hBitmap);
	m_hBitmap = LoadBitmap(hInstance,MAKEINTRESOURCE(m_iBKGCurId));
	if (m_hMemDc)
		DeleteDC(m_hMemDc);
	m_hMemDc = CreateCompatibleDC(hdc);
	SelectObject(m_hMemDc,m_hBitmap);
}

void CSelectBKG::SrcInvert(HDC srcDc)
{
	if (m_hBitmap)
		DeleteObject(m_hBitmap);
	m_hBitmap = CreateCompatibleBitmap(srcDc,m_iBKGWidth,m_iBKGHeight);
	if (m_hMemDc)
		DeleteDC(m_hMemDc);
	m_hMemDc = CreateCompatibleDC(srcDc);
	SelectObject(m_hMemDc,m_hBitmap);
	
	BitBlt(m_hMemDc,0,0,m_iBKGWidth,m_iBKGHeight,
		srcDc,m_ptOrgPos.x,m_ptOrgPos.y,NOTSRCCOPY);
}

void CSelectBKG::BltBKG(HDC hdc,int bFlag)
{
	if (bFlag == FLAG_STRECHBLT)
		StretchBlt(hdc,m_ptOrgPos.x,m_ptOrgPos.y,m_rcClient.right,m_rcClient.bottom,
			m_hMemDc,0,0,m_iBKGWidth,m_iBKGHeight,SRCCOPY);
	else if (bFlag == FLAGE_TRANSBLT)
		TransparentBlt(hdc,m_ptOrgPos.x,m_ptOrgPos.y,m_iBKGWidth,m_iBKGHeight,
		m_hMemDc,0,0,m_iBKGWidth,m_iBKGHeight,RGB(255,255,255));
	else
		BitBlt(hdc,m_ptOrgPos.x,m_ptOrgPos.y,m_iBKGWidth,m_iBKGHeight,
		m_hMemDc,0,0,SRCCOPY);
	DeleteDC(m_hMemDc);
	DeleteObject(m_hBitmap);
}

void CSelectBKG::PlaySelectBkgSound()
{

}