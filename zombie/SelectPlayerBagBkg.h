#ifndef _selectPlayerBagBkgH_
#define _selectPlayerBagBkgH_

#include "SelectBKG.h"

class CPlayer;
class CSceneObject;
class CWeapon;

class CSelectPlayerBagBkg:public CSelectBKG
{
public:
	CSelectPlayerBagBkg(CPlayer *player = 0);
	virtual ~CSelectPlayerBagBkg();
	/////////////////////////////////////////////
	CSceneObject* DropObjFromPlayerBag();
	CSceneObject* EquipPlayer();
public: // virtual func
	void ShowSelectBKG(HINSTANCE hInstance,HDC hdc);
	void IsOnBtn(POINT &ptMouse);
	int IsClickOnBtn();
protected:
	void CenterObj(int index);
	bool IsObjEquipAble(); //物品是否可以装备
	bool IsSelAvailable();
protected:
	CPlayer *m_pPlayer; //不要delete
	std::vector<CSceneObject*> m_vecObjInBag; //不要delete
	CButtonBKG *m_pEquipBtn;
	CButtonBKG *m_pDropBtn;
	CButtonBKG *m_pExitBtn;
	CButtonBKGEx *m_pMoveBtn; //跟随鼠标移动按钮
	CButtonBKGEx *m_pSelectedBtn; //选中的按钮
	POINT m_ptKeyPoint[16]; //每个物品框的左上顶点
	int m_moveBtnIndex; //移动按钮当前索引
	int m_selBtnIndex; //选中按钮的索引
};

#endif