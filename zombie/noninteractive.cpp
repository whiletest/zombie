#include "stdafx.h"

CNonInteractiveObj::CNonInteractiveObj(int width,
									   int height
									   ):CMultipleObj(OBJECT_NONINTERACTIVE,width,height)
{

}

int CNonInteractiveObj::IsOnObject(POINT ptPos)
{
	return ON_NOTHING;
}

int CNonInteractiveObj::OnObjectWhere(POINT &ptPos)
{
	return m_ptPosition.y;
}