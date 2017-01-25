#ifndef WEAPON_H_
#define WEAPON_H_

#include <vector>
using namespace std;

class CBullet;
class CDead;
class CSceneObject;

class CWeapon
{
public:
	CWeapon(int id = 0,
		int iKind = 0,
		int iWidth = 0,
		int iHeigth = 0,
		int iBulletNum = 0,
		int iRestBulletNum = 0,
		int iShootRate = 0
		);
	virtual ~CWeapon();
	/////////////////////inline function
	int GetWidth()const {return m_iWidth;}
	int GetHeigth()const {return m_iHeigth;}
	int GetWeaponID()const {return m_iWeaponId;}
	int GetShootRate()const {return m_iShootRate;}
	int GetBulletNum()const {return m_iBulletNum;}
	int GetRestBulletNum()const {return m_iRestBulletNum;}
	void SetPosOnGround(POINT &ptPos) {m_ptPosOnGround = ptPos;}
	POINT GetPosOnGround()const {return m_ptPosOnGround;}
	int GetKind()const {return m_iWeaponKind;}
	int GetWeaponHurt()const {return m_iHurt;}
	void GetWeaponName(TCHAR szName[]) {lstrcpy(szName,m_szWeaponName);}
	void GetBulletSupply(int iBulletNum) {m_iRestBulletNum += iBulletNum;}
	void SetBulletNum(int iNum) {m_iBulletNum = iNum;}
	/////////////////////
	void ClearBullet();
	bool IsExistBullet(); //发射的子弹是否在存在(击中物体后消失)
	void DrawBullet(HINSTANCE hInstance,HDC hdc); //画子弹并移动子弹
	void ShootOn(vector<CDead*> &vecDead,
		vector<CSceneObject*> &vecSceneObj);
	void PlayPullSound(); //播放拉枪栓声音
	void Reload(); //换子弹
protected:
	void PlayFireSound(); //播放枪击声音
	void PlayNoBulletFireSound(); //播放没有子弹枪响声音
	void PlayReloadSound(); //播放换弹夹声音
public:
	virtual void Draw(HINSTANCE hInstance,
		HDC hdc,
		int iFace,
		POINT ptPos,
		double sinA,
		double cosA
		) = 0;
	//发射子弹(创建对象并设置初始位置)
	virtual void Fire(const POINT &ptPos,double sinA,double cosA) = 0; 
	//绘制在地上的武器
	virtual void DrawOnGround(HINSTANCE hInstance,HDC hdc) = 0; 
protected:
	int m_iWeaponId; //武器ID
	int m_iWeaponKind; //武器类型
	int m_iBulletNum; //每个弹夹中的子弹数量
	int m_iRestBulletNum; //剩下的子弹(弹夹中的)
	int m_iBulletPerCartridge; //满弹夹时的子弹
	int m_iWidth;
	int m_iHeigth;
	int m_iShootRate; //发射频率(ms为单位)
	int m_iHurt; //杀伤力
	TCHAR m_szWeaponName[20]; //武器名
	POINT m_ptPosOnGround; //在地上时的位置(绘制在玩家手上的武器不要用此属性)
	vector<CBullet*> m_vecBullet; //发射出的子弹
};

#endif