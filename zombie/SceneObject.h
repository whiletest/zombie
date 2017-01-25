#ifndef SCENEOBJECT_H_
#define SCENEOBJECT_H_

class CSceneObject
{
public:
	CSceneObject(
		int id = 0,
		int iWidth = 0,
		int iHeigth = 0
	);
	~CSceneObject();
	//////////inline function
	int GetId()const {return m_iObjectId;}
	//////////////////////////
	void SetPosition(POINT pt);
	POINT GetPosition()const;
	void SetWidth(int iWidth);
	void SetHeigth(int iHeigth);
	int GetWidth()const;
	int GetHeigth()const;
	void GetObjRect(RECT &rcRect);
	bool IsMouseOnObj(POINT &ptMouse);
	void PlayObjSound();
public:
	virtual int OnObjectWhere(POINT &ptPos);
	virtual void Move();
	virtual int IsOnObject(POINT ptPos); //玩家或者死尸是否在此物体上
	virtual bool IsBulletOn(CBullet *pBullet); //子弹击中
	virtual void Draw(HINSTANCE hInstance,HDC hdc) = 0;
protected:
	int m_iObjectId;
	int m_iWidth;
	int m_iHeigth;
	POINT m_ptPosition;
	bool m_bMouseOnObj;
	int m_iSoundId; // 
};

#endif