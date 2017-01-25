#include "stdafx.h"
#include <fstream>

std::ifstream &operator >> (std::ifstream &in,BLOODSUPPLYPARAM &bsParam)
{
	in >> bsParam.bmpIndex;
	in >> bsParam.bloodIncrease;

	return in;
}

CBloodSupply::CBloodSupply(int bi /* = 0 */):
CMultipleObj(OBJECT_BLOODSUPPLY),
m_bloodIncrease(bi)
{

}

CBloodSupply::~CBloodSupply()
{

}

void CBloodSupply::Draw(HINSTANCE hInstance, HDC hdc)
{
	CMultipleObj::Draw(hInstance,hdc);

	if (m_bMouseOnObj)
		TextOut(hdc,m_ptPosition.x,m_ptPosition.y-15,TEXT("≤π≥‰∆∑"),3);
}