#ifndef _gameMachineH_
#define _gameMachineH_

#include "SceneObject.h"

class CGameMachine:public CSceneObject
{
public:
	CGameMachine(int id = OBJECT_GAMEMACHINE,int width = 59,int height = 70);
	~CGameMachine();
	void SetKind(_objectIdentify id,int iWidth,int iHeight);
public: //virtual function
	void Draw(HINSTANCE hInstance,HDC hdc);
	int IsOnObject(POINT ptPos);
};

#endif