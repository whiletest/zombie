#include "stdafx.h"

CLadderEx::CLadderEx(int width,
					 int height
					 ):CSceneObject(OBJECT_LADDEREX,width,height),
					 m_eachWidth(0),
					 m_eachHeight(0),
					 m_style(ls_normalL)
{
	
}


void CLadderEx::setLadderStyle(int eachWidth,int eachHeight,int style)
{
	m_style = style;
	m_eachHeight = eachHeight;
	m_eachWidth = eachWidth;

	m_iWidth = (int)(m_eachWidth*m_iHeigth/m_eachHeight);
}

void CLadderEx::Draw(HINSTANCE hInstance, HDC hdc)
{
	POINT ptBegin;
	if (m_style == ls_normalL) //向左上楼的普通梯子
	{
		ptBegin = m_ptPosition; 
		//从左上向右下画
		while (ptBegin.y != m_ptPosition.y + m_iHeigth)
		{
			MoveToEx(hdc,ptBegin.x,ptBegin.y,0);
			ptBegin.x += m_eachWidth;
			LineTo(hdc,ptBegin.x,ptBegin.y);
			
			MoveToEx(hdc,ptBegin.x,ptBegin.y,0);
			ptBegin.y += m_eachHeight;
			LineTo(hdc,ptBegin.x,ptBegin.y);
		}
	}
	else if (m_style == ls_normalR)//向右上楼的普通梯子
	{
		ptBegin.x = m_ptPosition.x;
		ptBegin.y = m_ptPosition.y + m_iHeigth;
		//从左下向右上画
		while (ptBegin.y != m_ptPosition.y)
		{
			MoveToEx(hdc,ptBegin.x,ptBegin.y,0);
			ptBegin.y -= m_eachHeight;
			LineTo(hdc,ptBegin.x,ptBegin.y);

			MoveToEx(hdc,ptBegin.x,ptBegin.y,0);
			ptBegin.x += m_eachWidth;
			LineTo(hdc,ptBegin.x,ptBegin.y);
		}
	}
}

int CLadderEx::IsOnObject(POINT ptPos)
{
	static const int litte = 2; //上楼时用
	POINT ptBegin;
	if (m_style == ls_normalL)
	{
		ptBegin = m_ptPosition;
		RECT rcArea;
		while (ptBegin.y != m_ptPosition.y + m_iHeigth)
		{
			rcArea.left = ptBegin.x;
			rcArea.top = ptBegin.y;

			ptBegin.x += m_eachWidth;
			ptBegin.y += m_eachHeight;

			rcArea.right = ptBegin.x + litte;
			rcArea.bottom = ptBegin.y +litte;

			if (PtInRect(&rcArea,ptPos))
			{
				m_yOnWhere = rcArea.top;
				return ON_BOTTOMFLOOR;
			}
		}
	}
	else if (m_style == ls_normalR)
	{
		ptBegin.x = m_ptPosition.x;
		ptBegin.y = m_ptPosition.y + m_iHeigth;
		RECT rcArea;
		while (ptBegin.y != m_ptPosition.y)
		{
			rcArea.left = ptBegin.x - litte;
			rcArea.top = ptBegin.y - m_eachHeight;

			ptBegin.x += m_eachWidth;
			rcArea.right = ptBegin.x;
			rcArea.bottom = ptBegin.y + litte;

			if (PtInRect(&rcArea,ptPos))
			{
				m_yOnWhere = rcArea.top;
				return ON_BOTTOMFLOOR;
			}

			ptBegin.y -= m_eachHeight;
		}
	}

	m_yOnWhere = m_ptPosition.y + m_iHeigth;
	return ON_NOTHING;
}

int CLadderEx::OnObjectWhere(POINT &ptPos)
{
	return m_yOnWhere;
}