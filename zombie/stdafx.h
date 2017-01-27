// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#pragma comment( lib, "msimg32" )
#pragma comment( lib, "winmm" )

#include "targetver.h"
#include "resource.h"

#define WIN32_LEAN_AND_MEAN             // 从 Windows 头中排除极少使用的资料
#define CW_USEDEFAULT       ((int)0x80000000)

//游戏状态
/************************************************************************/
#define GAMESTATE_SELECT 0 //选择界面
#define GAMESTATE_PLAY 1 //游戏界面
/************************************************************************/

//过关标识
/************************************************************************/
#define PASSSTAGE 1
#define STATICSTAGE 2
#define WINGAME 3
/************************************************************************/

/************************************************************************/
#define PASSWORD_RIGHT IDB_NUM0
#define PASSWORD_ERROR IDB_SAFEBOXOK
/************************************************************************/
// Windows 头文件:
#include <windows.h>

// C 运行时头文件
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: 在此处引用程序需要的其他头文件
#include <mmsystem.h>
#include <time.h>
//
#include "GlobalNamespace.h"
#include "timer.h"
#include "message.h"
#include "OnObject.h"
#include "_stage.h"
#include "_MoveDirection.h"
#include "_sound.h"
#include "_bltfmt.h"
#include "_shootOn.h"
#include "_weaponKind.h"
#include "_faceDirection.h"
#include "_objectIdentify.h"
//
#include "view.h"
#include "player.h"
#include "stage.h"
#include "map.h"
#include "SelectBKG.h"
#include "buttonBKG.h"
#include "buttonBKGEx.h"
#include "InitialSelectBKG.h"
#include "SelectBkg1.h"
#include "SelectBkg2.h"
#include "SelectBkg3.h"
#include "SelectBkg4.h"
#include "selectBkg5.h"
#include "SelectPlayerBagBkg.h"
//
#include "weapon.h"
#include "AK47.h"
#include "DesertEagle.h"
#include "m4a1.h"
#include "awp.h"
#include "FiveSeven.h"
#include "usp.h"
#include "mp5.h"
#include "bow.h"
//
#include "bullet.h"
#include "DEbullet.h"
#include "arrow.h"
//
#include "dead.h"
#include "smallzombie.h"
#include "bird.h"
#include "DeadMan.h"
#include "dog.h"
#include "hunter.h"
#include "spider_s.h"
#include "spider_b.h"
//
#include "SceneObject.h"
#include "multipleObj.h"
#include "noninteractive.h"
#include "tree.h"
#include "ground.h"
#include "cloud.h"
#include "grass.h"
#include "door.h"
#include "RoomDoor.h"
#include "CutDownTree.h"
#include "DeadTree.h"
#include "car.h"
#include "SmallCar.h"
#include "key.h"
#include "paper.h"
#include "house1.h"
#include "wall.h"
#include "window1.h"
#include "cabinet.h"
#include "BulletSupply.h"
#include "RoadSign.h"
#include "bus.h"
#include "closestool.h"
#include "bed.h"
#include "tv.h"
#include "socket.h"
#include "disk.h"
#include "WashPot.h"
#include "SafeBox.h"
#include "sofa.h"
#include "desk.h"
#include "football.h"
#include "MessiPaper.h"
#include "HomeGate.h"
#include "stick.h"
#include "BusSet.h"
#include "rain.h"
#include "truck.h"
#include "bike.h"
#include "buiding.h"
#include "gameMachine.h"
#include "coin.h"
#include "roadDirectLight.h"
#include "ladder.h"
#include "ladderEx.h"
#include "mask.h"
#include "bloodSupply.h"
#include "spiderBlood.h"
#include "LuaDefObj.h"