#ifndef RL_DATASTRUCTS
#pragma once
#include "RL_main.h"
///////////////////////////////////////////////
////////////////////DEFINES////////////////////
///////////////////////////////////////////////
#define PATH_NAME_LEN_MAX 32
#define PATH_LEVEL_DEV "./levels/level_dev.level"
#define PATH_LEVEL_1 "./levels/level_1.level"
#define PATH_LEVEL_2 "./levels/level_2.level"
#define PATH_LEVEL_3 "./levels/level_3.level"

#define ENTITY_NAME_LEN_MAX 32
#define ITEM_NAME_LEN_MAX 32
#define INVENTORY_CAPACITY_MAX 32
#define MAP_WIDTH_MAX 512
#define MAP_HEIGTH_MAX 512

#define ERR_INVENTORY_ADD 100
#define ERR_INVENTORY_REMOVE 101
#define ERR_ENTITY_CREATION 200
#define ERR_ENTITY_REMOVE 201

///////////////////////////////////////////////////////
////////////////////DATA_STRUCTURES////////////////////
///////////////////////////////////////////////////////
enum class KBKey
{
	sysKeyShift = -0x20,
	sysKeyCtrl = -0x60,
	keyUpArrow = 0x48,
	keyDownArrow = 0x50,
	keyLeftArrow = 0x4b,
	keyRightArrow = 0x4d,
	keyReturn = 0x0d,
	keyM = 0x6d,
	keyMU = 0x6d - 0x20,
	keyA = 0x61,
	keyAU = 0x61 - 0x20,
	keyE = 0x45,
	keyEU = 0x45 - 0x20,
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

struct Point
{
	int x,
		y;
};

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

enum class ItemID
{
	empty,
	gold,
	oldSword,
	oldKnife,
	oldArmor,
	weakRingOfHealth,
	weakRingOfDamage,
	healFlaskLittle,
	healFlaskMedium,
	healFlaskLarge,
	manaFlaskLittle,
	manaFlaskMedium,
	manaFlaskLarge,
	_last
};

struct Item
{
	int amount;	//	Количество предмета одного типа, если он стакается.
	int stackMax;	//	Максимальное кол-во предмета в 1 клетке.
	ItemID itemID;
	char name[ITEM_NAME_LEN_MAX]{};
};

struct Inventory
{
	int capacityBase,
		capacityModiffication,
		capacityCurrent;
	int itemsAmount;	//	Кол-во заполненых ячеек инвентаря
	Item items[INVENTORY_CAPACITY_MAX]{};
};

enum class Direction
{
	up,
	down,
	left,
	right,
	stay
};

struct Character
{
	int level,
		damageBase,
		damageModification,
		damageCurrent,
		healthBase,
		healthModification,
		healthCurrent,
		manaBase,
		manaModifitaion,
		manaCurrent,
		visionRangeBase,
		visionRangeModification,
		visionRangeCurrent;

	bool isAlive;

	//Direction direction;
	Inventory inventory;
};

enum class EntitySymb : char
{
	mainCharacter = '@',
	store = '$',
	enemyWardenDrop = 'w',
	enemyWarden = 'W',
	enemyDragonDrop = 'd',
	enemyDragon = 'D',
	camera = '?',
	empty = ' '
};

struct Entity
{
	bool isInRange;
	int ID;
	EntitySymb entitySymb;
	Character *character;
	Direction direction;
	Point coords;
	char name[ENTITY_NAME_LEN_MAX]{};
};

struct World
{
	int cellsRowsAmount,	//	максимальна y координата. задается worldLoadLevel()
		cellsColsAmount;	//	максимальна x координата. задается worldLoadLevel()
	Cell **pCell = nullptr;
	int entityAmount = 0,
		mainCharacterID,
		cameraID,
		cameraRange;
	bool isMapMode;

