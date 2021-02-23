#include "RL_global.h"
#include "RL_world_struct.h"
#include "RL_entity_struct.h"

//	SetConsoleTextAttribute
//	\b
//	Волновой алгоритм

#ifdef DEBUG

void printDebug(World &world)
{
	//	Вывод айди, имени, координат, состояния, каждого из Entity
	//	Если Entity имеет *Character != nullptr, то вывдояться дополнительные данные
	for(int i = 0; i < world.entityAmount; i++)
	{
		printf_s("[%i/%i][%i]: %32s", world.pEntity[i].coords.x, world.pEntity[i].coords.y, world.pEntity[i].ID, world.pEntity[i].name);
		if(world.pEntity[i].character != nullptr)
		{
			printf_s("\tisAlive: %5s\tDMG: %4i\tHLTH: %4i\tMNA: %4i\tLVL: %4i\tINV: %i/%i\tisVisn: %5s", world.pEntity[i].character->isAlive ? "true" : "false", world.pEntity[i].character->damageCurrent, world.pEntity[i].character->healthCurrent, 
					 world.pEntity[i].character->manaCurrent, world.pEntity[i].character->level, world.pEntity[i].character->inventory.itemsAmount, world.pEntity[i].character->inventory.capacityCurrent, world.pEntity[i].isInRange ? "true" : "false");
		}
		putchar('\n');
	}
}

#endif // DEBUG


int main()
{
	system("chcp 1251");

	World *pWorld = nullptr;
	worldInit(pWorld, {5, 10}, PATH_LEVEL_DEV);
	EntityAdd(pWorld->pEntity, pWorld->entityAmount, EntitySymb::enemyDragon, {6,10});


	while(true)
	{
		system("cls");
		worldLogic(*pWorld);
		printLevel(*pWorld);
		printDebug(*pWorld);
		worldInput(*pWorld);
	}


	return ERR_NO_ERR;
}