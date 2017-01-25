#ifndef TREE_H_
#define TREE_H_

#include "SceneObject.h"

class CTree:public CSceneObject
{
public:
	CTree();
	~CTree();
public: //virtual function
	void Draw(HINSTANCE hInstance,HDC hdc);
	int IsOnObject(POINT ptPos);
	bool IsBulletOn(CBullet *pBullet);
};

#endif