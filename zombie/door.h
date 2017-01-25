#ifndef DOOR_H_
#define DOOR_H_

#include "SceneObject.h"


struct DOORPARAM 
{
	int iDoorIndex; //门的索引号
	int iToMapIndex;
	int iKey;
	int iDoorType;
};


class CDoor:public CSceneObject
{
public:
	CDoor(int id = 0,int iWidth = 0,int iHeigth = 0);
	virtual ~CDoor();
	////////inline function
	void SetMapIndexTo(int index) {m_iToMapIndex = index;}
	void SetKey(int iKey) {m_iKey = iKey;}
	void SetDoorIndex(int index) {m_iDoorIndex = index;}
	void SetDoorType(int type) {m_iDoorType = type;}
	int GetDoorIndex()const {return m_iDoorIndex;}
	int GetKey()const {return m_iKey;}
	/////////////////////
	int Open();
	POINT GetPlayerPos();
	void GetClientOrgPosOnMap(POINT &ptClientOrgOnMap,RECT &rcClient);
	void PlayDoorOpenSound();
public: //virtual function
protected:
	int m_iDoorIndex; //门的索引号
	int m_iToMapIndex; //通向的地图的索引
	int m_iKey; //钥匙值(没有钥匙设置为0)
	int m_iDoorType; //门的类型(设置为图片id)
};

#endif