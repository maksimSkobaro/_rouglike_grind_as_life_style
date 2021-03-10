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
				log("inventoryItemAdd(): amount < 0 (в 1 блоке)");
			}
		}
		else
		{
			if(inventory.capacityCurrent <= inventory.itemsAmount)
			{
				return amount;	//ERR_ENTITY_ADD_OVERFLOW + amount;
			}

			inventory.items[inventory.itemsAmount].isEquipable = false;

			switch(itemID)
			{
			case ItemID::gold:
				{
					char name[] = "Золото";
					strcpy_s(inventory.items[inventory.itemsAmount].name, ITEM_NAME_LEN_MAX, name);
					inventory.items[inventory.itemsAmount].stackMax = 5000;
					inventory.items[inventory.itemsAmount].sellPrice = 1;
				}
				break;
			case ItemID::oldSword:
				{
					char name[] = "Поношенный старый меч";
					strcpy_s(inventory.items[inventory.itemsAmount].name, ITEM_NAME_LEN_MAX, name);
					inventory.items[inventory.itemsAmount].stackMax = 1;
					inventory.items[inventory.itemsAmount].isEquipable = true;
					inventory.items[inventory.itemsAmount].sellPrice = 10;
					inventory.items[inventory.itemsAmount].sellPrice = 50;
				}
				break;
			case ItemID::oldArmor:
				{
					char name[] = "Поношенная старая броня";
					strcpy_s(inventory.items[inventory.itemsAmount].name, ITEM_NAME_LEN_MAX, name);
					inventory.items[inventory.itemsAmount].stackMax = 1;
					inventory.items[inventory.itemsAmount].isEquipable = true;
					inventory.items[inventory.itemsAmount].sellPrice = 50;
				}
				break;
			case ItemID::weakRingOfHealth:
				{
					char name[] = "Слабое кольцо добавочного здоровья";
					strcpy_s(inventory.items[inventory.itemsAmount].name, ITEM_NAME_LEN_MAX, name);
					inventory.items[inventory.itemsAmount].stackMax = 1;
					inventory.items[inventory.itemsAmount].isEquipable = true;
					inventory.items[inventory.itemsAmount].sellPrice = 300;
				}
				break;
			case ItemID::weakRingOfDamage:
				{
					char name[] = "Слабое кольцо добавочного урона";
					strcpy_s(inventory.items[inventory.itemsAmount].name, ITEM_NAME_LEN_MAX, name);
					inventory.items[inventory.itemsAmount].stackMax = 1;
					inventory.items[inventory.itemsAmount].isEquipable = true;
					inventory.items[inventory.itemsAmount].sellPrice = 400;
				}
				break;
			case ItemID::healFlaskLittle:
				{
					char name[] = "Малое зелье регенерации";
					strcpy_s(inventory.items[inventory.itemsAmount].name, ITEM_NAME_LEN_MAX, name);
					inventory.items[inventory.itemsAmount].stackMax = 30;
					inventory.items[inventory.itemsAmount].sellPrice = 150;
				}
				break;
			case ItemID::healFlaskMedium:
				{
					char name[] = "Среднее зелье регенерации";
					strcpy_s(inventory.items[inventory.itemsAmount].name, ITEM_NAME_LEN_MAX, name);
					inventory.items[inventory.itemsAmount].stackMax = 30;
					inventory.items[inventory.itemsAmount].sellPrice = 500;
				}
				break;
			case ItemID::healFlaskLarge:
				{
					char name[] = "Большое зелье регенерации";
					strcpy_s(inventory.items[inventory.itemsAmount].name, ITEM_NAME_LEN_MAX, name);
					inventory.items[inventory.itemsAmount].stackMax = 30;
					inventory.items[inventory.itemsAmount].sellPrice = 1500;
				}
				break;
			default:
				{
					log("inventoryItemAdd(): Неизвестный ItemID");
					char name[] = "?_Пусто";
					strcpy_s(inventory.items[inventory.itemsAmount].name, ITEM_NAME_LEN_MAX, name);
					inventory.items[inventory.itemsAmount].stackMax = 100;
					inventory.items[inventory.itemsAmount].sellPrice = 0;
				}
				break;
			}
			inventory.items[inventory.itemsAmount].amount = 0;
			inventory.items[inventory.itemsAmount].isEquiped = false;

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
					inventory.items[inventory.itemsAmount - 1].amount = 0;
					inventory.items[inventory.itemsAmount - 1].itemID = ItemID::empty;
					inventory.items[inventory.itemsAmount - 1].stackMax = 0;
					char name[] = "Пусто";
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

int inventoryItemRemoveByID(Inventory &inventory, int itemIndex, int amount, bool fullRemove)
{
	if(itemIndex >= inventory.itemsAmount || itemIndex < 0)
	{
		return ERR_INVENTORY_REMOVE;
	}

	inventory.items[itemIndex].amount -= fullRemove ? inventory.items[itemIndex].amount : amount;
	if(inventory.items[itemIndex].amount <= 0)
	{
		for(int i = itemIndex; i < inventory.itemsAmount - 1; i++)
		{
			inventory.items[i] = inventory.items[i + 1];
		}
		inventory.items[inventory.itemsAmount - 1].amount = 0;
		inventory.items[inventory.itemsAmount - 1].itemID = ItemID::empty;
		inventory.items[inventory.itemsAmount - 1].stackMax = 0;
		char name[] = "Пусто";
		strcpy_s(inventory.items[inventory.itemsAmount--].name, ITEM_NAME_LEN_MAX, name);
	}


	return ERR_NO_ERR;
}

void entityInventoryMode(Entity &entity)
{
	Character &character = *entity.character;

	bool isLocalEOI = false;
	int chosenItemIndex = 0;

	do
	{
		system("cls");
		printf_s("Занято слотов/Всего слотов: %i/%i\n", character.inventory.itemsAmount, character.inventory.capacityCurrent);
		printf_s("Инвентарь: \n");
		if(character.inventory.itemsAmount > 0)
		{
			for(int itemIndex = 0; itemIndex < character.inventory.itemsAmount; itemIndex++)
			{
				if(itemIndex == chosenItemIndex)
				{
					putchar('\t');
				}
				printf_s("\t[%i] %s(%i/%i)", itemIndex + 1, character.inventory.items[itemIndex].name, character.inventory.items[itemIndex].amount, character.inventory.items[itemIndex].stackMax);
				if(character.inventory.items[itemIndex].isEquipable)
				{
					printf_s("%s", character.inventory.items[itemIndex].isEquiped ? "(+)" : "(-)");
				}
				putchar('\n');
			}
			printf_s("\nСтоимость: %i\n", character.inventory.items[chosenItemIndex].sellPrice);
			printf_s("\nУправление: \n\t[t/T] Выбросить [1/ВСЕ] единиц предмета\n\t[e] [Использовать/Одеть/Снять] предмет\n\t[Стрелки] Перемещение курсора\n\t[i] Закрыть инвентарь");
		}
		else
		{
			printf_s("\tПусто.\n");
		}


		switch((KBKey) _getch())
		{
		case KBKey::keyT:
			inventoryItemRemoveByID(character.inventory, chosenItemIndex, 1);
			break;
		case KBKey::keyTU:
			inventoryItemRemoveByID(character.inventory, chosenItemIndex, 1, true);
			break;
		case KBKey::keyE:
			inventoryItemUseByID(entity, chosenItemIndex);
			break;
		case KBKey::keyUpArrow:
			chosenItemIndex -= chosenItemIndex > 0 ? 1 : 0;
			break;
		case KBKey::keyDownArrow:
			chosenItemIndex += chosenItemIndex < character.inventory.itemsAmount - 1 ? 1 : 0;
			break;
		case KBKey::keyI:
			isLocalEOI = true;
			break;
		case KBKey::key9:
			exit(ERR_NO_ERR);
			break;
		default:
			break;
		}
	} while(!isLocalEOI);
}

void entityInventoryModeDrop(Entity &mainEntity, Entity &targetEntity, bool &isLocalEOI)
{
	Character &mainCharacter = *mainEntity.character;
	Character &targetCharacter = *targetEntity.character;
	int chosenItemIndex = 0;

	do
	{
		system("cls");
		printf_s("Занято слотов/Всего слотов: %i/%i\n", mainCharacter.inventory.itemsAmount, mainCharacter.inventory.capacityCurrent);
		printf_s("Инвентарь: \n");
		if(mainCharacter.inventory.itemsAmount > 0)
		{
			for(int itemIndex = 0; itemIndex < mainCharacter.inventory.itemsAmount; itemIndex++)
			{
				printf_s("\t[%i] %s(%i/%i)", itemIndex + 1, mainCharacter.inventory.items[itemIndex].name, mainCharacter.inventory.items[itemIndex].amount, mainCharacter.inventory.items[itemIndex].stackMax);
				if(mainCharacter.inventory.items[itemIndex].isEquipable)
				{
					printf_s("%s", mainCharacter.inventory.items[itemIndex].isEquiped ? "(+)" : "(-)");
				}
				putchar('\n');
			}
		}
		else
		{
			printf_s("\tПусто.\n");
		}

		printf_s("\n\nЦелевой инвентарь:\n");
		if(targetCharacter.inventory.itemsAmount > 0)
		{
			for(int itemIndex = 0; itemIndex < targetCharacter.inventory.itemsAmount; itemIndex++)
			{
				if(chosenItemIndex == itemIndex)
				{
					putchar('\t');
				}
				printf_s("\t[%i] %s(%i/%i)\n", itemIndex + 1, targetCharacter.inventory.items[itemIndex].name, targetCharacter.inventory.items[itemIndex].amount, targetCharacter.inventory.items[itemIndex].stackMax);
			}
			printf_s("\nСтоимость: %i\n", targetCharacter.inventory.items[chosenItemIndex].sellPrice);
		}
		else
		{
			printf_s("\tПусто.\n");
		}

		printf_s("\n\nУправление: \n\t[t/T] Выбросить [1/ВСЕ] единиц предмета\n\t[g/G] Забрать [1/ЗАДАННОЕ] кол-во предмета\n\t[Стрелки] Перемещение курсора\n\t[e] Закрыть инвентарь");

		switch((KBKey) _getch())
		{
		case KBKey::keyT:
			inventoryItemRemoveByID(targetCharacter.inventory, chosenItemIndex, 1);
			break;
		case KBKey::keyTU:
			inventoryItemRemoveByID(targetCharacter.inventory, chosenItemIndex, 1, true);
			break;
		case KBKey::keyE:
			isLocalEOI = true;
			break;
		case KBKey::keyG:
			inventoryItemRelocate(targetCharacter.inventory, mainCharacter.inventory, targetCharacter.inventory.items[chosenItemIndex].itemID, 1);
			break;
		case KBKey::keyGU:
			inventoryItemRelocate(targetCharacter.inventory, mainCharacter.inventory, targetCharacter.inventory.items[chosenItemIndex].itemID, getInt("Введите желаемое количество предмета: ", 0));
			break;
		case KBKey::keyUpArrow:
			chosenItemIndex -= chosenItemIndex > 0 ? 1 : 0;
			break;
		case KBKey::keyDownArrow:
			chosenItemIndex += chosenItemIndex < targetCharacter.inventory.itemsAmount - 1 ? 1 : 0;
			break;
		case KBKey::key9:
			exit(ERR_NO_ERR);
			break;
		default:
			break;
		}

		for(int i = 0; i < mainEntity.character->inventory.itemsAmount; i++)
		{
			inventoryItemNormalize(mainEntity.character->inventory, mainEntity.character->inventory.items[i].itemID);
		}

	} while(!isLocalEOI);
}

void entityInventoryModeStore(Entity &mainEntity, Entity &targetEntity, bool &isLocalEOI)
{
	Character &mainCharacter = *mainEntity.character;
	Character &targetCharacter = *targetEntity.character;
	int chosenItemIndex = 0;

	do
	{
		system("cls");
		printf_s("Занято слотов/Всего слотов: %i/%i\n", mainCharacter.inventory.itemsAmount, mainCharacter.inventory.capacityCurrent);
		printf_s("Инвентарь: \n");
		if(mainCharacter.inventory.itemsAmount > 0)
		{
			for(int itemIndex = 0; itemIndex < mainCharacter.inventory.itemsAmount; itemIndex++)
			{
				if(chosenItemIndex == itemIndex)
				{
					putchar('\t');
				}
				printf_s("\t[%i] %s(%i/%i)", itemIndex + 1, mainCharacter.inventory.items[itemIndex].name, mainCharacter.inventory.items[itemIndex].amount, mainCharacter.inventory.items[itemIndex].stackMax);
				if(mainCharacter.inventory.items[itemIndex].isEquipable)
				{
					printf_s("%s", mainCharacter.inventory.items[itemIndex].isEquiped ? "(+)" : "(-)");
				}
				putchar('\n');
			}
		}
		else
		{
			printf_s("\tПусто.\n");
		}

		printf_s("\n\nИнвентарь торговца:\n");
		if(targetCharacter.inventory.itemsAmount > 0)
		{
			for(int itemIndex = 0; itemIndex < targetCharacter.inventory.itemsAmount; itemIndex++)
			{
				if(chosenItemIndex == itemIndex + mainCharacter.inventory.itemsAmount)
				{
					putchar('\t');
				}
				printf_s("\t[%i] %s\n", itemIndex + 1, targetCharacter.inventory.items[itemIndex].name);
			}
		}
		else
		{
			printf_s("\tПусто.\n");
		}

		printf_s("\nСтоимость: %i\n",
				 chosenItemIndex < mainCharacter.inventory.itemsAmount ? mainCharacter.inventory.items[chosenItemIndex].sellPrice : targetCharacter.inventory.items[chosenItemIndex - mainCharacter.inventory.itemsAmount].sellPrice);
		printf_s("\n\nУправление: \n\t[b/B] Купить/Продать [1/ЗАДАННОЕ] кол-во предмета\n\t[Стрелки] Перемещение курсора\n\t[s] Закрыть меню покупки");

		switch((KBKey) _getch())
		{
		case KBKey::keyS:
			isLocalEOI = true;
			break;
		case KBKey::keyB:
			if(chosenItemIndex < mainCharacter.inventory.itemsAmount)
			{
				InventoryStoreModeSellAction(mainCharacter.inventory, &mainCharacter.inventory.items[chosenItemIndex], 1);
			}
			else
			{
				InventoryStoreModeBuyAction(mainCharacter.inventory, &targetCharacter.inventory.items[chosenItemIndex - mainCharacter.inventory.itemsAmount], 1);
			}
			break;
		case KBKey::keyBU:
			if(chosenItemIndex < mainCharacter.inventory.itemsAmount)
			{
				InventoryStoreModeSellAction(mainCharacter.inventory, &mainCharacter.inventory.items[chosenItemIndex], getInt("Введите желаемое количество: ", 0));
			}
			else
			{
				InventoryStoreModeBuyAction(mainCharacter.inventory, &targetCharacter.inventory.items[chosenItemIndex - mainCharacter.inventory.itemsAmount], getInt("Введите желаемое количество: ", 0));
			}
			break;
		case KBKey::keyUpArrow:
			chosenItemIndex -= chosenItemIndex > 0 ? 1 : 0;
			break;
		case KBKey::keyDownArrow:
			chosenItemIndex += chosenItemIndex < mainCharacter.inventory.itemsAmount + targetCharacter.inventory.itemsAmount - 1 ? 1 : 0;
			break;
		case KBKey::key9:
			exit(ERR_NO_ERR);
			break;
		default:
			break;
		}
	} while(!isLocalEOI);
}

void InventoryStoreModeBuyAction(Inventory &inventory, Item *item, int amount)
{
	int finCoast = amount * item->sellPrice;
	int goldAmount = 0;
	int spaceCount = 0;

	for(int i = 0; i < inventory.itemsAmount; i++)
	{
		if(inventory.items[i].itemID == ItemID::gold)
		{
			goldAmount += inventory.items[i].amount;
		}

		if(inventory.items[i].itemID == item->itemID)
		{
			spaceCount += inventory.items[i].stackMax - inventory.items[i].amount;
		}
	}
	spaceCount += (inventory.capacityCurrent - inventory.itemsAmount) * item->stackMax;


	if(goldAmount < finCoast)
	{
		system("cls");
		printf_s("Недостаточно золота.\nНажмите любую конпку, чтобы продолжить . . .");
		_getch();
		return;
	}

	if(amount > spaceCount)
	{
		system("cls");
		printf_s("Недостаточно места.\nНажмите любую конпку, чтобы продолжить . . .");
		_getch();
		return;
	}

	inventoryItemRemove(inventory, ItemID::gold, finCoast);
	inventoryItemAdd(inventory, item->itemID, amount);
	for(int i = 0; i < inventory.itemsAmount; i++)
	{
		inventoryItemNormalize(inventory, inventory.items[i].itemID);
	}
}

void InventoryStoreModeSellAction(Inventory &inventory, Item *item, int amount)
{
	if(item->isEquiped)
	{
		system("cls");
		printf_s("Продовец не будет сам снимать с вас предмет.\nНажмите любую конпку, чтобы продолжить . . .");
		_getch();
		return;
	}

	if(item->itemID == ItemID::gold)
	{
		system("cls");
		printf_s("Продовец не будет обменивать золото на золото.\nНажмите любую конпку, чтобы продолжить . . .");
		_getch();
		return;
	}

	int finCoast = amount * item->sellPrice;
	int itemAmount = 0;
	int spaceCount = 0;

	for(int i = 0; i < inventory.itemsAmount; i++)
	{
		if(inventory.items[i].itemID == ItemID::gold)
		{
			spaceCount += inventory.items[i].stackMax - inventory.items[i].amount;
		}

		if(inventory.items[i].itemID == item->itemID)
		{
			itemAmount += inventory.items[i].amount;
		}
	}
	spaceCount += (inventory.capacityCurrent - inventory.itemsAmount) * 5000;	//	Убрать отсюда этот хардкод н***й.

	if(finCoast > spaceCount)
	{
		system("cls");
		printf_s("Недостаточно места.\nНажмите любую конпку, чтобы продолжить . . .");
		_getch();
		return;
	}

	inventoryItemRemove(inventory, item->itemID, amount);
	inventoryItemAdd(inventory, ItemID::gold, finCoast);
	for(int i = 0; i < inventory.itemsAmount; i++)
	{
		inventoryItemNormalize(inventory, inventory.items[i].itemID);
	}
}

void inventoryItemNormalize(Inventory &inventory, ItemID itemToNormalize)
{
	int firstNotFullIndex = -1, secondNotFullIndex = -1;
	bool wasChange = false;
	do
	{
		firstNotFullIndex = -1; secondNotFullIndex = -1;
		wasChange = false;
		for(int i = 0; i < inventory.itemsAmount; i++)
		{
			if(firstNotFullIndex == -1 && inventory.items[i].itemID == itemToNormalize && inventory.items[i].amount < inventory.items[i].stackMax)
			{
				firstNotFullIndex = i;
			}
			else if(secondNotFullIndex == -1 && inventory.items[i].itemID == itemToNormalize && inventory.items[i].amount < inventory.items[i].stackMax)
			{
				secondNotFullIndex = i;
			}

			if(firstNotFullIndex != -1 && secondNotFullIndex != -1)
			{
				if(inventory.items[firstNotFullIndex].stackMax - inventory.items[firstNotFullIndex].amount >= inventory.items[secondNotFullIndex].amount)
				{
					inventory.items[firstNotFullIndex].amount += inventory.items[secondNotFullIndex].amount;
					inventoryItemRemoveByID(inventory, secondNotFullIndex, 1, true);
				}
				else
				{
					inventory.items[secondNotFullIndex].amount -= inventory.items[firstNotFullIndex].stackMax - inventory.items[firstNotFullIndex].amount;
					inventory.items[firstNotFullIndex].amount = inventory.items[firstNotFullIndex].stackMax;
				}
				wasChange = true;
				break;
			}
		}
	} while(wasChange);
}

int inventoryItemRelocate(Inventory &fromInventory, Inventory &toInventory, ItemID itemID, int amount)
{
	bool wasIn = false;
	int fromInventoryItemIndex = 0;
	for(int i = 0; i < fromInventory.itemsAmount; i++)
	{
		if(fromInventory.items[i].itemID == itemID && fromInventory.items[i].amount >= amount)
		{
			wasIn = true;
			fromInventoryItemIndex = i;
		}
	}

	if(!wasIn)
	{
		system("cls");
		printf_s("Недостаточно предмета в целевом инвентаре.\nНажмите любую кнопку чтобы продолжить . . .");
		_getch();
		return ERR_NO_ERR;
	}

	bool anoughCapacity = toInventory.capacityCurrent > toInventory.itemsAmount ? true : false;
	for(int i = 0; i < toInventory.itemsAmount; i++)
	{
		if(toInventory.items[i].itemID == itemID && toInventory.items[i].stackMax - toInventory.items[i].amount > amount)
		{
			anoughCapacity = true;
		}
	}

	if(!anoughCapacity)
	{
		system("cls");
		printf_s("Недостаточно места в инвентаре\nНажмите любую кнопку чтобы продолжить . . .");
		_getch();
		return ERR_NO_ERR;
	}

	if(wasIn && anoughCapacity)
	{
		inventoryItemRemoveByID(fromInventory, fromInventoryItemIndex, amount);
		inventoryItemAdd(toInventory, itemID, amount);
	}

	return ERR_NO_ERR;
}

int inventiryModeEquipMode(Character &character, int itemIndex)
{
	Inventory &inventory = character.inventory;

	bool isMele = false;
	bool isArmor = false;
	bool isOther = false;

	switch(inventory.items[itemIndex].itemID)
	{
	case ItemID::oldSword:
		isMele = true;
		break;
	case ItemID::oldArmor:
		isArmor = true;
		break;
	case ItemID::weakRingOfHealth:
	case ItemID::weakRingOfDamage:
		isOther = true;
		break;
	default:
		return ERR_INVENTORY_USE_EQUIP_INDEX_FAIL;
		break;
	}

	bool workMode = inventory.items[itemIndex].isEquiped;
	for(int i = 0; i < inventory.itemsAmount; i++)
	{
		if(!workMode)
		{
			switch(inventory.items[i].itemID)
			{
			case ItemID::oldSword:
				if(isMele)
				{
					inventory.items[i].isEquiped = i == itemIndex ? true : false;
				}
				break;
			case ItemID::oldArmor:
				if(isArmor)
				{
					inventory.items[i].isEquiped = i == itemIndex ? true : false;
				}
				break;
			case ItemID::weakRingOfHealth:
			case ItemID::weakRingOfDamage:
				if(isOther)
				{
					inventory.items[i].isEquiped = i == itemIndex ? true : false;
				}
				break;
			}
		}
		else
		{
			inventory.items[itemIndex].isEquiped = false;
			break;
		}
	}

	characterModifDamageSet(character, 0);
	characterModifHealthSet(character, 0);
	characterModifVisionSet(character, 0);
	for(int i = 0; i < inventory.itemsAmount; i++)
	{
		if(inventory.items[i].isEquiped)
		{
			switch(inventory.items[i].itemID)
			{
			case ItemID::oldSword:
				characterModifDamageSet(character, 30);
				break;
			case ItemID::oldArmor:
				characterModifHealthSet(character, 60);
				break;
			case ItemID::weakRingOfHealth:
				break;
			case ItemID::weakRingOfDamage:
				break;
			}
		}
	}

	return ERR_NO_ERR;
}

int inventoryItemUseByID(Entity &entity, int itemIndex)
{
	Character &character = *entity.character;

	if(itemIndex >= character.inventory.itemsAmount || itemIndex < 0)
	{
		return ERR_INVENTORY_USE_OUT_OF_RANGE;
	}

	switch(character.inventory.items[itemIndex].itemID)
	{
	case ItemID::oldSword:
		inventiryModeEquipMode(*entity.character, itemIndex);
		break;
	case ItemID::oldArmor:
		inventiryModeEquipMode(*entity.character, itemIndex);
		break;
	case ItemID::healFlaskLittle:
		entityCharacterGetHeal(entity, 300);
		inventoryItemRemoveByID(character.inventory, itemIndex, 1);
		break;
	case ItemID::healFlaskMedium:
		entityCharacterGetHeal(entity, 1200);
		inventoryItemRemoveByID(character.inventory, itemIndex, 1);
		break;
	case ItemID::healFlaskLarge:
		entityCharacterGetHeal(entity, 5000);
		inventoryItemRemoveByID(character.inventory, itemIndex, 1);
		break;
	default:
		break;
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
		pCharacter->killExpReward = 0;
		pCharacter->team = Team::ally;
		pCharacter->level = 1;
		pCharacter->nextLevelExp = sqrt(pCharacter->level) * 100;
		pCharacter->expa = 0;
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
		pCharacter->healthReal = pCharacter->healthCurrent;
		pCharacter->manaBase = 100;
		pCharacter->manaModifitaion = 0;
		pCharacter->manaCurrent = pCharacter->manaBase + pCharacter->manaModifitaion;
		pCharacter->visionRangeBase = 3;
		pCharacter->visionRangeModification = 0;
		pCharacter->visionRangeCurrent = pCharacter->visionRangeBase + pCharacter->visionRangeModification;
		break;
	case EntitySymb::store:
		pCharacter->killExpReward = -100;
		pCharacter->team = Team::neutral;
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
		pCharacter->healthReal = pCharacter->healthCurrent;
		pCharacter->manaBase = 0;
		pCharacter->manaModifitaion = 15000;
		pCharacter->manaCurrent = pCharacter->manaBase + pCharacter->manaModifitaion;
		pCharacter->visionRangeBase = 1;
		pCharacter->visionRangeModification = 9;
		pCharacter->visionRangeCurrent = pCharacter->visionRangeBase + pCharacter->visionRangeModification;
		for(int i = 2; i < (int) ItemID::_last; i++)
		{
			inventoryItemAdd(pCharacter->inventory, (ItemID) i, 1);
		}
		break;
	case EntitySymb::enemyWarden:
		pCharacter->killExpReward = 5;
		pCharacter->team = Team::enemy;
		pCharacter->level = 1;
		pCharacter->inventory.itemsAmount = 0;
		pCharacter->inventory.capacityBase = 2;
		pCharacter->inventory.capacityModiffication = 0;
		pCharacter->inventory.capacityCurrent = pCharacter->inventory.capacityBase + pCharacter->inventory.capacityModiffication;
		pCharacter->damageBase = 20;
		pCharacter->damageModification = 0;
		pCharacter->damageCurrent = pCharacter->damageBase + pCharacter->damageModification;
		pCharacter->healthBase = 80;
		pCharacter->healthModification = 0;
		pCharacter->healthCurrent = pCharacter->healthBase + pCharacter->healthModification;
		pCharacter->healthReal = pCharacter->healthCurrent;
		pCharacter->manaBase = 10;
		pCharacter->manaModifitaion = 0;
		pCharacter->manaCurrent = pCharacter->manaBase + pCharacter->manaModifitaion;
		pCharacter->visionRangeBase = 2;
		pCharacter->visionRangeModification = 0;
		pCharacter->visionRangeCurrent = pCharacter->visionRangeBase + pCharacter->visionRangeModification;
		break;
	case EntitySymb::enemyDragon:
		pCharacter->killExpReward = 250;
		pCharacter->team = Team::enemy;
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
		pCharacter->healthReal = pCharacter->healthCurrent;
		pCharacter->manaBase = 400;
		pCharacter->manaModifitaion = 0;
		pCharacter->manaCurrent = pCharacter->manaBase + pCharacter->manaModifitaion;
		pCharacter->visionRangeBase = 4;
		pCharacter->visionRangeModification = 2;
		pCharacter->visionRangeCurrent = pCharacter->visionRangeBase + pCharacter->visionRangeModification;
		break;
	default:
		entityCharacterRemove(worldEntity);
		break;
	}

	return ERR_NO_ERR;
}

int entityCharacterDie(Entity &worldEntity)
{
	if(worldEntity.character->isAlive)
	{
		worldEntity.direction = Direction::stay;
		worldEntity.character->isAlive = false;
		worldEntity.character->inventory.itemsAmount = 0;
		worldEntity.character->killExpReward = 0;
	}

	//	Сценарии смерти персонажа:
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
			case 2:
				inventoryItemAdd(worldEntity.character->inventory, ItemID::gold, 15 + rand() % 11);
				break;
			case 3:
			case 4:
			case 5:
				inventoryItemAdd(worldEntity.character->inventory, ItemID::healFlaskLittle, 1 + rand() % 2);
				break;
			case 6:
				inventoryItemAdd(worldEntity.character->inventory, ItemID::oldArmor, 1);
				break;
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

int EntityAdd(Entity *&entity, int &entityAmount, EntitySymb entitySymb, Point coords, bool isSpawner, int toSpawnCount)
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


	pEntityNew[entityAmount - 1].character = nullptr;
	pEntityNew[entityAmount - 1].ID = entityID++;
	pEntityNew[entityAmount - 1].spawner = nullptr;
	pEntityNew[entityAmount - 1].isInRange = false;
	pEntityNew[entityAmount - 1].entitySymb = entitySymb;
	pEntityNew[entityAmount - 1].coords = coords;
	pEntityNew[entityAmount - 1].direction = Direction::stay;

	if(!isSpawner)
	{
		entityCharacterCreate(pEntityNew[entityAmount - 1], entitySymb);
	}

	if(isSpawner)
	{
		pEntityNew[entityAmount - 1].entitySymb = EntitySymb::spawner;
		char name[ENTITY_NAME_LEN_MAX] = "Лагерь";
		strcpy_s(pEntityNew[entityAmount - 1].name, ENTITY_NAME_LEN_MAX, name);
		entitySpawnerCreate(pEntityNew[entityAmount - 1], entitySymb, toSpawnCount);
	}
	else
	{
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
		entityCharacterRemove(entity[i]);
		entitySpawnerRemove(entity[i]);
		for(int j = i; j < entityAmount - 1; j++)
		{
			entity[j] = entity[j + 1];
		}
		--entityAmount;
		entity[entityAmount].spawner = nullptr;
		entity[entityAmount].character = nullptr;
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
		log("getWorldMainCharacterID(): Идентификатор MainCharacter не был найден среди существующих Entity.");
	}

	return id;
}

int entitySpawnerCreate(Entity &entity, EntitySymb characterToSpawn, int toSpawnCount)
{
	Spawner *pNewSpawner = nullptr;
	pNewSpawner = (Spawner *) malloc(sizeof(*pNewSpawner));
	if(!pNewSpawner)
	{
		log("entitySpawnerCreate(): Не удалось выделить память. pNewSpawner = nullptr.");
		exit(ERR_MEMORY);
	}

	for(int i = 0; i < SPAWN_AMOUNT_MAX; i++)
	{
		pNewSpawner->IDs[i] = -1;
	}
	pNewSpawner->curIDs = 0;
	pNewSpawner->entityToSpawn = characterToSpawn;
	pNewSpawner->maxIDs = toSpawnCount;
	free(entity.spawner);
	entity.spawner = pNewSpawner;
	return ERR_NO_ERR;
}

int entitySpawnerRemove(Entity &entity)
{
	free(entity.spawner);
	entity.spawner = nullptr;
	return ERR_NO_ERR;
}

int entityLevelUpLogic(Entity &entity)
{
	if(entity.character->nextLevelExp <= entity.character->expa)
	{
		entity.character->level++;
		entity.character->expa -= entity.character->nextLevelExp;
		entity.character->nextLevelExp = sqrt(entity.character->level) * 100;
		system("cls");
		bool isUpdateInventory = entity.character->inventory.capacityCurrent < INVENTORY_CAPACITY_MAX;
		int rightBorder = 4;
		int num;
		do
		{
			printf("Выберетите что бы вы хотели прокачать \n"
				   "\t[1] Прокачать урон на 30 едениц\n"
				   "\t[2] Прокачать здоровье на 60 едениц\n"
				   "\t[3] Прокачать диапазон видимости на 1 еденицу\n");
			if(isUpdateInventory)
			{
				printf("\t[4] Прокачать вместимость инвентаря на 1 еденицу\n");
			}
			scanf_s("%i", &num);
			if(!isUpdateInventory)
			{
				rightBorder = 3;
			}
		} while(num <= 0 || num > rightBorder);
		switch(num)
		{
		case 1:
			entity.character->damageModification += 30;
			break;
		case 2:
			entity.character->healthModification += 60;
			break;
		case 3:
			entity.character->visionRangeModification += 1;
			break;
		case 4:
			entity.character->inventory.capacityModiffication += 1;
			break;
		default:
			break;
		}
	}

	return ERR_NO_ERR;
}

void characterExpIncrease(Character &character, int additionExp)
{
	character.expa += additionExp;
}

void characterModifDamageSet(Character &character, int newState)
{
	character.damageModification = newState;
}

void characterModifVisionSet(Character &character, int newState)
{
	character.visionRangeModification = newState;
}

void characterModifHealthSet(Character &character, int newState)
{
	character.healthModification = newState;
}

void entityCharacterGetDamage(Entity &entity, int damageAmount, bool fullKill)
{
	if(fullKill)
	{
		damageAmount = entity.character->healthCurrent;
	}

	if(damageAmount > 0)
	{
		entity.character->healthReal -= damageAmount;
		if(entity.character->healthReal < 0)
		{
			entityCharacterDie(entity);
		}
	}
	else
	{
		log("characterGetDamage(): получено отрицательное значение damageAmount");
	}

}

void entityCharacterGetHeal(Entity &entity, int healAmount, bool fullHeal)
{
	if(fullHeal)
	{
		healAmount = entity.character->healthCurrent;
	}

	if(healAmount > 0)
	{
		entity.character->healthReal += healAmount;
		if(entity.character->healthReal > entity.character->healthCurrent)
		{
			entity.character->healthReal = entity.character->healthCurrent;
		}
	}
	else
	{
		log("characterGetHeal(): получено отрицательное значение healAmount");
	}

}