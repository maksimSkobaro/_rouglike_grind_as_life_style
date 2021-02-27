#pragma once
#ifndef _RL_WORLD_STRUCT_H_
#define _RL_WORLD_STRUCT_H_
#include "RL_global.h"
#include "RL_entity_struct.h"

///////////////////////////////////////////////
////////////////////DEFINES////////////////////
///////////////////////////////////////////////

#define MAP_WIDTH_MAX 512
#define MAP_HEIGTH_MAX 512

#define CAMERA_RANGE_MAX 24
#define CONDITION_STR_ONELINE_MAX 64

#define ERR_UI_OUTPUT 300
#define ERR_UI_INPUT 301


///////////////////////////////////////////////////////
////////////////////DATA_STRUCTURES////////////////////
///////////////////////////////////////////////////////

enum class CellSymb : char
{
	ground = '.',
	stone = '&',
	wall = '#',
	empty = ' '
};

struct Cell
{
	bool isGhost;
	bool isReserched;
	bool isInRange;
	CellSymb cellSymb;
};

struct World
{
	int cellsRowsAmount,	//	����������� y ����������. �������� worldLoadLevel()
		cellsColsAmount;	//	����������� x ����������. �������� worldLoadLevel()
	Cell **pCell = nullptr;

	int	mainCharacterID,
		cameraID,
		cameraRange;
	bool isMapMode;

	int entityAmount;
	Entity *pEntity = nullptr;
	char levelName[64];
	char ConditionSting[CAMERA_RANGE_MAX / 3 * 2 - 1][CONDITION_STR_ONELINE_MAX];
};


////////////////////////////////////////////////////////////
////////////////////FUNCTIONS_DECLARATION///////////////////
////////////////////////////////////////////////////////////

//	��������� ������� �� ����� � ������[][] ��������
int worldLoadLevel(World &world);
//	�������������� ������������ ���������� World
int worldInit(World *&world, Point mainCharacterCoord = {3, 20}, const char *const worldName = PATH_LEVEL_1);
//	�������� ������� World
int worldDestruct(World *&world);
//	�-� ������ ������ �� **Cell � �������.
int printLevel(const World &world);
//	��������� UI � ������ ��������
int printLevelUI(const char(&conditionString)[CAMERA_RANGE_MAX / 3 * 2 - 1][CONDITION_STR_ONELINE_MAX], int cameraRange, int curY);
//	�-�� �������������� ������� �� ������.
int worldInput(World &world);
//	�-�� ����������� ������ ����.
int worldLogic(World &world);


#endif // !_RL_WORLD_STRUCT_H_
