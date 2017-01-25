#ifndef SELECTBKG4_H_
#define SELECTBKG4_H_

#include "SelectBKG.h"
#include <vector>

#define TOTAL_ITEM_NUM 21  //总共的项数为21

enum _choice_name;
class CPlayer;

class CGameMachineOperation // 游戏机操作类
{
public:
	CGameMachineOperation():m_numMaxSeleted(2)
	{
		m_iCurItem = 0;
	}
	////////////////////////////////////////////
	bool Select(int index)
	{
		if (m_vecSeletedIndex.size() == m_numMaxSeleted)
			return false;

		m_vecSeletedIndex.push_back(index);
		return true;
	}
    ////////////////////////////////////////////////////////
	bool CancelSeleted(int index)
	{	
		for (std::vector<int>::iterator iter = m_vecSeletedIndex.begin();
			iter != m_vecSeletedIndex.end();++iter)
		{
			if (*iter == index)
			{
				m_vecSeletedIndex.erase(iter);
				return true;
			}
		}

		return false;
	}
	/////////////////////////////////////////////////////////
	void CanCelAll()
	{
		m_vecSeletedIndex.clear();
	}
	/////////////////////////////////////////////////////////
	int MoveToNextItem()
	{
		m_iCurItem = (m_iCurItem+1)%TOTAL_ITEM_NUM;
		return m_iCurItem;
	}
	/////////////////////////////////////////////////////////
	int getCurItem()const 
	{return m_iCurItem;}
	/////////////////////////////////////////////////////////
	bool Run()
	{
		if (m_vecSeletedIndex.size() == 0)
			return false;
		return true;
	}
	/////////////////////////////////////////////////////////
	bool IsWin(_choice_name cn)
	{
		for (int i = 0;i != m_vecSeletedIndex.size();++i)
		{
			if (m_vecSeletedIndex[i] == cn)
				return true;
		}
		return false;
	}
	/////////////////////////////////////////////////////////
protected:
	const int m_numMaxSeleted;
	int m_iCurItem;  //当前滚动到的选项 < TOTAL_ITEM_NUM
	std::vector<int> m_vecSeletedIndex; //选择的按钮基于0的索引
};

enum _choice_name
{
	_bar,
	_double_seven,
	_double_star,
	_double_watermelon,
	_double_bell,
	_mango,
	_orange,
	_apple
};

struct ROLLINFO
{
	ROLLINFO()
	{
		ptPos.x = ptPos.y = 0;
		name = _bar;
	}
	ROLLINFO(int x,int y,_choice_name cn)
	{
		ptPos.x = x;
		ptPos.y = y;
		name =  cn;
	}

	POINT ptPos;
	_choice_name name;
};

class CSelectBKG4:public CSelectBKG
{
	typedef std::vector<CButtonBKGEx*>::iterator BTNBKG_ITER;
public:
	CSelectBKG4(CPlayer *pPlayer = 0);
	~CSelectBKG4();
	//////////////////////////////////////
	void PlayWinSound();
	void PlayLoseSound();
	/////////////////////////////////////
public: // virtual func
	void ShowSelectBKG(HINSTANCE hInstance,HDC hdc);
	void IsOnBtn(POINT &ptMouse);
	int IsClickOnBtn();
	void PlaySelectBkgSound();
	///////////////////////////////////
	int GameMachineMoveToNextItem();  //返回滚动间隔秒数，返回0结束
	////////////////////////////////////
protected:
	CPlayer *m_pPlayer; //析构时不要delete
	int m_numCoinInBag; //玩家现在拥有的游戏币数量
	bool m_bStart; //标识游戏是否开始
	int m_iRollTotalTimes; //滚动次数
	int m_cRollTimes; //已滚次数
	CButtonBKG *m_pExitBtn;  
	CButtonBKG *m_pStartBtn;
	CButtonBKG *m_pRollBtn; //用于游戏滚动的按钮
	std::vector<CButtonBKGEx*> m_vecChoiceBtn; //选项按钮
	CGameMachineOperation m_gameMachineOper;
	ROLLINFO m_Rollinfo[TOTAL_ITEM_NUM];
};

#endif