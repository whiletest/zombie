#ifndef DEAD_H_
#define DEAD_H_

class CPlayer;
class CBullet;

enum THING_TYPE
{
	tt_none,
	tt_sceneObj,
	tt_weapon,
	tt_dead
};

struct THING
{
	THING_TYPE tpye;
	void *pThing;
};

class CDead
{
public:
	CDead(
		int iId = 0,
		int iWidth = 0,
		int iHeigth = 0,
		int iSpeed = 0,
		int iHurt = 0,
		int iBlood = 0
		);
	virtual ~CDead();
public:
	void SetHeight(int iHeight) {m_iHeigth = iHeight;}
	void SetWidth(int iWidth) {m_iWidth = iWidth;}
	int GetDeadID()const {return m_iId;}
	bool IsSelfActionAble()const {return m_bSelfAction;}
	void SetAttackRect(const RECT &rcAttack); //设置攻击区域
	void SetCurPos(POINT ptPos);
	POINT GetCurPos()const;
	bool ChangeDirection(int ix); //改变死尸水平方向
	bool ChangeVertState(int iState); //改变竖直方向上的状态
	BOOL IsInHuntRect(POINT ptpos); //检测是否在追踪区域
	BOOL IsInAttackRect(POINT ptPos); //检测是否在攻击区域
	int GetWidth()const;
	int GetHeigth()const;
	int GetVertState()const;
	bool IsDied()const;
	bool IsBulletOn(CBullet *pBullet); //子弹击中
	void SetVertPos(int iy);
	void SetHoriPos(int ix);
	void PlayDeadHuntSound();//播放怪物追捕是声音
	void PlayDeadShootenSound(); //播放怪物被击中声音
protected:
	bool IsInMapRect(const RECT &rc); //检测怪物是否超出地图界限
	void HitBack(CBullet *pBullet); //根据子弹威力击退
	void BloodOut(HINSTANCE hInstance,HDC hdc); //击中出血
public: //virtual function
	virtual void Draw(HINSTANCE hInstance,HDC hdc) = 0; //绘制僵尸
	virtual void SetHuntRect(const RECT &rcClient) = 0; //设置追捕区域
	virtual bool Move(CPlayer &player,const RECT &rc) = 0; //移动 rc一般传入本地图大小
	virtual THING SelfAction(); //对地图产生改变的自定义动作(例如大蜘蛛可以产生小蜘蛛)
protected: //virtual function
	virtual void DrawDiedZombie(HINSTANCE hInstance,HDC hdc) = 0; //丧尸挂掉
	virtual bool LoseBlood(int iHurt); //击中掉血(为了播放声音，所以是虚函数)
protected:
	int m_iId; //id
	int m_iSpeed; //水平方向speed
	int m_iVertSpeed; //竖直方向速度
	int m_iWidth; //width
	int m_iHeigth; //heigth
	int m_iDirection; //朝向
	int m_iBlood; //血量
	int m_iHurt; //攻击力
	int m_iVertState; //竖直方向上的状态
	int m_iStepRate; //脚步移动频率
	RECT m_rcHunt; //追捕区域范围
	RECT m_rcAttack; //攻击区域
	POINT m_ptCurPos; //position
	bool m_bBulletHitOn; //标识子弹是否打中死尸
	bool m_bDied; //标志丧尸是否已经死亡
	POINT m_ptBulletHitPos; //打中情况下(m_bBulletHitOn == true)子弹的位置
	int m_soundHuntId; //攻击叫声id
	int m_soundShootenId; //被击中叫声id
	bool m_bSelfAction; //是否有自定义行为
	static int m_iGravity; //竖直(重力)加速度
};

#endif