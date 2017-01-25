#include "stdafx.h"
#include <cmath>

CBullet::CBullet(int id /* = 0 */,
				 int iWidth,
				 int iHeigth,
				 int iSpeed /* = 0 */,
				 int iRange,
				 int iHurt /* = 0 */
				 ):m_uiBulletId(id),
				 m_iWidth(iWidth),
				 m_iHeigth(iHeigth),
				 m_iSpeed(iSpeed),
				 m_iRange(iRange),
				 m_iHurt(iHurt),
				 m_ixDistance(0),
				 m_iyDistance(0),
				 m_dSinA(0.0f),
				 m_dCosA(0.0f)
{

}

CBullet::~CBullet()
{

}

bool CBullet::Move()
{
	m_ixDistance += m_ixIncrement;
	m_iyDistance += m_iyIncrement;
	if ( (int)fabs(float(m_ixDistance)) >= m_iRange
		|| (int)fabs(float(m_iyDistance)) >= m_iRange )
		return false;
	m_ptCurPos.x += m_ixIncrement;
	m_ptCurPos.y += m_iyIncrement;
	return true;
}

void CBullet::SetAngleValue(double sinA,double cosA)
{
	m_dSinA = sinA;
	m_dCosA = cosA;
	m_ixIncrement = (int)(m_iSpeed*m_dCosA);
	m_iyIncrement = (int)(m_iSpeed*m_dSinA);
}


