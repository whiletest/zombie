#ifndef MESSI_PAPER_H_
#define MESSI_PAPER_H_

#include "SceneObject.h"

class CMessiPaper:public CSceneObject
{
public:
	CMessiPaper();
	~CMessiPaper();
public: //virtual function
	void Draw(HINSTANCE hInstance,HDC hdc);
	int IsOnObject(POINT ptPos);
	bool IsBulletOn(CBullet *pBullet);
};

#endif