	Entity *pEntity = nullptr;
	char levelName[64];
};

////////////////////////////////////////////////////////////
////////////////////FUNCTIONS_DECLARATION///////////////////
////////////////////////////////////////////////////////////

//	Инициализирует стандартными значениями World
int worldInit(World *&world, Point mainCharacterCoord = {3, 20}, const char *const worldName = PATH_LEVEL_1);
//	Корретно удаляет World
int worldDestruct(World *&world);
//	Загружает уровень из файла в массив[][] структур
int worldLoadLevel(World &world);
//	Увеличивает кол-во предмета, или если его небыло то добавляет
//	Работайте с инвентарем только через эти ф-и
int inventoryItemAdd(Inventory &inventory, ItemID itemID, int amount = 1);
//	Уменьшает кол-во предмета, или если его кол-во <= 0 удаляет его.
//	Работайте с инвентарем только через эти ф-ии
int inventoryItemRemove(Inventory &inventory, ItemID itemID, int amount = 1, bool fullRemove = false);
//	Создает объект Character, в Entity.
//	Если вы переприсваиваете Character * !почистите память с помощью EntityCharacterRemove()
int entityCharacterCreate(Entity &worldEntity, EntitySymb characterToCreateSymbol);
//	Ф-я убивает персонажа
int entityCharacterDie(Entity &worldEntity);
//	Ф-я высвобаждает память под *Character в Entity, присваивая *Character nullptr.
int entityCharacterRemove(Entity &worldEntity);
//	Ф-я создает объект Entity, так же создает Character, если того требует описание передоваемого типа.
int worldEntityAdd(Entity *&entity, int &entityAmount, EntitySymb entitySymb, Point coords = {0, 0});
//	Ф-я корректно удаляет Entity
int worldEntityRemove(Entity *&entity, int &entityAmount, int ID);
//	Ф-я вывода уровня из **Cell в консоль.
int printLevel(const World &world);
//	depricated!
//	Ф-я возвращает ID первого найденого MainCharacter среди всех Entity
int getEntityMainCharacterID(const Entity *const worldEntity, int entityAmount);
//	Ф-ия обрабатывающая нажатия на кнопки.
int worldInput(World &world);
//	Ф-ия реализующая логику игры.
int worldLogic(World &world);

////////////////////////////////////////////////////////////
////////////////////FUNCTIONS_DEFINITION////////////////////
////////////////////////////////////////////////////////////

int worldInit(World *&world, Point mainCharacterCoords, const char *const worldName)
{
	World *pWorldNew = (World *) malloc(sizeof(*pWorldNew));
	if(!pWorldNew)
	{
		log("worldInit(): Ошибка выделения памяти. *pWorldNew = nullptr.");
		exit(ERR_MEMORY);
	}

	pWorldNew->pEntity = nullptr;
	pWorldNew->entityAmount = 0;
	pWorldNew->mainCharacterID = worldEntityAdd(pWorldNew->pEntity, pWorldNew->entityAmount,
												EntitySymb::mainCharacter, mainCharacterCoords);
	pWorldNew->cameraID = worldEntityAdd(pWorldNew->pEntity, pWorldNew->entityAmount,
										 EntitySymb::camera, mainCharacterCoords);
	pWorldNew->cameraRange = 18;
	pWorldNew->isMapMode = false;

	pWorldNew->pCell = nullptr;
	pWorldNew->cellsColsAmount = 0;
	pWorldNew->cellsRowsAmount = 0;
	strcpy_s(pWorldNew->levelName, PATH_NAME_LEN_MAX, worldName);
	worldLoadLevel(*pWorldNew);

	worldDestruct(world);
	world = pWorldNew;

	return ERR_NO_ERR;
}

int worldDestruct(World *&world)
{
	if(!world)
	{
		return ERR_NO_ERR;
	}

	for(int i = 0; i < world->entityAmount; i++)
	{
		worldEntityRemove(world->pEntity, world->entityAmount, world->pEntity[i].ID);
	}

	for(int i = 0; i < world->cellsColsAmount; i++)
	{
		free(world->pCell[i]);
	}
	free(world->pCell);

	free(world);
	world = nullptr;

	return ERR_NO_ERR;
}

int worldLoadLevel(World &world)
{
	world.pCell = (Cell **) malloc(sizeof(*world.pCell) * MAP_WIDTH_MAX);

	if(!world.pCell)
	{
		log("worldLoadLevel(): не получилось выделить память. **pCell = nullptr");
		exit(ERR_MEMORY);
	}

	for(int i = 0; i < MAP_WIDTH_MAX; i++)
	{
		world.pCell[i] = (Cell *) malloc(sizeof(**world.pCell) * MAP_HEIGTH_MAX);

		if(!world.pCell)
		{
			log("worldLoadLevel(): не получилось выделить память. *pCell = nullptr");
			exit(ERR_MEMORY);
		}
	}

	char ptrLevelLine[MAP_WIDTH_MAX]{};

	FILE *fLevel = nullptr;
	if(fopen_s(&fLevel, world.levelName, "r"))
	{
		log("worldLoadLevel(): не получилось открыть файл с уровнем. *fLevel = nullptr");
		exit(ERR_FILE);
	}

	int row = 0;
	int col = 0;

	while(!feof(fLevel))
	{

		char endSymb;
		bool isEmpty = false;

		do
		{

			endSymb = '\0';

			if(!fgets(ptrLevelLine, MAP_WIDTH_MAX, fLevel))
			{
				isEmpty = true;
			}
			else
			{
				isEmpty = false;
			}

			if(strchr(ptrLevelLine, '\n'))
			{
				endSymb = '\n';
			}

			if(strchr(ptrLevelLine, endSymb) == ptrLevelLine)
			{
				isEmpty = true;
			}

		} while(isEmpty && !feof(fLevel));

		if(!isEmpty)
		{
			col = 0;
		}

		for(; ptrLevelLine[col] != endSymb && !isEmpty; col++)
		{
			world.pCell[col][row].cellSymb = (CellSymb) ptrLevelLine[col];
			world.pCell[col][row].isInRange = false;
			world.pCell[col][row].isReserched = false;

			switch((CellSymb) ptrLevelLine[col])
			{
			case CellSymb::ground:
				world.pCell[col][row].isGhost = true;
				break;
			case CellSymb::stone:
				world.pCell[col][row].isGhost = false;
				break;
			case CellSymb::wall:
				world.pCell[col][row].isGhost = false;
				break;
			case CellSymb::empty:
				world.pCell[col][row].isGhost = true;
				break;
			default:
				log("worldLoadLevel(): Получен неизвестный CellSymb");
				world.pCell[col][row].isGhost = true;
				break;
			}
		}

		if(!isEmpty)
			row++;
	}

	fclose(fLevel);

#ifdef DEBUG

	char *tempStr = (char *) malloc(col + 1);

	for(int rw = 0; rw < row; rw++)
	{
		for(int cl = 0; cl < col; cl++)
		{
			tempStr[cl] = (char) world.pCell[cl][rw].cellSymb;
		}
		tempStr[col] = '\0';
		log(tempStr, PATH_LOG_MAP);
	}

	free(tempStr);
	log("---------------------------------------------------", PATH_LOG_MAP);

#endif // DEBUG

	world.cellsRowsAmount = row;
	world.cellsColsAmount = col;

	return ERR_NO_ERR;
}

int inventoryItemAdd(Inventory &inventory, ItemID itemID, int amount)
{
	while(amount != 0)
	{
		bool wasInNotFull = false;

		int i = 0;
		for(; i < inventory.itemsAmount; i++)
		{
			if(itemID == inventory.items[i].itemID && inventory.items[i].stackMax - inventory.items[i].amount > 0)
			{
				wasInNotFull = true;
				break;
			}
		}

		if(wasInNotFull)
		{
			int tmpAmount = inventory.items[i].stackMax - (amount + inventory.items[i].amount);
			inventory.items[i].amount += tmpAmount >= 0 ? amount : amount - abs(tmpAmount);
			amount = tmpAmount >= 0 ? 0 : abs(tmpAmount);
			if(amount < 0)
			{
				log("inventoryItemAdd(): amount < 0 (в 1 блоке)");
			}
		}
		else
		{

			switch(itemID)
			{
			case ItemID::gold:
				{
					char name[] = "Золото";
					strcpy_s(inventory.items[inventory.itemsAmount].name, ITEM_NAME_LEN_MAX, name);
					inventory.items[inventory.itemsAmount].stackMax = 50000;
				}
				break;
			case ItemID::oldSword:
				{
					char name[] = "Поношенный старый меч";
					strcpy_s(inventory.items[inventory.itemsAmount].name, ITEM_NAME_LEN_MAX, name);
					inventory.items[inventory.itemsAmount].stackMax = 1;
				}
				break;
			case ItemID::oldArmor:
				{
					char name[] = "Поношенная старая броня";
					strcpy_s(inventory.items[inventory.itemsAmount].name, ITEM_NAME_LEN_MAX, name);
					inventory.items[inventory.itemsAmount].stackMax = 1;
				}
				break;
			case ItemID::weakRingOfHealth:
				{
					char name[] = "Слабое кольцо добавочного здоровья";
					strcpy_s(inventory.items[inventory.itemsAmount].name, ITEM_NAME_LEN_MAX, name);
					inventory.items[inventory.itemsAmount].stackMax = 1;
				}
				break;
			case ItemID::weakRingOfDamage:
				{
					char name[] = "Слабое кольцо добавочного урона";
					strcpy_s(inventory.items[inventory.itemsAmount].name, ITEM_NAME_LEN_MAX, name);
					inventory.items[inventory.itemsAmount].stackMax = 1;
				}
				break;
			case ItemID::healFlaskLittle:
				{
					char name[] = "Малое зелье регенерации";
					strcpy_s(inventory.items[inventory.itemsAmount].name, ITEM_NAME_LEN_MAX, name);
					inventory.items[inventory.itemsAmount].stackMax = 120;
				}
				break;
			case ItemID::healFlaskMedium:
				{
					char name[] = "Среднее зелье регенерации";
					strcpy_s(inventory.items[inventory.itemsAmount].name, ITEM_NAME_LEN_MAX, name);
					inventory.items[inventory.itemsAmount].stackMax = 100;
				}
				break;
			case ItemID::healFlaskLarge:
				{
					char name[] = "Большое зелье регенерации";
					strcpy_s(inventory.items[inventory.itemsAmount].name, ITEM_NAME_LEN_MAX, name);
					inventory.items[inventory.itemsAmount].stackMax = 60;
				}
				break;
			case ItemID::manaFlaskLittle:
				{
					char name[] = "Малое зелье маны";
					strcpy_s(inventory.items[inventory.itemsAmount].name, ITEM_NAME_LEN_MAX, name);
					inventory.items[inventory.itemsAmount].stackMax = 120;
				}
				break;
			case ItemID::manaFlaskMedium:
				{
					char name[] = "Среднее зелье маны";
					strcpy_s(inventory.items[inventory.itemsAmount].name, ITEM_NAME_LEN_MAX, name);
					inventory.items[inventory.itemsAmount].stackMax = 100;
				}
				break;
			case ItemID::manaFlaskLarge:
				{
					char name[] = "Большое зелье регенерации";
					strcpy_s(inventory.items[inventory.itemsAmount].name, ITEM_NAME_LEN_MAX, name);
					inventory.items[inventory.itemsAmount].stackMax = 60;
				}
				break;
			default:
				{
					log("inventoryItemAdd(): Неизвестный ItemID");
					char name[] = "?_Пусто";
					strcpy_s(inventory.items[inventory.itemsAmount].name, ITEM_NAME_LEN_MAX, name);
					inventory.items[inventory.itemsAmount].stackMax = 100;
				}
				break;
			}

			int tmpAmount = inventory.items[inventory.itemsAmount].stackMax - (amount + inventory.items[inventory.itemsAmount].amount);
			inventory.items[inventory.itemsAmount].amount += tmpAmount >= 0 ? amount : amount - abs(tmpAmount);
			amount = tmpAmount >= 0 ? 0 : abs(tmpAmount);
			inventory.items[inventory.itemsAmount].itemID = itemID;

			if(amount < 0)
			{
				log("inventoryItemAdd(): amount < 0 (во 2 блоке)");
			}

			inventory.itemsAmount++;
		}
	}

	return ERR_NO_ERR;
}

int inventoryItemRemove(Inventory &inventory, ItemID itemID, int amount, bool fullRemove)
{
	if(fullRemove)
	{
		amount = 1;
	}

	bool wasIn = true;

	while(amount != 0 && wasIn)
	{
		wasIn = false;

		int i = 0;
		for(; i < inventory.itemsAmount; i++)
		{
			if(itemID == inventory.items[i].itemID)
			{
				wasIn = true;

				int tmpAmount = inventory.items[i].amount - amount;
				if(fullRemove)
				{
					tmpAmount = 1;
				}

				if(tmpAmount <= 0 || fullRemove)
				{
					for(int j = i; j < inventory.itemsAmount - 1; j++)
					{
						inventory.items[j] = inventory.items[j + 1];
					}
					inventory.items[inventory.itemsAmount].amount = 0;
					inventory.items[inventory.itemsAmount].itemID = ItemID::empty;
					inventory.items[inventory.itemsAmount].stackMax = 0;
					char name[] = "";
					strcpy_s(inventory.items[inventory.itemsAmount--].name, ITEM_NAME_LEN_MAX, name);
					amount = abs(tmpAmount);
				}
				else
				{
					inventory.items[i].amount -= amount;
					amount = 0;
				}
				break;
			}
		}
	}

	return ERR_NO_ERR;
}

int entityCharacterCreate(Entity &worldEntity, EntitySymb characterToCreateSymbol)
{
	Character *&pCharacter = worldEntity.character;

	pCharacter = (Character *) malloc(sizeof(*pCharacter));

	if(!pCharacter)
	{
		log("entityCharacterCreate(): ошибка выделения памяти. *pCharacter = nullptr.");
		exit(ERR_MEMORY);
	}


	//	Присваивание стнадартных значений при создании персонажей
	switch(characterToCreateSymbol)
	{
	case EntitySymb::mainCharacter:
		pCharacter->level = 1;
		pCharacter->inventory.itemsAmount = 0;
		pCharacter->inventory.capacityBase = 4;
		pCharacter->inventory.capacityModiffication = 0;
		pCharacter->inventory.capacityCurrent = pCharacter->inventory.capacityBase + pCharacter->inventory.capacityModiffication;
		pCharacter->damageBase = 50;
		pCharacter->damageModification = 0;
		pCharacter->damageCurrent = pCharacter->damageBase + pCharacter->damageModification;
		pCharacter->healthBase = 300;
		pCharacter->healthModification = 0;
		pCharacter->healthCurrent = pCharacter->healthBase + pCharacter->healthModification;
		pCharacter->manaBase = 100;
		pCharacter->manaModifitaion = 0;
		pCharacter->manaCurrent = pCharacter->manaBase + pCharacter->manaModifitaion;
		pCharacter->visionRangeBase = 3;
		pCharacter->visionRangeModification = 0;
		pCharacter->visionRangeCurrent = pCharacter->visionRangeBase + pCharacter->visionRangeModification;
		break;
	case EntitySymb::store:
		pCharacter->level = 100;
		pCharacter->inventory.itemsAmount = 0;
		pCharacter->inventory.capacityBase = 0;
		pCharacter->inventory.capacityModiffication = INVENTORY_CAPACITY_MAX;
		pCharacter->inventory.capacityCurrent = pCharacter->inventory.capacityBase + pCharacter->inventory.capacityModiffication;
		pCharacter->damageBase = 0;
		pCharacter->damageModification = 50000;
		pCharacter->damageCurrent = pCharacter->damageBase + pCharacter->damageModification;
		pCharacter->healthBase = 5;
		pCharacter->healthModification = 50000;
		pCharacter->healthCurrent = pCharacter->healthBase + pCharacter->healthModification;
		pCharacter->manaBase = 0;
		pCharacter->manaModifitaion = 15000;
		pCharacter->manaCurrent = pCharacter->manaBase + pCharacter->manaModifitaion;
		pCharacter->visionRangeBase = 1;
		pCharacter->visionRangeModification = 9;
		pCharacter->visionRangeCurrent = pCharacter->visionRangeBase + pCharacter->visionRangeModification;
		break;
	case EntitySymb::enemyWarden:
		pCharacter->level = 1;
		pCharacter->inventory.itemsAmount = 0;
		pCharacter->inventory.capacityBase = 2;
		pCharacter->inventory.capacityModiffication = 0;
		pCharacter->inventory.capacityCurrent = pCharacter->inventory.capacityBase + pCharacter->inventory.capacityModiffication;
		pCharacter->damageBase = 10;
		pCharacter->damageModification = 0;
		pCharacter->damageCurrent = pCharacter->damageBase + pCharacter->damageModification;
		pCharacter->healthBase = 30;
		pCharacter->healthModification = 0;
		pCharacter->healthCurrent = pCharacter->healthBase + pCharacter->healthModification;
		pCharacter->manaBase = 10;
		pCharacter->manaModifitaion = 0;
		pCharacter->manaCurrent = pCharacter->manaBase + pCharacter->manaModifitaion;
		pCharacter->visionRangeBase = 2;
		pCharacter->visionRangeModification = 0;
		pCharacter->visionRangeCurrent = pCharacter->visionRangeBase + pCharacter->visionRangeModification;
		break;
	case EntitySymb::enemyDragon:
		pCharacter->level = 10;
		pCharacter->inventory.itemsAmount = 0;
		pCharacter->inventory.capacityBase = 1;
		pCharacter->inventory.capacityModiffication = 0;
		pCharacter->inventory.capacityCurrent = pCharacter->inventory.capacityBase + pCharacter->inventory.capacityModiffication;
		pCharacter->damageBase = 150;
		pCharacter->damageModification = 0;
		pCharacter->damageCurrent = pCharacter->damageBase + pCharacter->damageModification;
		pCharacter->healthBase = 1200;
		pCharacter->healthModification = 0;
		pCharacter->healthCurrent = pCharacter->healthBase + pCharacter->healthModification;
		pCharacter->manaBase = 400;
		pCharacter->manaModifitaion = 0;
		pCharacter->manaCurrent = pCharacter->manaBase + pCharacter->manaModifitaion;
		pCharacter->visionRangeBase = 4;
		pCharacter->visionRangeModification = 2;
		pCharacter->visionRangeCurrent = pCharacter->visionRangeBase + pCharacter->visionRangeModification;
		break;
	default:
		free(worldEntity.character);
		worldEntity.character = nullptr;
		break;
	}

	return ERR_NO_ERR;
}

int entityCharacterDie(Entity &worldEntity)
{
	//	Сценарии смерти персонажа:
	worldEntity.direction = Direction::stay;
	worldEntity.character->isAlive = false;
	worldEntity.character->inventory.itemsAmount = 0;

	switch(worldEntity.entitySymb)
	{
	case EntitySymb::mainCharacter:
		break;
	case EntitySymb::enemyWarden:
		worldEntity.entitySymb = EntitySymb::enemyWardenDrop;
		if(rand() % 2)
		{
			switch(rand() % 8)
			{
			case 0:
			case 1:
			case 6:
				inventoryItemAdd(worldEntity.character->inventory, ItemID::gold, 15 + rand() % 11);
				break;
			case 2:
				inventoryItemAdd(worldEntity.character->inventory, ItemID::healFlaskLittle, 1 + rand() % 2);
				break;
			case 3:
				inventoryItemAdd(worldEntity.character->inventory, ItemID::manaFlaskLittle, 1);
				break;
			case 4:
				inventoryItemAdd(worldEntity.character->inventory, ItemID::oldArmor, 1);
				break;
			case 5:
			case 7:
				inventoryItemAdd(worldEntity.character->inventory, ItemID::oldSword, 1);
				break;
			}
		}
		break;
	case EntitySymb::enemyDragon:

		worldEntity.entitySymb = EntitySymb::enemyDragonDrop;
		inventoryItemAdd(worldEntity.character->inventory, ItemID::gold, 2000 + abs(rand() * rand()) % 1000);
		break;
	}

	return ERR_NO_ERR;

}

int entityCharacterRemove(Entity &worldEntity)
{
	free(worldEntity.character);
	worldEntity.character = nullptr;
	return ERR_NO_ERR;
}

int worldEntityAdd(Entity *&entity, int &entityAmount, EntitySymb entitySymb, Point coords)
{
	static int entityID = 0;

	Entity *pEntityNew = (Entity *) malloc(sizeof(*pEntityNew) * ++entityAmount);

	if(!pEntityNew)
	{
		log("worldEntityAdd(): Не удалось выделить память. pEntityNew = nullptr");
		exit(ERR_MEMORY);
	}

	for(int i = 0; i < entityAmount - 1; i++)
	{
		pEntityNew[i] = entity[i];
	}

	entityCharacterCreate(pEntityNew[entityAmount - 1], entitySymb);

	pEntityNew[entityAmount - 1].entitySymb = entitySymb;
	pEntityNew[entityAmount - 1].isInRange = false;
	pEntityNew[entityAmount - 1].ID = entityID++;
	pEntityNew[entityAmount - 1].coords = coords;
	pEntityNew[entityAmount - 1].direction = Direction::stay;

	switch(entitySymb)
	{
	case EntitySymb::mainCharacter:
		{
			char name[ENTITY_NAME_LEN_MAX] = "М'айк лжец";	//	Да, это рофл мы его переназавем.
			strcpy_s(pEntityNew[entityAmount - 1].name, ENTITY_NAME_LEN_MAX, name);
		}
		break;
	case EntitySymb::store:
		{
			char name[ENTITY_NAME_LEN_MAX] = "Странствующий торговец";
			strcpy_s(pEntityNew[entityAmount - 1].name, ENTITY_NAME_LEN_MAX, name);
		}
		break;
	case EntitySymb::enemyWarden:
		{
			char name[ENTITY_NAME_LEN_MAX] = "Защитник подземелия";
			strcpy_s(pEntityNew[entityAmount - 1].name, ENTITY_NAME_LEN_MAX, name);
		}
		break;
	case EntitySymb::enemyDragon:
		{
			char name[ENTITY_NAME_LEN_MAX] = "Дракон";
			strcpy_s(pEntityNew[entityAmount - 1].name, ENTITY_NAME_LEN_MAX, name);
		}
		break;
	case EntitySymb::camera:
		{
			char name[ENTITY_NAME_LEN_MAX] = "_Camera";
			strcpy_s(pEntityNew[entityAmount - 1].name, ENTITY_NAME_LEN_MAX, name);
		}
		break;
	default:
		{
			log("worldEntityAdd(): Неизветсный тип добавляемого Entity.");
			char name[ENTITY_NAME_LEN_MAX] = "_?_Entity";
			strcpy_s(pEntityNew[entityAmount - 1].name, ENTITY_NAME_LEN_MAX, name);
		}
		break;
	}

	free(entity);
	entity = pEntityNew;

	return entityID - 1;
}

int worldEntityRemove(Entity *&entity, int &entityAmount, int ID)
{
	bool wasIn = false;

	int i = 0;
	for(; i < entityAmount; i++)
	{
		if(entity[i].ID == ID)
		{
			wasIn = true;
			break;
		}
	}

	if(wasIn)
	{
		for(int j = i; j < entityAmount - 1; j++)
		{
			entity[j] = entity[j + 1];
		}
		entityCharacterRemove(entity[--entityAmount]);
		entity[entityAmount].entitySymb = EntitySymb::empty;
		entity[entityAmount].direction = Direction::stay;
		entity[entityAmount].name[0] = '\0';
		entity[entityAmount].coords = {0,0};
		entity[entityAmount].isInRange = false;
	}
	else
	{
		log("worldEntityRemove(): ошибка удаления Entity. Entity не был найден по ID");
#ifdef DEBUG
		exit(ERR_ENTITY_REMOVE);
#else
		return ERR_ENTITY_REMOVE;
#endif // DEBUG

	}

	return ERR_NO_ERR;
}

int printLevel(const World &world)
{
	for(int i = world.pEntity[world.cameraID].coords.y - world.cameraRange / 3; i != (world.pEntity[world.cameraID].coords.y + world.cameraRange / 3) + 1; i++)
	{
		for(int j = world.pEntity[world.cameraID].coords.x - world.cameraRange; j != world.pEntity[world.cameraID].coords.x + world.cameraRange + 1; j++)
		{
			if(i < 0 || i >= world.cellsRowsAmount || j < 0 || j >= world.cellsColsAmount || !world.pCell[j][i].isReserched)
			{
				putchar((char) CellSymb::empty);
				continue;
			}
			else
			{
				putchar((char) world.pCell[j][i].cellSymb);
			}

			//if(!world.pCell[j][i].isGhost)
			{

				for(int k = 0; k < world.entityAmount; k++)
				{
					if(world.pEntity[k].isInRange && world.pEntity[k].coords.x == j && world.pEntity[k].coords.y == i && world.pEntity[k].ID != world.pEntity[world.cameraID].ID)
					{
						putchar('\b');
						putchar((char) world.pEntity[k].entitySymb);
					}
				}
			}
		}

		putchar('\n');

	}

	return ERR_NO_ERR;
}

//	depricated!
int getEntityMainCharacterID(const Entity *const worldEntity, int entityAmount)
{
	int id = -1;
	for(int i = 0; i < entityAmount; i++)
	{
		if(worldEntity[i].entitySymb == EntitySymb::mainCharacter)
		{
			id = worldEntity[i].ID;
		}
		break;
	}

	if(id == -1)
	{
		log("getWorldMainCharacterID(): Идентификатор MainCharacter не был найден среди существующих Entity.");
	}

	return id;
}

int worldInput(World &world)
{
	bool isEOI = false;	//	isEOI демонстрирует закончен ли ввод. (EOI - End of input)

	do
	{
		switch((KBKey) _getch())
		{
		case KBKey::keyUpArrow:
			if(!world.isMapMode)
			{
				world.pEntity[world.mainCharacterID].direction = Direction::up;
				world.pEntity[world.cameraID].direction = Direction::stay;
			}
			else
			{
				world.pEntity[world.mainCharacterID].direction = Direction::stay;
				world.pEntity[world.cameraID].direction = Direction::up;
			}
			isEOI = true;
			break;
		case KBKey::keyDownArrow:
			if(!world.isMapMode)
			{
				world.pEntity[world.mainCharacterID].direction = Direction::down;
				world.pEntity[world.cameraID].direction = Direction::stay;
			}
			else
			{
				world.pEntity[world.mainCharacterID].direction = Direction::stay;
				world.pEntity[world.cameraID].direction = Direction::down;
			}
			isEOI = true;
			break;
		case KBKey::keyLeftArrow:
			if(!world.isMapMode)
			{
				world.pEntity[world.mainCharacterID].direction = Direction::left;
				world.pEntity[world.cameraID].direction = Direction::stay;
			}
			else
			{
				world.pEntity[world.mainCharacterID].direction = Direction::stay;
				world.pEntity[world.cameraID].direction = Direction::left;
			}
			isEOI = true;
			break;
		case KBKey::keyRightArrow:
			if(!world.isMapMode)
			{
				world.pEntity[world.mainCharacterID].direction = Direction::right;
				world.pEntity[world.cameraID].direction = Direction::stay;
			}
			else
			{
				world.pEntity[world.mainCharacterID].direction = Direction::stay;
				world.pEntity[world.cameraID].direction = Direction::right;
			}
			isEOI = true;
			break;
		case KBKey::keyReturn:
			if(!world.isMapMode)
			{
				world.pEntity[world.mainCharacterID].direction = Direction::stay;
				world.pEntity[world.cameraID].direction = Direction::stay;
			}
			else
			{
				world.pEntity[world.mainCharacterID].direction = Direction::stay;
				world.pEntity[world.cameraID].direction = Direction::stay;
			}
			isEOI = true;
			break;
		case KBKey::keyM:
			world.isMapMode = !world.isMapMode;
			break;
		case KBKey::key9:
			exit(ERR_NO_ERR);
			break;
		default:
			break;	//	сообщение в UI : нет такой кнопки
		}
	} while(!isEOI);

	return ERR_NO_ERR;
}

int worldLogic(World &world)
{
	// Entity - эвенты
	for(int i = 0; i < world.entityAmount; i++)
	{
		// Привязка камеры к основному персонажу. Режим карты.
		if(!world.isMapMode)
		{
			world.pEntity[world.cameraID].coords = world.pEntity[world.mainCharacterID].coords;
		}

		// Передвижение Entity
		switch(world.pEntity[i].direction)
		{
		case Direction::up:
			if(world.pCell[world.pEntity[i].coords.x][world.pEntity[i].coords.y - 1].isGhost)
			{
				world.pCell[world.pEntity[i].coords.x][world.pEntity[i].coords.y - 1].isGhost = false;
				world.pCell[world.pEntity[i].coords.x][world.pEntity[i].coords.y].isGhost = true;
				world.pEntity[i].coords.y -= 1;
			}
			break;
		case Direction::down:
			if(world.pCell[world.pEntity[i].coords.x][world.pEntity[i].coords.y + 1].isGhost)
			{
				world.pCell[world.pEntity[i].coords.x][world.pEntity[i].coords.y + 1].isGhost = false;
				world.pCell[world.pEntity[i].coords.x][world.pEntity[i].coords.y].isGhost = true;
				world.pEntity[i].coords.y += 1;
			}
			break;
		case Direction::left:
			if(world.pCell[world.pEntity[i].coords.x - 1][world.pEntity[i].coords.y].isGhost)
			{
				world.pCell[world.pEntity[i].coords.x - 1][world.pEntity[i].coords.y].isGhost = false;
				world.pCell[world.pEntity[i].coords.x][world.pEntity[i].coords.y].isGhost = true;
				world.pEntity[i].coords.x -= 1;
			}
			break;
		case Direction::right:
			if(world.pCell[world.pEntity[i].coords.x + 1][world.pEntity[i].coords.y].isGhost)
			{
				world.pCell[world.pEntity[i].coords.x + 1][world.pEntity[i].coords.y].isGhost = false;
				world.pCell[world.pEntity[i].coords.x][world.pEntity[i].coords.y].isGhost = true;
				world.pEntity[i].coords.x += 1;
			}
			break;
		case Direction::stay:
			if(world.pCell[world.pEntity[i].coords.x][world.pEntity[i].coords.y].isGhost)
			{
				world.pCell[world.pEntity[i].coords.x][world.pEntity[i].coords.y].isGhost = false;
			}
			break;
		default:
			log("worldLogic(): Получено не существующее Direction");
			break;
		}

		// Entity.Character - эвенты
		if(world.pEntity[i].character != nullptr)
		{
			//	Entity.Character MainCharacter - эвенты
			if(world.pEntity[i].ID == world.mainCharacterID)
			{
				//	Сис-ма изучения карты, вижн на Entity
				for(int q = 0; q < world.entityAmount; q++)
				{
						world.pEntity[q].isInRange = false;
				}

				for(int curY = world.pEntity[i].coords.y, _i = 0; curY <= world.pEntity[i].coords.y + world.pEntity[i].character->visionRangeCurrent; curY++, _i++)
				{
					for(int curX = world.pEntity[i].coords.x; curX <= world.pEntity[i].coords.x + world.pEntity[i].character->visionRangeCurrent - _i; curX++)
					{
						int tmpY = curY - 2 * abs(world.pEntity[i].coords.y - curY);
						int tmpX = curX - 2 * abs(world.pEntity[i].coords.x - curX);



						for(int q = 0; q < world.entityAmount; q++)
						{
							if((world.pEntity[q].coords.x == curX && world.pEntity[q].coords.y == curY) || (world.pEntity[q].coords.x == tmpX && world.pEntity[q].coords.y == curY)||
							  (world.pEntity[q].coords.x == curX && world.pEntity[q].coords.y == tmpY) || (world.pEntity[q].coords.x == tmpX && world.pEntity[q].coords.y == tmpY))
							{
								world.pEntity[q].isInRange = true;
							}
						}

						world.pCell[curX][curY].isReserched = true;


						if(tmpX < world.cellsColsAmount && tmpX >= 0)
						{
							world.pCell[tmpX][curY].isReserched = true;

							if(tmpY < world.cellsRowsAmount && tmpY >= 0)
							{
								world.pCell[tmpX][tmpY].isReserched = true;
							}
						}

						world.pCell[curX][tmpY].isReserched = true;
					}
				}
			}
		}
	}

	return ERR_NO_ERR;
}

#endif // !RL_DATASTRUCTS