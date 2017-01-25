#ifndef SELECT_BKG_H
#define SELECT_BKG_H

/************************************************************************/
/* 选择界面基类                                                                
/************************************************************************/

class CSelectBKG
{
public:
	CSelectBKG(int id = 0,
		int iWidth = 0,
		int iHeight = 0);
	virtual ~CSelectBKG();
	/////////////////inline function
	static void SetClientSize(RECT &rcClient) {m_rcClient = rcClient;}
	void SetOrgPoint(POINT &ptPos) {m_ptOrgPos = ptPos;}
	POINT getOrgPoint()const {return m_ptOrgPos;}
	void SetBKGId(int id) {m_iBKGCurId = id;}
	int GetBKGId()const {return m_iBKGCurId;}
	int GetWidth()const {return m_iBKGWidth;}
	int GetHeight()const {return m_iBKGHeight;}
	///////////////////////////////
	void SrcInvert(HDC srcDc);                 //将指定区域反色
	void LoadBKG(HINSTANCE hInstance,HDC hdc);
	void BltBKG(HDC hdc,int bFlag);
public: //virtual func
	virtual void ShowSelectBKG(HINSTANCE hInstance,HDC hdc) = 0;
	virtual void IsOnBtn(POINT &ptMouse) = 0;
	virtual int IsClickOnBtn() = 0;
	virtual void PlaySelectBkgSound();//播放选择界面出现时的声音
protected:
	int m_iBKGCurId; //背景图片id
	int m_iBKGWidth; //背景图片宽度
	int m_iBKGHeight; //背景图片高度
	POINT m_ptOrgPos; //图片左上点位置
	HDC m_hMemDc; //内存dc
	HBITMAP m_hBitmap; //位图句柄
	static RECT m_rcClient; //客户区大小
};

#endif