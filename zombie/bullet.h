#ifndef BULLET_H_
#define BULLET_H_

class CBullet
{
public:
	CBullet(int id = 0,
		int iWidth = 0,
		int iHeigth = 0,
		int iSpeed = 0,
		int iRange = 0,
		int iHurt = 0
		);
	virtual ~CBullet();
	bool Move();
	void SetAngleValue(double sinA,double cosA);
	//inline function
	int GetID()const {return (int)m_uiBulletId;}
	void SetBulletPos(const POINT &ptPos) {m_ptCurPos = ptPos;}
	int GetHurt()const {return m_iHurt;}
	void SetHurt(int iHurt) {m_iHurt = iHurt;}
	POINT GetPosition()const {return m_ptCurPos;}
	void SetRange(int iRange) {m_iRange = iRange;}
	int GetCosA()const {return (int)m_dCosA;}
public: //virtual function
	virtual void Draw(HINSTANCE,HDC) = 0;
protected:
	UINT m_uiBulletId; //子弹id(与枪的id相同)
	int m_iWidth;
	int m_iHeigth;
	int m_iSpeed; //子弹速度
	int m_iHurt; //伤害(子弹的攻击力)
	int m_iRange; //子弹射程
	POINT m_ptCurPos; //子弹位置
	double m_dSinA; //正玄
	double m_dCosA; //余弦
	int m_ixDistance;
	int m_iyDistance;
	//下面两个变量通过m_iSpeed和正余弦值
	//计算出，用于减少计算次数
	int m_ixIncrement; //水平方向增量
	int m_iyIncrement; //竖直方向增量
};

#endif