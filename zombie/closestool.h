#ifndef CLOSESTOOL_H_
#define CLOSESTOOL_H_

#include "SceneObject.h"

class CDisk;

class CClosestool:public CSceneObject
{
public:
	CClosestool();
	~CClosestool();
	bool IsDiskFinded()const {return m_bDiskFinded;}
	void SetRelativeDisk(CSceneObject *pSceneObj) {m_pDisk = (CDisk*)pSceneObj;}
	void FindDisk();
public://virtual function
	void Draw(HINSTANCE hInstance,HDC hdc);
	int IsOnObject(POINT ptPos);
	bool IsBulletOn(CBullet *pBullet);
	int OnObjectWhere(POINT &ptPos);
protected:
	CDisk *m_pDisk; //录像带
	bool m_bDiskFinded; //是否发现了录像带
};

#endif