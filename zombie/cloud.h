#ifndef CLOUD_H_
#define CLOUD_H_

#include "SceneObject.h"

class CCloud:public CSceneObject
{
public:
	CCloud();
	~CCloud();
	void SetRainFlag(bool bRainFlag){m_bRain = bRainFlag;}
	void GenerateRain(vector<CSceneObject*> &vecDynamicObj);
public://virtual function
	void Draw(HINSTANCE hInstance,HDC hdc);
	int IsOnObject(POINT ptPos);
	bool IsBulletOn(CBullet *pBullet);
protected:
	bool m_bRain;
	int m_bmpRainId; //ÎÚÔÆÍ¼Æ¬id
	int m_count;
	int m_countGap; //¸ô¶à¾Ã´òÀ×
	bool m_bGetCountGap;
};


#endif