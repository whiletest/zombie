#include "stdafx.h"

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}


DWORD WINAPI PlayerSoundThread(LPVOID lpParameter)
{
	int iSoundID = *((int*)lpParameter);
	TCHAR szFilePath[100];
	switch (iSoundID)
	{
	case _sound_player_hurt:
		wsprintf(szFilePath,TEXT("%s"),TEXT(".\\res\\playerHurt.wav"));
		break;
	case _sound_player_dead:
		wsprintf(szFilePath,TEXT("%s"),TEXT(".\\res\\playerDead.wav"));
		break;
	default:
		break;
	}
	TCHAR szOpenText[MAX_PATH];
	
	wsprintf(szOpenText,TEXT("open %s type waveaudio alias mymusic"),szFilePath);
	mciSendString(szOpenText,NULL,0,NULL);
	mciSendString(TEXT("play mymusic"),NULL,0,NULL);
	return 0;
}

DWORD WINAPI ObjectSoundThread(LPVOID lpParameter)
{
	int iSoundID = *((int*)lpParameter);
	TCHAR szFilePath[100];
	switch (iSoundID)
	{
	case _sound_rain:
		wsprintf(szFilePath,TEXT("%s"),TEXT(".\\res\\rain.wav"));
		break;
	case _soude_thunder:
		wsprintf(szFilePath,TEXT("%s"),TEXT(".\\res\\thunder.wav"));
		break;
	default:
		break;
	}
	TCHAR szOpenText[MAX_PATH];
	wsprintf(szOpenText,TEXT("open %s type waveaudio alias mymusic"),szFilePath);
	mciSendString(szOpenText,NULL,0,NULL);
	mciSendString(TEXT("play mymusic"),NULL,0,NULL);
	return 0;
}

DWORD WINAPI DeadHuntSoundThread(LPVOID lpParameter)
{
	int iSoundID = *((int*)lpParameter);
	TCHAR szFilePath[100];
	switch (iSoundID)
	{
	case _sound_dog:
		wsprintf(szFilePath,TEXT("%s"),TEXT(".\\res\\bark.wav"));
		break;
	case _sound_smallZombie:
		wsprintf(szFilePath,TEXT("%s"),TEXT(".\\res\\smallZombieHunt.wav"));
		break;
	case _sound_bird:
		wsprintf(szFilePath,TEXT("%s"),TEXT(".\\res\\CrowTweet.wav"));
		break;
	default:
		break;
	}
	TCHAR szOpenText[MAX_PATH];
	
	wsprintf(szOpenText,TEXT("open %s type waveaudio alias mymusic"),szFilePath);
	mciSendString(szOpenText,NULL,0,NULL);
	mciSendString(TEXT("play mymusic"),NULL,0,NULL);
	return 0;
}

DWORD WINAPI DeadShootenSoundThread(LPVOID lpParameter)
{
	int iSoundID = *((int*)lpParameter);
	TCHAR szFilePath[100];
	switch (iSoundID)
	{
	case _sound_dog:
		wsprintf(szFilePath,TEXT("%s"),TEXT(".\\res\\DogShooten.wav"));
		break;
	case _sound_smallZombie:
		wsprintf(szFilePath,TEXT("%s"),TEXT(".\\res\\smallZombieDead.wav"));
		break;
	default:
		break;
	}
	TCHAR szOpenText[MAX_PATH];
	
	wsprintf(szOpenText,TEXT("open %s type waveaudio alias mymusic"),szFilePath);
	mciSendString(szOpenText,NULL,0,NULL);
	mciSendString(TEXT("play mymusic"),NULL,0,NULL);
	return 0;
}

DWORD WINAPI WeaponPullSoundThread(LPVOID lpParameter)
{
	int iSoundID = *((int*)lpParameter);
	TCHAR szFilePath[100];
	switch (iSoundID)
	{
	case SOUND_AK_PULL:
		wsprintf(szFilePath,TEXT("%s"),TEXT(".\\res\\ak47-pull.wav"));
		break;
	default:
		break;
	}
	TCHAR szOpenText[MAX_PATH];
	wsprintf(szOpenText,TEXT("open %s type waveaudio alias mymusic"),szFilePath);
	mciSendString(szOpenText,NULL,0,NULL);
	mciSendString(TEXT("play mymusic"),NULL,0,NULL);
	return 0;
}

DWORD WINAPI WeaponFireSoundThread(LPVOID lpParameter)
{
	int iSoundID = *((int*)lpParameter);
	TCHAR szFilePath[100];
	TCHAR szOpenText[MAX_PATH];
	//
	switch (iSoundID)
	{
	case SOUND_AK_FIRE:
		wsprintf(szFilePath,TEXT("%s"),TEXT(".\\res\\ak47-fire.wav"));
		break;
	case SOUNDE_FIVESEVEN_FIRE:
	case SOUND_DESERTEAGLE_FIRE:
		wsprintf(szFilePath,TEXT("%s"),TEXT(".\\res\\DesertEagle-fire.wav"));
		break;
	case SOUND_USP_FIRE:
		wsprintf(szFilePath,TEXT("%s"),TEXT(".\\res\\usp_fire.wav"));
		break;
	case SOUND_AWP_FIRE:
		wsprintf(szFilePath,TEXT("%s"),TEXT(".\\res\\awp.wav"));
		break;
	case SOUND_MP5_FIRE:
		wsprintf(szFilePath,TEXT("%s"),TEXT(".\\res\\mp5fire.wav"));
		break;
	default:
		break;
	}
	wsprintf(szOpenText,TEXT("open %s type waveaudio alias mymusic"),szFilePath);
	mciSendString(szOpenText,NULL,0,NULL);
	mciSendString(L"play mymusic",NULL,0,NULL);
	
	return 0;
}

