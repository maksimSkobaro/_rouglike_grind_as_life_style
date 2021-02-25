#include "RL_global.h"
#include "RL_world_struct.h"
#include "RL_entity_struct.h"

//	SetConsoleTextAttribute
//	Волновой алгоритм

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