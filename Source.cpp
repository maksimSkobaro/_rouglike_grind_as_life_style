#include "RL_global.h"
#include "RL_world_struct.h"
#include "RL_entity_struct.h"

int main()
{
	system("chcp 1251");

	World *pWorld = nullptr;
	worldInit(pWorld, {5, 10}, PATH_LEVEL_DEV);
	entityCharacterDie(pWorld->pEntity[EntityAdd(pWorld->pEntity, pWorld->entityAmount, EntitySymb::enemyDragon, {6,10})]);
	EntityAdd(pWorld->pEntity, pWorld->entityAmount, EntitySymb::store, {51,1});
	EntityAdd(pWorld->pEntity, pWorld->entityAmount, EntitySymb::enemyWarden, { 15,10 }, true, 3);

	inventoryItemAdd(pWorld->pEntity[pWorld->mainCharacterID].character->inventory, ItemID::healFlaskLarge, 2);
	inventoryItemAdd(pWorld->pEntity[pWorld->mainCharacterID].character->inventory, ItemID::oldSword);
	inventoryItemAdd(pWorld->pEntity[pWorld->mainCharacterID].character->inventory, ItemID::oldArmor);

	while(true)
	{
		worldLogic(*pWorld);
		printWorldLevel(*pWorld);
		worldInput(*pWorld);
	}


	return ERR_NO_ERR;
}