#ifndef VIEW_H_
#define VIEW_H_

#include "player.h"
#include "stage.h"
#include <vector>
using namespace std;

class CDead;
class CSceneObject;
class CWeapon;
class CSelectBKG;

class CZombieView
{
	typedef vector<CSceneObject*>::iterator SCENEOBJITER;
	typedef vector<CSelectBKG*>::iterator SELECTBKGITER;
public: //view function
	CZombieView();
	CZombieView(HINSTANCE hInstance,HWND hWnd);
	~CZombieView();
	void SetMemDc(HDC hdc);
	void InitialBackGround(HDC hdc);
	void MemToScreen(HDC hdc);
	void SetInitDataFlag(bool bFlag); //
	bool InitializeBKGObject(); //初始化所有对象数据
	int PassStage(); //
	void SomethingHappen(); //按键E
	void ShowMssg(); //显示游戏中的提示信息
	void EndShowMssg(); //停止显示游戏中的提示信息
	void SetMssg(int iMssg) {m_iMssg = iMssg;} //设置显示的消息代号
	void TvSnow(); //电视背景雪花处理
	void PlayTvSnowSound(); //播放电视机雪花声音
	void OperateHelp(); //按h键弹出操作说明
protected: //view function
	bool MoveHoriBkg(const POINT &ptPos); //背景水平移动
	bool MoveVertBkg(const POINT &ptPos); //背景竖直移动
	//void SetPassStageRect(); //设置过关区域
public: //BKG function
	void InitialSelectBKG();
	void ShowSelectBKG(HDC hdc); //
	void IsMouseOnBtnBKG(POINT &ptMouse); //鼠标是否在按键上(WM_MOUSEMOVE)
	void IsClickOnBtnBKG(); //
//	void ClearBKG();
public: //SelectBkg4 Function
	int SelBkg4_MoveToNextItem();
protected:////////////////// weapon function
	void DrawWeaponOnGround(); //绘制地上的武器
	void ClearWeaponOnGround(); //清除地上的所有武器
public: /////////////player function
	void DrawPlayer();
	POINT GetPlayerPos()const;
	bool ChangePlayerDirection(UINT uiDirection); //移动方向改变
	void MovePlayer(); //
	void PlayerJump(); //玩家跳起
	void PlayerFire(); //玩家射击
	int GetPlayerWeaponShootRate()const;
	void DrawPlyerMessage();
	void ChangePlayerWeapon();
	void GetWeaponOnGround();
	void PlayerWeaponReload();
	void ShowPlayerBag(); //显示玩家背包里的物品 按B
protected:///////////////player function
	int IsPlayerOnGround(); //检测玩家是否在地上(不在空中)
protected: /////////////// sceneobject function
	void DrawSceneObject();
	void ClearSceneObject(); //清除所有背景物体
	void IsObjectOnObject(); //可动物体是否在物体上
public: /////////////// sceneobject function
	void IsMouseOnObject(); //鼠标是否在物体上
public: //zombie function
	void DrawZombie();
	void ClearZombie(); //清除所有丧尸
protected: //zombie function
	int IsDeadOnGround(CDead *pDead); //检测死尸是否在地上(不在空中)
protected:
	int m_iMssg; //游戏中显示提示信息的种类
	HINSTANCE m_hInstance;
	HWND m_hWnd;
	HDC m_hMemDc;
	HBITMAP m_hBmpBKG; 
	bool m_bIsInitData; //标记数据是否已经初始化
	RECT m_rcPassStage; //过关区域
	RECT m_rcMap; //地图大小
	CPlayer m_Player; //玩家
	CStage m_Stage; //关卡
	CSelectBKG *m_pSelectBKG; //选择背景
	vector<CSceneObject*> m_vecDynamicObj; //可动的物体
	vector<CSceneObject*> m_vecSceneObj; //背景物体集合
	vector<CDead*> m_vecDead; //死尸集合
	vector<CWeapon*> m_vecWeaponOnGround; //地上的武器集合
	CSceneObject *m_pTemSceneObj;
public:
	POINT m_ptClientOrgOnMap; //客户区原点(左上)在地图上对应的点
	POINT m_ptMousePosOnMap; //鼠标在地图上的点
	RECT m_rcClient; //屏幕显示客户区大小(不是地图大小)
	int m_iGameState; //游戏状态
};

#endif