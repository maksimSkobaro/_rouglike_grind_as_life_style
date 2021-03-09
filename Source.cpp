#include "RL_global.h"
#include "RL_world_struct.h"
#include "RL_entity_struct.h"

//	волновой алгоритм

int main()
{
	system("chcp 1251");

	World *pWorld = nullptr;
	worldInit(pWorld, {5, 10}, PATH_LEVEL_DEV);
	entityCharacterDie(pWorld->pEntity[EntityAdd(pWorld->pEntity, pWorld->entityAmount, EntitySymb::enemyDragon, {6,10})]);
	EntityAdd(pWorld->pEntity, pWorld->entityAmount, EntitySymb::store, {51,1});
	EntityAdd(pWorld->pEntity, pWorld->entityAmount, EntitySymb::enemyWarden, { 15,10 }, true, 3);

	while(true)
	{
		pWorld->pEntity[pWorld->mainCharacterID].character->expa += 10;
		char temp[32]{};
		char temp2[32]{};
		_itoa_s(pWorld->pEntity[pWorld->mainCharacterID].character->expa, temp2, 16, 10 );
		strcpy_s(temp, 8, temp2);
		worldUIStrAdd(pWorld->ConditionString, temp);
		system("cls");
		worldLogic(*pWorld);
		printWorldLevel(*pWorld);
		worldInput(*pWorld);
	}


	return ERR_NO_ERR;
}