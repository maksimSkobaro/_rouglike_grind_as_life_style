#pragma once
#ifndef _GLOBAL_H_
#define _GLOBAL_H_

////////////////////////////////////////////////
////////////////////INCLUDES////////////////////
////////////////////////////////////////////////

#include <iostream>
#include <conio.h>
#include <cstring>
#include <Windows.h>
#include <ctime>

///////////////////////////////////////////////
////////////////////DEFINES////////////////////
///////////////////////////////////////////////

#define DEBUG

#define ERR_NO_ERR 0
#define ERR_FILE 10
#define ERR_MEMORY 20

#define PATH_NAME_LEN_MAX 32
#define PATH_LOG "./log/log.log"
#define PATH_LOG_MAP "./log/_map_log.log"
#define PATH_LEVEL_DEV "./levels/level_dev.level"
#define PATH_LEVEL_1 "./levels/level_1.level"
#define PATH_LEVEL_2 "./levels/level_2.level"
#define PATH_LEVEL_3 "./levels/level_3.level"


//////////////////////////////////////////////////
////////////////////ENUMIRATIONS//////////////////
//////////////////////////////////////////////////

enum class KBKey
{
	sysKeyShift = -0x20,
	sysKeyCtrl = -0x60,
	keyUpArrow = 0x48,
	keyDownArrow = 0x50,
	keyLeftArrow = 0x4b,
	keyRightArrow = 0x4d,
	keyReturn = 0x0d,
	keyT = 0x74,
	keyTU = 0x74 - 0x20,
	keyM = 0x6d,
	keyMU = 0x6d - 0x20,
	keyA = 0x61,
	keyAU = 0x61 - 0x20,
	keyE = 0x65,
	keyEU = 0x65 - 0x20,
	keyI = 0x69,
	keyIU = 0x69 - 0x20,
	keyS = 0x73,
	keySU = 0x73 - 0x20,
	key0 = 0x30,
	key1 = 0x31,
	key2 = 0x32,
	key3 = 0x33,
	key4 = 0x34,
	key5 = 0x35,
	key6 = 0x36,
	key7 = 0x37,
	key8 = 0x38,
	key9 = 0x39,
};


////////////////////////////////////////////////
////////////////////STRUCTURES//////////////////
////////////////////////////////////////////////

struct Point
{
	int x,
		y;
};


////////////////////////////////////////////////////////////
////////////////////FUNCTIONS_DECLARATION///////////////////
////////////////////////////////////////////////////////////

int log(const char *logString, const char *const logFileName = PATH_LOG);


#endif // !_GLOBAL_H_