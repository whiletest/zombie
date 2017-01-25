#ifndef DE_BULLET_H
#define DE_BULLET_H

#include "bullet.h"

class CDEBullet:public CBullet
{
public:
	CDEBullet();
	virtual ~CDEBullet();
public: //virtual function
	void Draw(HINSTANCE,HDC);
};

#endif