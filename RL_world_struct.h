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
	int cellsRowsAmount,	//	максимальна y координата. задается worldLoadLevel()
		cellsColsAmount;	//	максимальна x координата. задается worldLoadLevel()
	Cell **pCell = nullptr;

	int	mainCharacterID,
		cameraID,
		cameraRange;
	bool isMapMode;

	int entityAmount = 0;
	Entity *pEntity = nullptr;
	char levelName[64];
};


////////////////////////////////////////////////////////////
////////////////////FUNCTIONS_DECLARATION///////////////////
////////////////////////////////////////////////////////////

//	Загружает уровень из файла в массив[][] структур
int worldLoadLevel(World &world);
//	Инициализирует стандартными значениями World
int worldInit(World *&world, Point mainCharacterCoord = {3, 20}, const char *const worldName = PATH_LEVEL_1);
//	Корретно удаляет World
int worldDestruct(World *&world);
//	Ф-я вывода уровня из **Cell в консоль.
int printLevel(const World &world);
//	Ф-ия обрабатывающая нажатия на кнопки.
int worldInput(World &world);
//	Ф-ия реализующая логику игры.
int worldLogic(World &world);


#endif // !_RL_WORLD_STRUCT_H_
