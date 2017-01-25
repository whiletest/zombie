#ifndef ROOM_DOOR_H
#define ROOM_DOOR_H

#include "door.h"

class CRoomDoor:public CDoor
{
public:
	CRoomDoor();
	~CRoomDoor();
	////////inline function
	///////////////////
public: //virtual function
	void Draw(HINSTANCE hInstance,HDC hdc);
	int IsOnObject(POINT ptPos);
	bool IsBulletOn(CBullet *pBullet);
};

#endif