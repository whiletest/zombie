#ifndef CUT_DOWN_TREE_H
#define CUT_DOWN_TREE_H

#include "SceneObject.h"

class CCutDownTree:public CSceneObject
{
public:
	CCutDownTree();
	~CCutDownTree();
public: //virtual function
	void Draw(HINSTANCE hInstance,HDC hdc);
	int IsOnObject(POINT ptPos);
	bool IsBulletOn(CBullet *pBullet);
};

#endif