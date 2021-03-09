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
	int globTick,
		globBigTick;

	int cellsRowsAmount,	//	максимальна y координата. задается worldLoadLevel()
		cellsColsAmount;	//	максимальна x координата. задается worldLoadLevel()
	Cell **pCell = nullptr;

	int	mainCharacterID,
		cameraID,
		cameraRange;

	int entityAmount;
	Entity *pEntity = nullptr;
	char levelName[64];
	char ConditionString[CAMERA_RANGE_MAX / 3 * 2 - 1][CONDITION_STR_ONELINE_MAX];
};


////////////////////////////////////////////////////////////
////////////////////FUNCTIONS_DECLARATION///////////////////
////////////////////////////////////////////////////////////

#ifdef DEBUG
//	Выводит отладочную информацию под вывод printWorldLevel()
void printWorldDebug(const World &world);
#endif // DEBUG
//	Загружает уровень из файла в массив[][] структур
int worldLoadLevel(World &world);
//	Инициализирует стандартными значениями World
int worldInit(World *&world, Point mainCharacterCoord = {3, 20}, const char *const worldName = PATH_LEVEL_1);
//	Корретно удаляет World
int worldDestruct(World *&world);
//	Ф-я вывода уровня из **Cell в консоль.
int printWorldLevel(const World &world, bool attackMode = false, Point attackPoint = {0,0});
//	обработка UI и строки сотояния
int worldPrintLevelUI(const char(&ConditionString)[CAMERA_RANGE_MAX / 3 * 2 - 1][CONDITION_STR_ONELINE_MAX], int curY);
//	Ф-я обрабатывающая нажатия на кнопки.
int worldInput(World &world);
//	Ф-я реализующая логику игры.
int worldLogic(World &world);
//	Ф-я для изменения времени.
void worldIncreaseHistoryTime(int &tick, int &bigTick);
//	Ф-я реализующая логику передвижения Entity.
int worldDirectionLogic(World &world, Entity &entity);
//	Ф-я области видимости, изучения карты.
void worldVisionLogic(World &world);
//	Ф-я атаки
int worldCharacterAttack(const World& world, Entity& entity, bool& isEOI);
//	Ф-я реализует механизм прокрутки камеры
void worldMapMode(World &world);
//	Ф-я корректного измененния положения Entity в пространстве. 
//	При телепортации на занятую клетку в isGhost моде, клетка перестает быть isGhost навсегда.
void worldEntityGoto(World &world, Entity &entity, Point toGoPoint, bool isGhost = false);
//	Ф-я реализующая логику работы spawner'ов(лагерей)
int worldEntitySpawnerLogic(World& world, int spawnerID);
//	Ф-я обновления UI
void worldUILogic(World& world);
//	Ф-я добавление новой строки состояние в UI
void worldUIStrAdd(char(&ConditionString)[CAMERA_RANGE_MAX / 3 * 2 - 1][CONDITION_STR_ONELINE_MAX], const char* newString);
//
//
//int systemUpMainCharacter(World& world, Entity& entity, EntitySymb nameCharacter);

#endif // !_RL_WORLD_STRUCT_H_
