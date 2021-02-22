#include "RL_main.h"
#include "RL_dataStructs.h"
#include "RL_mem.h"


#ifdef DEBUG

void printDebug(World &world)
{
	//	¬ывод айди, имени, координат, состо€ни€, каждого из Entity
	//	≈сли Entity имеет *Character != nullptr, то вывдо€тьс€ дополнительные данные
	for(int i = 0; i < world.entityAmount; i++)
	{
		printf_s("[%i/%i][%i]: %32s", world.pEntity[i].coords.x, world.pEntity[i].coords.y, world.pEntity[i].ID, world.pEntity[i].name);
		if(world.pEntity[i].character != nullptr)
		{
			printf_s("\tisAlive: %5s\tDMG: %4i\tHLTH: %4i\tMNA: %4i\tLVL: %4i\tINV: %i/%i\n", world.pEntity[i].character->isAlive ? "true" : "false", world.pEntity[i].character->damageCurrent, world.pEntity[i].character->healthCurrent, 
					 world.pEntity[i].character->manaCurrent, world.pEntity[i].character->level, world.pEntity[i].character->inventory.itemsAmount, world.pEntity[i].character->inventory.capacityCurrent);
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
	worldEntityAdd(pWorld->pEntity, pWorld->entityAmount, EntitySymb::enemyDragon, {10,10});


	while(true)
	{
		system("cls");
		printLevel(*pWorld);
		printDebug(*pWorld);
		worldInput(*pWorld);
		worldLogic(*pWorld);
	}


	return ERR_NO_ERR;
}