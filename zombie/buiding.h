#ifndef _buidingH_
#define _buidingH_

class CBuiding:public CSceneObject
{
public:
	CBuiding();
	virtual ~CBuiding();
public://virtual function
	void Draw(HINSTANCE hInstance,HDC hdc);
};

#endif