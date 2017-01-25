#include "stdafx.h"

CMultipleObj::CMultipleObj(int objId /* = 0 */,
						   int width /* = 0 */,
						   int height /* = 0 */
						   ):CSceneObject(objId,width,height)
{
	m_bmpIndex = 0;
}

CMultipleObj::~CMultipleObj()
{

}

void CMultipleObj::setObjKind(int width,int height,int bmpIndex)
{
	m_iWidth = width;
	m_iHeigth = height;
	m_bmpIndex = bmpIndex;
}

void CMultipleObj::getObjkind(int *pIndex,
							  int *pwidth /* = 0 */,
							  int *pheight /* = 0 */)
{
	*pheight = m_bmpIndex;
	if (pwidth)
		*pwidth = m_iWidth;
	if (pheight)
		*pheight = m_iHeigth;
}

void CMultipleObj::Draw(HINSTANCE hInstance, HDC hdc)
{
	HDC hMemDc = CreateCompatibleDC(hdc);
	HBITMAP hbmp = LoadBitmap(hInstance,MAKEINTRESOURCE(m_bmpIndex));
	SelectObject(hMemDc,hbmp);

	BitBlt(hdc,m_ptPosition.x,m_ptPosition.y,m_iWidth,m_iHeigth,
		hMemDc,0,0,SRCCOPY);

	DeleteDC(hMemDc);
	DeleteObject(hbmp);
}