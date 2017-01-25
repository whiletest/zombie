#ifndef PAPER_H_
#define PAPER_H_

#include "SceneObject.h"

class CPaper:public CSceneObject
{
public:
	CPaper();
	virtual ~CPaper();
	void SetIndex(int index) {m_iIndex = index;}
	int GetIndex()const {return m_iIndex;}
public: //virtual function
	void Draw(HINSTANCE hInstance,HDC hdc);
	int IsOnObject(POINT ptPos);
	bool IsBulletOn(CBullet *pBullet);
protected:
	int m_iIndex; //选择界面索引
};

#endif