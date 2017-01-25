#ifndef CAR_H_
#define CAR_H_

#include "SceneObject.h"

class CCar:public CSceneObject
{
public:
	CCar(int id = 0,int iWidth = 0,int iHeigth = 0);
	virtual ~CCar();
	/////////////////inline function
	void SetKey(int iKey) {m_ikey = iKey;}
	int GetKeyIndex()const {return m_ikey;}
	///////////////////////////////
	BOOL Open(int iKey);
protected:
	int m_ikey;
};

#endif