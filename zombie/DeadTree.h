#ifndef DEAD_TREE_H_
#define DEAD_TREE_H_

#include "SceneObject.h"

class CDeadTree:public CSceneObject
{
public:
	CDeadTree();
	virtual ~CDeadTree();
public: //virtual function
	void Draw(HINSTANCE hInstance,HDC hdc);
	int IsOnObject(POINT ptPos);
	bool IsBulletOn(CBullet *pBullet);
};

#endif