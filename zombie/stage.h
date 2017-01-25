#ifndef STAGE_H_
#define STAGE_H_

#include <vector>

#define MAX_DOORNUM 30

class CMap;
class CDoor;
class CSceneObject;
class CWeapon;
class CDead;

class CStage
{
	typedef std::vector<CMap*>::iterator MAPITER;
	typedef std::vector<CDead*>::iterator DEADITER;
	typedef std::vector<CSceneObject*>::iterator SCENEOBJITER;
	typedef std::vector<CWeapon*>::iterator WEAPONITER;
	typedef int INT_PARAM;
public:
	CStage();
	~CStage();
	////////////////////////////inline function
	void StagePlus() {++m_iStage;}
	void StageReduce() {--m_iStage;}
	int GetStage()const {return m_iStage;}
	int GetCurMapIndex()const {return m_iCurIndex;}
	void SetCurMapIndex(int index) {m_iCurIndex = index;}
	int GetDoorIndexTable(int index)const {return m_iDoorIndexTable[index];}
	////////////////////////////
	RECT GetCurMapSize()const; //返回当前地图大小
	CDoor* FoundRelativeDoor(int iDoorIndex); //根据索引找到对应的door对象
	void SetCurMapNewWeapon(CWeapon *pOld,CWeapon *pNew); //一般用于玩家拾取武器时

	bool LoadMapInfo(); //初始化某地图各种数据信息(背景物，怪)
	void CreateWeaponOnGround(int id,POINT &ptPos); //创建地图上的武器
	void CreateSceneObject(int id,POINT &ptPos,int iWidth,int iHeigth,LPVOID pVoid); //创建第背景物体
	void CreateZombie(int id,POINT &ptPos,int iWidth,int iHeigth,LPVOID pVoid); //创建丧尸
	bool InitializeStage(CPlayer &player,POINT &ptClientOrgOnMap);

	void ClearAllDead(); //清除此关卡所有地图的所有死尸
	void ClearAllSceneObj(); //清除此关卡所有地图的所有背景物体
	void ClearAllWeapon(); //清除此关卡所有地图的所有地上的武器

	void GetCurMapDead(std::vector<CDead*> &vecDead); //导出当前地图的死尸
	void GetCurMapSceneObj(std::vector<CSceneObject*> &vecSceneObj); //导出当前地图背景物
	void GetCurMapWeapon(std::vector<CWeapon*> &vecWeapon); //导出当前地图武器

	void ReInitialStage();

	void EraseObjFromCurMap(CSceneObject *pObj); //删除指定背景物体
	void EraseWeaponFromCurMap(CWeapon *pWeapon); //删除指定武器


	void AddObjToCurMap(CSceneObject *pObj); //添加指定物体
	void AddWeaponToCurMap(CWeapon *pWeapon); //添加指定武器
	void AddDeadToCurMap(CDead *pDead); //添加指定丧尸
protected:
	void InitializeMap(int id,POINT &ptPos, //in
		int iWidth, int iHeigth, //in
		CPlayer &player, //out
		POINT &ptClientOrgOnMap /*out*/); //初始化某地图(大小)
protected:
	int m_iStage; //当前关卡
	int m_iMapNodeNum; //本关卡地图节点个数
	int m_iCurIndex; //本关卡当前地图索引
	int m_iDoorNum; //本关门的个数
	int m_iDoorIndexTable[MAX_DOORNUM]; //本关门的索引表
	std::vector<CMap*> m_vecMap; //本关卡地图集合
};

#endif