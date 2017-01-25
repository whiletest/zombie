#ifndef __soundH_
#define __soundH_

enum _sound_WPS
{
SOUND_AK_PULL
};

enum _sound_WFS
{
 SOUND_AK_FIRE,
 SOUND_DESERTEAGLE_FIRE,
 SOUND_AWP_FIRE,
 SOUNDE_FIVESEVEN_FIRE,
 SOUND_USP_FIRE,
 SOUND_MP5_FIRE
};

enum _sound_DS
{
 SOUNDE_ROOMDOOR_OPEN,
 SOUNDE_ROADDIRECTLIGHT
};

enum _sound_OBJ
{
	_sound_none,
	_sound_rain,
	_soude_thunder //À×Éù
};

enum _sound_DEAD
{
	_sound_dog = 1,
	_sound_smallZombie,
	_sound_bird
};

enum _sound_PLAYER
{
	_sound_player_hurt = 1,
	_sound_player_dead
};

#endif