DWORD WINAPI WeaponNoBulletFireSoundThread(LPVOID lpParameter)
{
	int iSoundID = *((int*)lpParameter);
	TCHAR szFilePath[100];
	TCHAR szOpenText[MAX_PATH];
	switch (iSoundID)
	{
	case SOUND_DESERTEAGLE_FIRE:
	case SOUND_AK_FIRE:
	case SOUND_USP_FIRE:
		wsprintf(szFilePath,TEXT("%s"),TEXT(".\\res\\ak47-nobullet.wav"));
		break;
	default:
		break;
	}
	wsprintf(szOpenText,TEXT("open %s type waveaudio alias mymusic"),szFilePath);
	mciSendString(szOpenText,NULL,0,NULL);
	mciSendString(TEXT("play mymusic"),NULL,0,NULL);

	return 0;
}

DWORD WINAPI DoorOpenSoundThread(LPVOID lpParameter)
{
	int iSoundID = *((int*)lpParameter);
	TCHAR szFilePath[100];
	switch (iSoundID)
	{
	case SOUNDE_ROOMDOOR_OPEN:
		wsprintf(szFilePath,TEXT("%s"),TEXT(".\\res\\dooropen.wav"));
		break;
	case SOUNDE_ROADDIRECTLIGHT:
		wsprintf(szFilePath,TEXT("%s"),TEXT(".\\res\\roadDirectLight.wav"));
		break;
	default:
		break;
	}
	TCHAR szOpenText[MAX_PATH];
	wsprintf(szOpenText,TEXT("open %s type waveaudio alias mymusic"),szFilePath);
	mciSendString(szOpenText,NULL,0,NULL);
	mciSendString(TEXT("play mymusic"),NULL,0,NULL);
	return 0;
}

DWORD WINAPI WeaponReloadSoundThread(LPVOID lpParameter)
{
	TCHAR szFilePath[100];
	wsprintf(szFilePath,TEXT("%s"),TEXT(".\\res\\reload.wav"));
	TCHAR szOpenText[MAX_PATH];
	wsprintf(szOpenText,TEXT("close %s"),szFilePath);
	mciSendString(szOpenText, NULL, 0, NULL);
	wsprintf(szOpenText,TEXT("open %s type waveaudio alias mymusic"),szFilePath);
	mciSendString(szOpenText,NULL,0,NULL);
	mciSendString(TEXT("play mymusic"),NULL,0,NULL);
	return 0;
}

DWORD WINAPI SelectBkgSoundThread(LPVOID lpParameter)
{
	mciSendString(TEXT("open .\\res\\paper.wav type waveaudio alias mymusic"),NULL,0,NULL);
	mciSendString(TEXT("play mymusic"),NULL,0,NULL);
	return 0;
}

DWORD WINAPI ClickSoundThread(LPVOID lpParameter)
{
	TCHAR szFilePath[100];
	wsprintf(szFilePath,TEXT("%s"),TEXT(".\\res\\click.wav"));
	TCHAR szOpenText[MAX_PATH];
	wsprintf(szOpenText,TEXT("open %s type waveaudio alias mymusic"),szFilePath);
	mciSendString(szOpenText,NULL,0,NULL);
	mciSendString(TEXT("play mymusic"),NULL,0,NULL);
	return 0;
}

DWORD WINAPI SocketSoundThread(LPVOID lpParameter)
{
	TCHAR szFilePath[100];
	wsprintf(szFilePath,TEXT("%s"),TEXT(".\\res\\socket.wav"));
	TCHAR szOpenText[MAX_PATH];
	wsprintf(szOpenText,TEXT("open %s type waveaudio alias mymusic"),szFilePath);
	mciSendString(szOpenText,NULL,0,NULL);
	mciSendString(TEXT("play mymusic"),NULL,0,NULL);
	return 0;
}

DWORD WINAPI TvSnowSoundThread(LPVOID lpParameter)
{
	TCHAR szFilePath[100];
	wsprintf(szFilePath,TEXT("%s"),TEXT(".\\res\\TvSnow.wav"));
	TCHAR szOpenText[MAX_PATH];
	wsprintf(szOpenText,TEXT("open %s type waveaudio alias mymusic"),szFilePath);
	mciSendString(szOpenText,NULL,0,NULL);
	mciSendString(TEXT("play mymusic"),NULL,0,NULL);
	return 0;
}

DWORD WINAPI GameMachineBkgSoundThread(LPVOID lpParameter)
{
	mciSendString(TEXT("open .\\res\\gameMachineBkg.wav type waveaudio alias mymusic"),0,0,0);
	mciSendString(TEXT("play mymusic"),0,0,0);
	return 0;
}

DWORD WINAPI GameMachineWinSoundThread(LPVOID lpParameter)
{
	mciSendString(TEXT("open .\\res\\gameMachineWin.wav type waveaudio alias mymusic"),0,0,0);
	mciSendString(TEXT("play mymusic"),0,0,0);
	return 0;
}

DWORD WINAPI GameMachineLoseSoundThread(LPVOID lpParameter)
{
	mciSendString(TEXT("open .\\res\\gameMachineLose.wav type waveaudio alias mymusic"),0,0,0);
	mciSendString(TEXT("play mymusic"),0,0,0);
	return 0;
}