#pragma once
#ifndef _RL_ENTITY_STRUCT_H
#define _RL_ENTITY_STRUCT_H
#include "RL_global.h"

///////////////////////////////////////////////
////////////////////DEFINES////////////////////
///////////////////////////////////////////////

#define ENTITY_NAME_LEN_MAX 32
#define ITEM_NAME_LEN_MAX 64
#define INVENTORY_CAPACITY_MAX 32
#define SPAWN_AMOUNT_MAX 16

#define ERR_INVENTORY_ADD 100
#define ERR_INVENTORY_REMOVE 101
#define ERR_INVENTORY_USE_OUT_OF_RANGE 401
#define ERR_INVENTORY_USE_EQUIP_INDEX_FAIL 402
#define ERR_INVENTORY_BUY_LOW_MONEY 403
#define ERR_INVENTORY_USE 400
#define ERR_ENTITY_CREATION 200
#define ERR_ENTITY_REMOVE 201


///////////////////////////////////////////////////////
////////////////////DATA_STRUCTURES////////////////////
///////////////////////////////////////////////////////

enum class ItemID
{
	empty,
	gold,
	oldSword,
	dworfAxe,
	volcanSword,
	silverSpear,
	goldenSword,
	leatherArmor,
	hunterArmor,
	corgArmor,
	chainMail,
	silverArmor,
	goldenArmor,
	healFlaskLittle,
	healFlaskMedium,
	healFlaskLarge,

	_nextNotBuyable,

	dragonScaleArmor,
	godsMadeArmor,
	undeadKingArmor,
	justiceMantle,

	huntingGroundsSword,
	atlantAxe,
	spiritHammer,
	justiceHummer,
};

enum class Direction
{
	up,
	down,
	left,
	right,
	stay
};

enum class EntitySymb : char
{
	mainCharacter = '@',
	store = '$',
	enemyZombyDrop = 'z',
	enemyZomby = 'Z',
	enemySkeletonDrop = 's',
	enemySkeleton = 'S',
	enemyGiantDrop = 'g',
	enemyGiant = 'G',
	enemyLarvaDrop = 'l',
	enemyLarva = 'L',
	enemyCorgDrop = 'c',
	enemyCorg = 'C',
	enemyBeastmanDrop = 'b',
	enemyBeastman = 'B',
	enemyKriDrop = 'k',
	enemyKri = 'K',
	enemyJudgeDrop = 'j',
	enemyJudge = 'J',
	enemyDragonDrop = 'd',
	enemyDragon = 'D',
	camera = '?',
	spawner = '!',
	empty = ' '
};

enum class Team
{
	ally,
	neutral,
	enemy,
};

struct Item
{
	bool isEquiped,
		isEquipable;

	int dmgEffect,
		healthEffect,
		healEffect;

	EntitySymb additionDmgTo,
		reduceDamageFrom;

	int amount;	//	Количество предмета одного типа, если он стакается.
	int stackMax;	//	Максимальное кол-во предмета в 1 клетке.
	int sellPrice;
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

struct Character
{
	int level,
		expa,
		nextLevelExp,
		damageBase,
		damageModification,
		damageCurrent,
		healthBase,
		healthModification,
		healthCurrent,
		healthReal,
		manaBase,
		manaModifitaion,
		manaCurrent,
		visionRangeBase,
		visionRangeModification,
		visionRangeCurrent;

	int killExpReward;

	Point spawnPoint;

	Team team;

	bool isAlive;

	//Direction direction;
	Inventory inventory;
};

struct Spawner
{
	int IDs[SPAWN_AMOUNT_MAX];
	int maxIDs,
		curIDs;
	EntitySymb entityToSpawn;
};

struct Entity
{
	bool isInRange;
	int ID;
	Spawner *spawner;
	EntitySymb entitySymb;
	Character *character;
	Direction direction;
	Point coords;
	char name[ENTITY_NAME_LEN_MAX];
};


////////////////////////////////////////////////////////////
////////////////////FUNCTIONS_DECLARATION///////////////////
////////////////////////////////////////////////////////////

//	Изменяет кол-во предмета.
//	Работайте с инвентарем только через эти ф-и
int inventoryItemAdd(Inventory &inventory, ItemID itemID, int amount = 1);
int inventoryItemRemove(Inventory &inventory, ItemID itemID, int amount = 1, bool fullRemove = false);
int inventoryItemRemoveByID(Inventory &inventory, int itemIndex, int amount = 1, bool fullRemove = false);
int inventoryItemRelocate(Inventory &fromInventory, Inventory &toInventory, ItemID itemID, int amount = 1);
//	Создает объект Character, в Entity.
//	Если вы переприсваиваете Character * !почистите память с помощью EntityCharacterRemove()
int entityCharacterCreate(Entity &worldEntity, EntitySymb characterToCreateSymbol);
//	Ф-я убивает Character
int entityCharacterDie(Entity &worldEntity);
//	Ф-я высвобаждает память под *Character в Entity, присваивая *Character nullptr.
int entityCharacterRemove(Entity &worldEntity);
//	Ф-я создает объект Entity, так же создает Character, если того требует описание передоваемого типа.
int EntityAdd(Entity *&entity, int &entityAmount, EntitySymb entitySymb, Point coords = {0, 0}, bool isSpawner = false, int toSpawnCount = 0);
//	Ф-я корректно удаляет Entity
int EntityRemove(Entity *&entity, int &entityAmount, int ID);
//	depricated!
//	Ф-я возвращает ID первого найденого MainCharacter среди всех Entity
int getEntityMainCharacterID(const Entity *const worldEntity, int entityAmount);
//
//
int entitySpawnerRemove(Entity &entity);
//
//
int entitySpawnerCreate(Entity &entity, EntitySymb characterToSpawn, int toSpawnCount);
//
//
int entityLevelUpLogic(Entity &entity);
//	Ф-ии отрисовки и взаимодействия с инвентарем(ями)
void entityInventoryMode(Entity &entity);
void entityInventoryModeStore(Entity &mainEntity, Entity &targetEntity, bool &isLocalEOI);
void entityInventoryModeDrop(Entity &mainEntity, Entity &targetEntity, bool &isLocalEOI);
void InventoryStoreModeBuyAction(Inventory &inventory, Item *item, int amount);
void InventoryStoreModeSellAction(Inventory &inventory, Item *item, int amount);
void inventoryItemNormalize(Inventory &inventory, ItemID itemToNormalize);
//	Ф-я реализует корректное добавление опыта пероснажу
void characterExpIncrease(Character &character, int additionExp);
//	Ф-ии реализующие использование предметов
int inventoryItemUseByID(Entity &entity, int itemIndex);
int inventiryModeEquipMode(Character &character, int itemIndex);
//	Ф-ии-сеттеры для модификаций.
void characterModifDamageSet(Character &character, int newState);
void characterModifVisionSet(Character &character, int newState);
void characterModifHealthSet(Character &character, int newState);
void characterModifDamageIncrease(Character &character, int increase);
void characterModifVisionIncrease(Character &character, int increase);
void characterModifHealthIncrease(Character &character, int increase);
void itemInfoPrint(ItemID itemID);
//	Ф-ии для обработки урона/хила
void entityCharacterGetDamage(Entity &entity, int damageAmount, bool fullKill = false);
void entityCharacterGetHeal(Entity &entity, int healAmount, bool fullHeal = false);


#endif // !_RL_ENTITY_STRUCT_H

