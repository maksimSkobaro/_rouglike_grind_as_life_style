#include "RL_global.h"
#include "RL_world_struct.h"
#include "RL_entity_struct.h"

void demoLogo()
{
	system("cls");
	printf_s("Спасибо за игру. Представленная копия реализует лишь часть функционала полной.\n");
	system("pause");
}

int main()
{
	system("chcp 1251");
	atexit(demoLogo);

	World *pWorld = nullptr;
	worldInit(pWorld, {178, 22}, PATH_LEVEL_DEV);
	EntityAdd(pWorld->pEntity, pWorld->entityAmount, EntitySymb::store, {184,18});
	EntityAdd(pWorld->pEntity, pWorld->entityAmount, EntitySymb::enemyWarden, {188,22}, true, 3);

	//inventoryItemAdd(pWorld->pEntity[pWorld->mainCharacterID].character->inventory, ItemID::healFlaskLarge, 2);
	//inventoryItemAdd(pWorld->pEntity[pWorld->mainCharacterID].character->inventory, ItemID::oldSword);
	//inventoryItemAdd(pWorld->pEntity[pWorld->mainCharacterID].character->inventory, ItemID::oldSword);

	while(true)
	{
		worldLogic(*pWorld);
		printWorldLevel(*pWorld);
		worldInput(*pWorld);
	}

	worldDestruct(pWorld);
	return ERR_NO_ERR;
}