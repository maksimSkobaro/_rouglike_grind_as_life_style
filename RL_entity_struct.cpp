#include "RL_entity_struct.h"


////////////////////////////////////////////////////////////
////////////////////FUNCTIONS_DEFINITION////////////////////
////////////////////////////////////////////////////////////

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
				log("inventoryItemAdd(): amount < 0 (� 1 �����)");
			}
		}
		else
		{

			switch(itemID)
			{
			case ItemID::gold:
				{
					char name[] = "������";
					strcpy_s(inventory.items[inventory.itemsAmount].name, ITEM_NAME_LEN_MAX, name);
					inventory.items[inventory.itemsAmount].stackMax = 50000;
				}
				break;
			case ItemID::oldSword:
				{
					char name[] = "���������� ������ ���";
					strcpy_s(inventory.items[inventory.itemsAmount].name, ITEM_NAME_LEN_MAX, name);
					inventory.items[inventory.itemsAmount].stackMax = 1;
				}
				break;
			case ItemID::oldArmor:
				{
					char name[] = "���������� ������ �����";
					strcpy_s(inventory.items[inventory.itemsAmount].name, ITEM_NAME_LEN_MAX, name);
					inventory.items[inventory.itemsAmount].stackMax = 1;
				}
				break;
			case ItemID::weakRingOfHealth:
				{
					char name[] = "������ ������ ����������� ��������";
					strcpy_s(inventory.items[inventory.itemsAmount].name, ITEM_NAME_LEN_MAX, name);
					inventory.items[inventory.itemsAmount].stackMax = 1;
				}
				break;
			case ItemID::weakRingOfDamage:
				{
					char name[] = "������ ������ ����������� �����";
					strcpy_s(inventory.items[inventory.itemsAmount].name, ITEM_NAME_LEN_MAX, name);
					inventory.items[inventory.itemsAmount].stackMax = 1;
				}
				break;
			case ItemID::healFlaskLittle:
				{
					char name[] = "����� ����� �����������";
					strcpy_s(inventory.items[inventory.itemsAmount].name, ITEM_NAME_LEN_MAX, name);
					inventory.items[inventory.itemsAmount].stackMax = 120;
				}
				break;
			case ItemID::healFlaskMedium:
				{
					char name[] = "������� ����� �����������";
					strcpy_s(inventory.items[inventory.itemsAmount].name, ITEM_NAME_LEN_MAX, name);
					inventory.items[inventory.itemsAmount].stackMax = 100;
				}
				break;
			case ItemID::healFlaskLarge:
				{
					char name[] = "������� ����� �����������";
					strcpy_s(inventory.items[inventory.itemsAmount].name, ITEM_NAME_LEN_MAX, name);
					inventory.items[inventory.itemsAmount].stackMax = 60;
				}
				break;
			case ItemID::manaFlaskLittle:
				{
					char name[] = "����� ����� ����";
					strcpy_s(inventory.items[inventory.itemsAmount].name, ITEM_NAME_LEN_MAX, name);
					inventory.items[inventory.itemsAmount].stackMax = 120;
				}
				break;
			case ItemID::manaFlaskMedium:
				{
					char name[] = "������� ����� ����";
					strcpy_s(inventory.items[inventory.itemsAmount].name, ITEM_NAME_LEN_MAX, name);
					inventory.items[inventory.itemsAmount].stackMax = 100;
				}
				break;
			case ItemID::manaFlaskLarge:
				{
					char name[] = "������� ����� �����������";
					strcpy_s(inventory.items[inventory.itemsAmount].name, ITEM_NAME_LEN_MAX, name);
					inventory.items[inventory.itemsAmount].stackMax = 60;
				}
				break;
			default:
				{
					log("inventoryItemAdd(): ����������� ItemID");
					char name[] = "?_�����";
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
				log("inventoryItemAdd(): amount < 0 (�� 2 �����)");
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
		log("entityCharacterCreate(): ������ ��������� ������. *pCharacter = nullptr.");
		exit(ERR_MEMORY);
	}


	//	������������ ����������� �������� ��� �������� ����������
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
	//	�������� ������ ���������:
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

int EntityAdd(Entity *&entity, int &entityAmount, EntitySymb entitySymb, Point coords)
{
	static int entityID = 0;

	Entity *pEntityNew = (Entity *) malloc(sizeof(*pEntityNew) * ++entityAmount);

	if(!pEntityNew)
	{
		log("worldEntityAdd(): �� ������� �������� ������. pEntityNew = nullptr");
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
			char name[ENTITY_NAME_LEN_MAX] = "�'��� ����";	//	��, ��� ���� �� ��� �����������.
			strcpy_s(pEntityNew[entityAmount - 1].name, ENTITY_NAME_LEN_MAX, name);
		}
		break;
	case EntitySymb::store:
		{
			char name[ENTITY_NAME_LEN_MAX] = "������������� ��������";
			strcpy_s(pEntityNew[entityAmount - 1].name, ENTITY_NAME_LEN_MAX, name);
		}
		break;
	case EntitySymb::enemyWarden:
		{
			char name[ENTITY_NAME_LEN_MAX] = "�������� ����������";
			strcpy_s(pEntityNew[entityAmount - 1].name, ENTITY_NAME_LEN_MAX, name);
		}
		break;
	case EntitySymb::enemyDragon:
		{
			char name[ENTITY_NAME_LEN_MAX] = "������";
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
			log("worldEntityAdd(): ����������� ��� ������������ Entity.");
			char name[ENTITY_NAME_LEN_MAX] = "_?_Entity";
			strcpy_s(pEntityNew[entityAmount - 1].name, ENTITY_NAME_LEN_MAX, name);
		}
		break;
	}

	free(entity);
	entity = pEntityNew;

	return entityID - 1;
}

int EntityRemove(Entity *&entity, int &entityAmount, int ID)
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
		log("worldEntityRemove(): ������ �������� Entity. Entity �� ��� ������ �� ID");
#ifdef DEBUG
		exit(ERR_ENTITY_REMOVE);
#else
		return ERR_ENTITY_REMOVE;
#endif // DEBUG

	}

	return ERR_NO_ERR;
}

//	DEPRICATED
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
		log("getWorldMainCharacterID(): ������������� MainCharacter �� ��� ������ ����� ������������ Entity.");
	}

	return id;
}