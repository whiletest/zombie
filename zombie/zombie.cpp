// zombie.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "zombie.h"
#include <mmsystem.h>

#pragma comment(lib,"winmm")

#define MAX_LOADSTRING 100
#define WINDOW_CX 1025
#define WINDOW_CY 531

// 全局变量:
HINSTANCE hInst;								// 当前实例
TCHAR szTitle[MAX_LOADSTRING];					// 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名

// 此代码模块中包含的函数的前向声明:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);


int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: 在此放置代码。
	MSG msg;
	HACCEL hAccelTable;

	// 初始化全局字符串
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_ZOMBIE, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ZOMBIE));

	// 主消息循环:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目的: 注册窗口类。
//
//  注释:
//
//    仅当希望
//    此代码与添加到 Windows 95 中的“RegisterClassEx”
//    函数之前的 Win32 系统兼容时，才需要此函数及其用法。调用此函数十分重要，
//    这样应用程序就可以获得关联的
//    “格式正确的”小图标。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ZOMBIE));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目的: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // 将实例句柄存储在全局变量中

   hWnd = CreateWindow(szWindowClass, szTitle, 
	   WS_OVERLAPPEDWINDOW & ~WS_MINIMIZEBOX & ~WS_MAXIMIZEBOX,
      100, 100, WINDOW_CX, WINDOW_CY, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的: 处理主窗口的消息。
//
//  WM_COMMAND	- 处理应用程序菜单
//  WM_PAINT	- 绘制主窗口
//  WM_DESTROY	- 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	//int iCharCount;
	PAINTSTRUCT ps;
	HDC hdc;
	static CZombieView view(hInst,hWnd);
	static RECT rcClient;
	static DWORD dwFireLastTime = timeGetTime(); //用于控制武器发射频率
	static DWORD dwChangeWeaponTime = timeGetTime(); //用于控制按键频率(q,g键)
	static DWORD dwReloadTime = timeGetTime(); //R键
	DWORD dwCurrentTime; //用于控制武器发射频率,按键频率(q键)

	//选择界面
	if ( !view.m_iGameState )
	{
		POINT ptMouse;
		int elapse;

		switch (message)
		{
		case WM_SIZE:
			GetClientRect(hWnd,&rcClient);
			view.m_rcClient = rcClient;
			mciSendString(TEXT("open .\\res\\GameInitial.wav type MPEGVideo"),
				NULL,0,NULL);
			mciSendString(TEXT("play .\\res\\GameInitial.wav repeat"),NULL,0,NULL);
			return 0;
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			view.ShowSelectBKG(hdc);
			EndPaint(hWnd, &ps);
			return 0;
		case WM_MOUSEMOVE:
			ptMouse.x = LOWORD(lParam);
			ptMouse.y = HIWORD(lParam);

			view.IsMouseOnBtnBKG(ptMouse);
			InvalidateRect(hWnd,&rcClient,FALSE);
			return 0;
		case WM_LBUTTONDOWN:
			view.IsClickOnBtnBKG();
			InvalidateRect(hWnd,&rcClient,FALSE);
			return 0;
		case WM_TIMER:
			switch (wParam)
			{
			case TIMER_TVSNOWRATE:
				view.TvSnow();
				view.PlayTvSnowSound();
				InvalidateRect(hWnd,&rcClient,FALSE);
				break;
			case TIMER_GMAEMACHINEROLL:
				elapse = view.SelBkg4_MoveToNextItem();
				if (elapse)
					SetTimer(hWnd,TIMER_GMAEMACHINEROLL,elapse,NULL);
				else
					KillTimer(hWnd,TIMER_GMAEMACHINEROLL);
				InvalidateRect(hWnd,NULL,FALSE);
				break;
			default:
				break;
			}
			return 0;
		case WM_DESTROY:
			KillTimer(hWnd,GAME_UPDATE);
			PostQuitMessage(0);
			return 0;
		default:
			return DefWindowProc(hWnd,message,wParam,lParam);
		}
	}

	mciSendString(TEXT("close all"),NULL,0,NULL);

	//游戏开始
	switch (message)
	{
	case WM_SIZE:
		GetClientRect(hWnd,&rcClient);
		view.m_rcClient = rcClient;
		SetTimer(hWnd,GAME_UPDATE,20,NULL);
		break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		view.InitialBackGround(hdc);
		view.DrawPlayer();
		view.DrawZombie();
		view.DrawPlyerMessage();
		view.ShowMssg();
		view.MemToScreen(hdc);
		EndPaint(hWnd, &ps);
		break;
	case WM_MOUSEMOVE:
		view.m_ptMousePosOnMap.x =
			LOWORD(lParam) + view.m_ptClientOrgOnMap.x;
		view.m_ptMousePosOnMap.y = 
			HIWORD(lParam) + view.m_ptClientOrgOnMap.y;

		view.IsMouseOnObject();
		break;
	case WM_LBUTTONDOWN:
		dwCurrentTime = timeGetTime();
		if ( int(dwCurrentTime - dwFireLastTime) > 
			view.GetPlayerWeaponShootRate() )
		{
			view.PlayerFire();
			dwFireLastTime = dwCurrentTime;
		}
		SetTimer(hWnd,TIMER_PLAYERFIRE,
			(UINT)view.GetPlayerWeaponShootRate(),NULL);
		break;
	case WM_LBUTTONUP:
		KillTimer(hWnd,TIMER_PLAYERFIRE);
		break;
	case WM_CHAR:
		switch (wParam)
		{
		case 'a':
		case 'A':
			view.ChangePlayerDirection(MOVE_LEFT);
			break;
		case 'd':
		case 'D':
			view.ChangePlayerDirection(MOVE_RIGHT);
			break;
		case 'q':
		case 'Q':
			dwCurrentTime = timeGetTime();
			if (int(dwCurrentTime - dwChangeWeaponTime) > 1000)
			{
				view.ChangePlayerWeapon();
				dwChangeWeaponTime = dwCurrentTime;
			}
			break;
		case 'g':
		case 'G':
			dwCurrentTime = timeGetTime();
			if (int(dwCurrentTime - dwChangeWeaponTime) > 1000)
			{
				view.GetWeaponOnGround();
				dwChangeWeaponTime = dwCurrentTime;
			}
			break;
		case 'r':
		case 'R':
			dwCurrentTime = timeGetTime();
			if (int(dwCurrentTime - dwReloadTime) > 2000)
			{
				view.PlayerWeaponReload();
				dwReloadTime = dwCurrentTime;

				//换子弹时不能发子弹
				dwFireLastTime = dwCurrentTime; 
				KillTimer(hWnd,TIMER_PLAYERFIRE);
			}
			break;
		case 'e':
		case 'E':
			view.SomethingHappen();
			break;
		case 'h':
		case 'H':
			view.OperateHelp();
			break;
		case 'b':
		case 'B':
			view.ShowPlayerBag();
			break;
		default:
			break;
		}
		break;
	case WM_KEYDOWN:
		if ((int)wParam == VK_SPACE)
			view.PlayerJump();
		else
			return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	case WM_KEYUP:
		switch ((int)wParam)
		{
		case 'a':
		case 'A':
		case 'd':
		case 'D':
			view.ChangePlayerDirection(MOVE_HORISTATIC);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_TIMER:
		switch (wParam)
		{
		case GAME_UPDATE:
			view.MovePlayer();
			InvalidateRect(hWnd,&rcClient,FALSE);
			break;
		case TIMER_PLAYERFIRE:
			view.PlayerFire();
			break;
		case TIMER_ENDSHOWMSSG:
			view.EndShowMssg();
			break;
		default:
			break;
		}
		break;
	case WM_DESTROY:
		KillTimer(hWnd,GAME_UPDATE);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}


