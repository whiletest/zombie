#ifndef ARROW_H_
#define ARROW_H_

#include "bullet.h"

class CArrow:public CBullet
{
public:
	CArrow();
	~CArrow();
public: //virtual function
	void Draw(HINSTANCE,HDC);
};

#endif