#ifndef PLAYER_H_
#define PLAYER_H_

#include <windows.h>
#include <vector>

class CWeapon;
class CDead;
class CSceneObject;
enum _sound_PLAYER;

#define MAX_LOADSTRING 100

class CPlayer
{
	typedef std::vector<CSceneObject*>::iterator SCENEOBJITER;
public:
	CPlayer();
	~CPlayer();
	///////////////////////////////inline function
	POINT GetCurPos()const {return m_ptCurPos;}
	UINT GetVertDirection()const {return m_uiVertDirection;} //获得竖直运动方向
	UINT GetHoriDirection()const {return m_uiHoriDirection;} //获得水平运动方向
	void SetVertPos(int iy) {m_ptCurPos.y = iy;} //设玩家竖直坐标
	void SetHoriPos(int ix) {m_ptCurPos.x = ix;} //设玩家水平坐标
	int GetWidth()const {return m_iWidth;}
	int GetHeight()const {return m_iHeight;}
	int GetHoriSpeed()const {return m_uiHorizontalCurSpeed;} //获取水平速度
	int GetVertSpeed()const {return m_uiVerticalCurSpeed;} //获取竖直速度
	bool IsDead()const {return (m_iBlood == 0);}
	void SetBloodOutFlag(bool flag) {m_bBloodOut = flag;}
	void BloodFull() {m_iBlood = 300;}
	/////////////////////////////////
	void Fire(); //开枪
	void ChangeWeapon(); //按q键切换背包中的武器
	int GetWeaponShootRate()const;
	bool LoseBlood(int iHurt);
	bool IncreaseBlood(int iBlood);
	//玩家移动并处理子弹打击到物体上
	void Move(std::vector<CDead*> &vecDead,
		std::vector<CSceneObject*> &vecSceneObj); 
	void Jump(UINT uiInitSpeed); //跳起
	bool ChangeDirection(UINT uiDirection); //移动方向改变
	void DrawPerson(int ix,int iy,HDC hdc,HINSTANCE hInstance); //画出火柴人
	void DrawMessage(HINSTANCE hInstance,HDC hdc,POINT &ptPos); //绘制客户区左上角提示信息
	void GetWeaponOnGround(CWeapon *&pWeapon); //获得地上的武器
	void WeaponReload(); //换子弹
	void GetPlayerRect(RECT &rcRect);
	void GetUsefulObject(CSceneObject *pSceneObj); //获得有用的物品
	void dropObjFromBag(CSceneObject *pSceneObj); //将背包内的东西丢掉
    BOOL IsUseObject(int iObjID,int index = -1); //是否可以使用物品(重载) index用于查找钥匙
	BOOL IsUseObject(CSceneObject *pObj); //是否可以使用物品(重载)
	int  getObjNumInBag(int iObjID); //返回物品包中某类物品的总数
	void ClearObjBag(); //清楚物品包中的物品
	void ReInitialize(); //重新开始游戏初始化玩家数据
	bool GetBulletSupply(int iWeaponKind,int iBulletNum); //获得子弹供给
	void RememberInitilaWeaponBag(); //过关时记忆初始时刻的武器包
	void playSound(_sound_PLAYER sound);
	void getAllObjInBag(std::vector<CSceneObject*> &vecBagObj);
	void EquipHead(CSceneObject *pObj);
protected:
	void DrawHande(int ix,int iy,HDC hdc); //画手
	void DrawHead(int ix,int iy,HDC hdc,HINSTANCE hInstance); //画头
	void DrawBody(HINSTANCE hInstance,HDC hdc); //绘制身体
//	void DrawWeapon(HINSTANCE,HDC,POINT,double,double); //绘制武器
	void BloodOut(HINSTANCE hInstance,HDC hdc); //出血
	void InitWeaponBag(); //初始化武器包
	void DrawObjEquipHead(HDC hdc,HINSTANCE hInstance); //绘制头部装饰品
protected:
	TCHAR m_szPlayerName[MAX_LOADSTRING]; //玩家名
	int m_iBlood; //血量
	UINT m_uiLife; //生命值
	UINT m_uiHoriDirection; //水平移动方向
	UINT m_uiVertDirection; //竖直移动方向
	UINT m_uiHorizontalCurSpeed; //水平当前速度
	UINT m_uiGravity; //竖直(重力)加速度
	UINT m_uiVerticalCurSpeed; //竖直当前速度
	POINT m_ptCurPos; //当前位置
	int m_iHeight; //身体长度
	int m_iWidth; //宽度
	int m_iWeaponSelection; //当前武器选择标识
	bool m_bBloodOut; //出血标志(被攻击时为true)
	CWeapon* m_pWeaponBag[WEAPON_KIND_NUM]; //武器包
	CWeapon* m_pTemWeaponBag[WEAPON_KIND_NUM]; //用于重玩时初始化武器包
	std::vector<CSceneObject*> m_vecObjBag; //物品包
	CSceneObject *m_pObjEquipHead; //不要delete(指向物品包中的物品指针)
	int m_iFace; //朝向
	_sound_PLAYER m_sound; //玩家发出声音
	POINT m_ptCurHandePos; //当前手的位置(地图上的设备坐标)
	//以ptOrg为原点的逻辑角度正玄值,ptOrg = {m_ptCurPos.x,m_ptCurPos.y-m_iHeight/2-4};
	double m_dCurSinA; 
	//以ptOrg为原点的逻辑角度余玄值,ptOrg = {m_ptCurPos.x,m_ptCurPos.y-m_iHeight/2-4};
	double m_dCurCosA; 
};


#endif