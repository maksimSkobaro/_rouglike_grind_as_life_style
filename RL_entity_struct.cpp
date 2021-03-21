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
			inventory.items[inventory.itemsAmount].dmgEffect = 0;
			inventory.items[inventory.itemsAmount].healEffect = 0;
			inventory.items[inventory.itemsAmount].healthEffect = 0;
			inventory.items[inventory.itemsAmount].additionDmgTo = EntitySymb::empty;
			inventory.items[inventory.itemsAmount].reduceDamageFrom = EntitySymb::empty;

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
					char name[] = "Сточившийся старый меч";
					strcpy_s(inventory.items[inventory.itemsAmount].name, ITEM_NAME_LEN_MAX, name);
					inventory.items[inventory.itemsAmount].stackMax = 1;
					inventory.items[inventory.itemsAmount].isEquipable = true;
					inventory.items[inventory.itemsAmount].sellPrice = 495;
					inventory.items[inventory.itemsAmount].dmgEffect = 18;
				}
				break;
			case ItemID::dworfAxe:
				{
					char name[] = "Секира дворфа";
					strcpy_s(inventory.items[inventory.itemsAmount].name, ITEM_NAME_LEN_MAX, name);
					inventory.items[inventory.itemsAmount].stackMax = 1;
					inventory.items[inventory.itemsAmount].isEquipable = true;
					inventory.items[inventory.itemsAmount].sellPrice = 1008;
					inventory.items[inventory.itemsAmount].dmgEffect = 42;
				}
				break;
			case ItemID::volcanSword:
				{
					char name[] = "Меч из вулканического камня";
					strcpy_s(inventory.items[inventory.itemsAmount].name, ITEM_NAME_LEN_MAX, name);
					inventory.items[inventory.itemsAmount].stackMax = 1;
					inventory.items[inventory.itemsAmount].isEquipable = true;
					inventory.items[inventory.itemsAmount].sellPrice = 1256;
					inventory.items[inventory.itemsAmount].dmgEffect = 56;
				}
				break;
			case ItemID::silverSpear:
				{
					char name[] = "Копье серебряного генерала";
					strcpy_s(inventory.items[inventory.itemsAmount].name, ITEM_NAME_LEN_MAX, name);
					inventory.items[inventory.itemsAmount].stackMax = 1;
					inventory.items[inventory.itemsAmount].isEquipable = true;
					inventory.items[inventory.itemsAmount].sellPrice = 2112;
					inventory.items[inventory.itemsAmount].dmgEffect = 75;
				}
				break;
			case ItemID::goldenSword:
				{
					char name[] = "Меч золотого генерала";
					strcpy_s(inventory.items[inventory.itemsAmount].name, ITEM_NAME_LEN_MAX, name);
					inventory.items[inventory.itemsAmount].stackMax = 1;
					inventory.items[inventory.itemsAmount].isEquipable = true;
					inventory.items[inventory.itemsAmount].sellPrice = 3418;
					inventory.items[inventory.itemsAmount].dmgEffect = 96;
				}
				break;


			case ItemID::hunterArmor:
				{
					char name[] = "Броня охотника";
					strcpy_s(inventory.items[inventory.itemsAmount].name, ITEM_NAME_LEN_MAX, name);
					inventory.items[inventory.itemsAmount].stackMax = 1;
					inventory.items[inventory.itemsAmount].isEquipable = true;
					inventory.items[inventory.itemsAmount].sellPrice = 310;
					inventory.items[inventory.itemsAmount].healthEffect = 25;
				}
				break;
			case ItemID::leatherArmor:
				{
					char name[] = "Потрепанный кожаный доспех";
					strcpy_s(inventory.items[inventory.itemsAmount].name, ITEM_NAME_LEN_MAX, name);
					inventory.items[inventory.itemsAmount].stackMax = 1;
					inventory.items[inventory.itemsAmount].isEquipable = true;
					inventory.items[inventory.itemsAmount].sellPrice = 119;
					inventory.items[inventory.itemsAmount].healthEffect = 12;
				}
				break;
			case ItemID::corgArmor:
				{
					char name[] = "Доспех корга";
					strcpy_s(inventory.items[inventory.itemsAmount].name, ITEM_NAME_LEN_MAX, name);
					inventory.items[inventory.itemsAmount].stackMax = 1;
					inventory.items[inventory.itemsAmount].isEquipable = true;
					inventory.items[inventory.itemsAmount].sellPrice = 942;
					inventory.items[inventory.itemsAmount].healthEffect = 50;
				}
				break;
			case ItemID::chainMail:
				{
					char name[] = "Кольчуга";
					strcpy_s(inventory.items[inventory.itemsAmount].name, ITEM_NAME_LEN_MAX, name);
					inventory.items[inventory.itemsAmount].stackMax = 1;
					inventory.items[inventory.itemsAmount].isEquipable = true;
					inventory.items[inventory.itemsAmount].sellPrice = 640;
					inventory.items[inventory.itemsAmount].healthEffect = 40;
				}
				break;
			case ItemID::silverArmor:
				{
					char name[] = "Доспехи серебряного генерала";
					strcpy_s(inventory.items[inventory.itemsAmount].name, ITEM_NAME_LEN_MAX, name);
					inventory.items[inventory.itemsAmount].stackMax = 1;
					inventory.items[inventory.itemsAmount].isEquipable = true;
					inventory.items[inventory.itemsAmount].sellPrice = 1200;
					inventory.items[inventory.itemsAmount].healthEffect = 70;
				}
				break;
			case ItemID::goldenArmor:
				{
					char name[] = "Доспехи золотого генерала";
					strcpy_s(inventory.items[inventory.itemsAmount].name, ITEM_NAME_LEN_MAX, name);
					inventory.items[inventory.itemsAmount].stackMax = 1;
					inventory.items[inventory.itemsAmount].isEquipable = true;
					inventory.items[inventory.itemsAmount].sellPrice = 2700;
					inventory.items[inventory.itemsAmount].healthEffect = 135;
				}
				break;


			case ItemID::healFlaskLittle:
				{
					char name[] = "Плохое зелье регенерации";
					strcpy_s(inventory.items[inventory.itemsAmount].name, ITEM_NAME_LEN_MAX, name);
					inventory.items[inventory.itemsAmount].stackMax = 30;
					inventory.items[inventory.itemsAmount].sellPrice = 50;
					inventory.items[inventory.itemsAmount].healEffect = 80;
				}
				break;
			case ItemID::healFlaskMedium:
				{
					char name[] = "Обычное зелье регенерации";
					strcpy_s(inventory.items[inventory.itemsAmount].name, ITEM_NAME_LEN_MAX, name);
					inventory.items[inventory.itemsAmount].stackMax = 30;
					inventory.items[inventory.itemsAmount].sellPrice = 420;
					inventory.items[inventory.itemsAmount].healEffect = 380;
				}
				break;
			case ItemID::healFlaskLarge:
				{
					char name[] = "Великое зелье регенерации";
					strcpy_s(inventory.items[inventory.itemsAmount].name, ITEM_NAME_LEN_MAX, name);
					inventory.items[inventory.itemsAmount].stackMax = 10;
					inventory.items[inventory.itemsAmount].sellPrice = 890;
					inventory.items[inventory.itemsAmount].healEffect = 50000;
				}
				break;


			case ItemID::dragonScaleArmor:
				{
					char name[] = "Броня из драконьей чешуи";
					strcpy_s(inventory.items[inventory.itemsAmount].name, ITEM_NAME_LEN_MAX, name);
					inventory.items[inventory.itemsAmount].stackMax = 1;
					inventory.items[inventory.itemsAmount].sellPrice = 8500;
					inventory.items[inventory.itemsAmount].isEquipable = true;
					inventory.items[inventory.itemsAmount].healthEffect = 250;
					inventory.items[inventory.itemsAmount].reduceDamageFrom = EntitySymb::enemyDragon;
				}
				break;
			case ItemID::godsMadeArmor:
				{
					char name[] = "Броня сотворенная богами";
					strcpy_s(inventory.items[inventory.itemsAmount].name, ITEM_NAME_LEN_MAX, name);
					inventory.items[inventory.itemsAmount].stackMax = 1;
					inventory.items[inventory.itemsAmount].sellPrice = 14500;
					inventory.items[inventory.itemsAmount].isEquipable = true;
					inventory.items[inventory.itemsAmount].healthEffect = 900;
					inventory.items[inventory.itemsAmount].reduceDamageFrom = EntitySymb::enemyKri;
				}
				break;
			case ItemID::undeadKingArmor:
				{
					char name[] = "Броня короля нежити";
					strcpy_s(inventory.items[inventory.itemsAmount].name, ITEM_NAME_LEN_MAX, name);
					inventory.items[inventory.itemsAmount].stackMax = 1;
					inventory.items[inventory.itemsAmount].sellPrice = 11000;
					inventory.items[inventory.itemsAmount].isEquipable = true;
					inventory.items[inventory.itemsAmount].healthEffect = 330;
					inventory.items[inventory.itemsAmount].dmgEffect = 80;
				}
				break;
			case ItemID::justiceMantle:
				{
					char name[] = "Мантия верховного судьи";
					strcpy_s(inventory.items[inventory.itemsAmount].name, ITEM_NAME_LEN_MAX, name);
					inventory.items[inventory.itemsAmount].stackMax = 1;
					inventory.items[inventory.itemsAmount].isEquipable = true;
					inventory.items[inventory.itemsAmount].sellPrice = 13000;
					inventory.items[inventory.itemsAmount].healthEffect = 470;
					inventory.items[inventory.itemsAmount].dmgEffect = 100;
					inventory.items[inventory.itemsAmount].reduceDamageFrom = EntitySymb::enemyKri;
				}

			case ItemID::huntingGroundsSword:
				{
					char name[] = "Меч охотничьих угодий";
					strcpy_s(inventory.items[inventory.itemsAmount].name, ITEM_NAME_LEN_MAX, name);
					inventory.items[inventory.itemsAmount].stackMax = 1;
					inventory.items[inventory.itemsAmount].sellPrice = 6400;
					inventory.items[inventory.itemsAmount].isEquipable = true;
					inventory.items[inventory.itemsAmount].dmgEffect = 84;
					inventory.items[inventory.itemsAmount].additionDmgTo = EntitySymb::enemyBeastman;
				}
				break;
			case ItemID::atlantAxe:
				{
					char name[] = "Секира Атланата";
					strcpy_s(inventory.items[inventory.itemsAmount].name, ITEM_NAME_LEN_MAX, name);
					inventory.items[inventory.itemsAmount].stackMax = 1;
					inventory.items[inventory.itemsAmount].isEquipable = true;
					inventory.items[inventory.itemsAmount].sellPrice = 8900;
					inventory.items[inventory.itemsAmount].dmgEffect = 140;
					inventory.items[inventory.itemsAmount].additionDmgTo = EntitySymb::enemyGiant;
				}
				break;
			case ItemID::spiritHammer:
				{
					char name[] = "Молот духа земли";
					strcpy_s(inventory.items[inventory.itemsAmount].name, ITEM_NAME_LEN_MAX, name);
					inventory.items[inventory.itemsAmount].stackMax = 1;
					inventory.items[inventory.itemsAmount].isEquipable = true;
					inventory.items[inventory.itemsAmount].sellPrice = 9600;
					inventory.items[inventory.itemsAmount].dmgEffect = 150;
					inventory.items[inventory.itemsAmount].additionDmgTo = EntitySymb::enemyCorg;
				}
				break;
			case ItemID::justiceHummer:
				{
					char name[] = "Молот верховного судьи";
					strcpy_s(inventory.items[inventory.itemsAmount].name, ITEM_NAME_LEN_MAX, name);
					inventory.items[inventory.itemsAmount].stackMax = 1;
					inventory.items[inventory.itemsAmount].isEquipable = true;
					inventory.items[inventory.itemsAmount].sellPrice = 14000;
					inventory.items[inventory.itemsAmount].dmgEffect = 220;
					inventory.items[inventory.itemsAmount].additionDmgTo = EntitySymb::enemyKri;
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
		char name[] = "Пусто";
		strcpy_s(inventory.items[inventory.itemsAmount--].name, ITEM_NAME_LEN_MAX, name);
	}


	return ERR_NO_ERR;
}

void itemInfoPrint(ItemID itemID)
{
	switch(itemID)
	{
	case ItemID::empty:
		readList("./lists/list-empty.list");
		break;
	case ItemID::gold:
		readList("./lists/list-gold.list");
		break;
	case ItemID::oldSword:
		readList("./lists/list-oldSword.list");
		break;
	case ItemID::dworfAxe:
		readList("./lists/list-dworfAxe.list");
		break;
	case ItemID::volcanSword:
		readList("./lists/list-volcanSword.list");
		break;
	case ItemID::silverSpear:
		readList("./lists/list-silverSpear.list");
		break;
	case ItemID::goldenSword:
		readList("./lists/list-goldenSword.list");
		break;
	case ItemID::leatherArmor:
		readList("./lists/list-leatherArmor.list");
		break;
	case ItemID::hunterArmor:
		readList("./lists/list-hunterArmor.list");
		break;
	case ItemID::corgArmor:
		readList("./lists/list-corgArmor.list");
		break;
	case ItemID::chainMail:
		readList("./lists/list-chainMail.list");
		break;
	case ItemID::silverArmor:
		readList("./lists/list-silverArmor.list");
		break;
	case ItemID::goldenArmor:
		readList("./lists/list-goldenArmor.list");
		break;
	case ItemID::healFlaskLittle:
		readList("./lists/list-healFlaskLittle.list");
		break;
	case ItemID::healFlaskMedium:
		readList("./lists/list-healFlaskMedium.list");
		break;
	case ItemID::healFlaskLarge:
		readList("./lists/list-healFlaskLarge.list");
		break;
	case ItemID::dragonScaleArmor:
		readList("./lists/list-dragonScaleArmor.list");
		break;
	case ItemID::godsMadeArmor:
		readList("./lists/list-godsMadeArmor.list");
		break;
	case ItemID::undeadKingArmor:
		readList("./lists/list-undeadKingArmor.list");
		break;
	case ItemID::justiceMantle:
		readList("./lists/list-justiceMantle.list");
		break;
	case ItemID::huntingGroundsSword:
		readList("./lists/list-huntingGroundsSword.list");
		break;
	case ItemID::atlantAxe:
		readList("./lists/list-atlantAxe.list");
		break;
	case ItemID::spiritHammer:
		readList("./lists/list-spiritHammer.list");
		break;
	case ItemID::justiceHummer:
		readList("./lists/list-justiceHummer.list");
		break;
	default:
		break;
	}
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
					printf_s("%s ", character.inventory.items[itemIndex].isEquiped ? "(+)" : "(-)");
				}
				if(character.inventory.items[itemIndex].dmgEffect > 0)
				{
					printf_s("(+%i DMG) ", character.inventory.items[itemIndex].dmgEffect);
				}
				if(character.inventory.items[itemIndex].healthEffect > 0)
				{
					printf_s("(+%i HP) ", character.inventory.items[itemIndex].healthEffect);
				}
				if(character.inventory.items[itemIndex].healEffect > 0)
				{
					printf_s("(+%i HEAL) ", character.inventory.items[itemIndex].healEffect);
				}
				putchar('\n');
			}
			printf_s("\nСредняя стоимость: %i\n", character.inventory.items[chosenItemIndex].sellPrice);
			printf_s("\nУправление: \n\t[t/T] Выбросить [1/ВСЕ] единиц предмета\n\t[e] [Использовать/Одеть/Снять] предмет\n\t[Стрелки] Перемещение курсора\n\t[i] Закрыть инвентарь\n\t[I] Посмотреть расширенную информацию о предмете");
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
		case KBKey::keyIU:
			itemInfoPrint(character.inventory.items[chosenItemIndex].itemID);
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
					printf_s("%s ", mainCharacter.inventory.items[itemIndex].isEquiped ? "(+)" : "(-)");
				}
				if(mainCharacter.inventory.items[itemIndex].dmgEffect > 0)
				{
					printf_s("(+%i DMG) ", mainCharacter.inventory.items[itemIndex].dmgEffect);
				}
				if(mainCharacter.inventory.items[itemIndex].healthEffect > 0)
				{
					printf_s("(+%i HP) ", mainCharacter.inventory.items[itemIndex].healthEffect);
				}
				if(mainCharacter.inventory.items[itemIndex].healEffect > 0)
				{
					printf_s("(+%i HEAL) ", mainCharacter.inventory.items[itemIndex].healEffect);
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
				printf_s("\t[%i] %12s(%i/%i) ", itemIndex + 1, targetCharacter.inventory.items[itemIndex].name, targetCharacter.inventory.items[itemIndex].amount, targetCharacter.inventory.items[itemIndex].stackMax);
				if(targetCharacter.inventory.items[itemIndex].dmgEffect > 0)
				{
					printf_s("(+%i DMG) ", targetCharacter.inventory.items[itemIndex].dmgEffect);
				}
				if(targetCharacter.inventory.items[itemIndex].healthEffect > 0)
				{
					printf_s("(+%i HP) ", targetCharacter.inventory.items[itemIndex].healthEffect);
				}
				if(targetCharacter.inventory.items[itemIndex].healEffect > 0)
				{
					printf_s("(+%i HEAL) ", targetCharacter.inventory.items[itemIndex].healEffect);
				}
				putchar('\n');
			}
			printf_s("\nСреднняя стоимость: %i\n", targetCharacter.inventory.items[chosenItemIndex].sellPrice);
		}
		else
		{
			printf_s("\tПусто.\n");
		}

		printf_s("\n\nУправление: \n\t[t/T] Выбросить [1/ВСЕ] единиц предмета\n\t[g/G] Забрать [1/ЗАДАННОЕ] кол-во предмета\n\t[Стрелки] Перемещение курсора\n\t[e] Закрыть инвентарь\n\t[I] Посмотреть расширенную информацию о предмете");

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
		case KBKey::keyIU:
			itemInfoPrint(targetCharacter.inventory.items[chosenItemIndex].itemID);
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
				printf_s("\t[%i] %s(%i/%i) ", itemIndex + 1, mainCharacter.inventory.items[itemIndex].name, mainCharacter.inventory.items[itemIndex].amount, mainCharacter.inventory.items[itemIndex].stackMax);
				if(mainCharacter.inventory.items[itemIndex].isEquipable)
				{
					printf_s("%s ", mainCharacter.inventory.items[itemIndex].isEquiped ? "(+)" : "(-)");
				}
				if(mainCharacter.inventory.items[itemIndex].dmgEffect > 0)
				{
					printf_s("(+%i DMG) ", mainCharacter.inventory.items[itemIndex].dmgEffect);
				}
				if(mainCharacter.inventory.items[itemIndex].healthEffect > 0)
				{
					printf_s("(+%i HP) ", mainCharacter.inventory.items[itemIndex].healthEffect);
				}
				if(mainCharacter.inventory.items[itemIndex].healEffect > 0)
				{
					printf_s("(+%i HEAL) ", mainCharacter.inventory.items[itemIndex].healEffect);
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
				printf_s("\t[%i] %12s ", itemIndex + 1, targetCharacter.inventory.items[itemIndex].name);
				if(targetCharacter.inventory.items[itemIndex].dmgEffect > 0)
				{
					printf_s("(+%i DMG) ", targetCharacter.inventory.items[itemIndex].dmgEffect);
				}
				if(targetCharacter.inventory.items[itemIndex].healthEffect > 0)
				{
					printf_s("(+%i HP) ", targetCharacter.inventory.items[itemIndex].healthEffect);
				}
				if(targetCharacter.inventory.items[itemIndex].healEffect > 0)
				{
					printf_s("(+%i HEAL) ", targetCharacter.inventory.items[itemIndex].healEffect);
				}
				putchar('\n');
			}
		}
		else
		{
			printf_s("\tПусто.\n");
		}

		printf_s("\nСтоимость покупки/продажи: %i\n",
				 chosenItemIndex < mainCharacter.inventory.itemsAmount ? int( mainCharacter.inventory.items[chosenItemIndex].sellPrice * 0.75) : int(targetCharacter.inventory.items[chosenItemIndex - mainCharacter.inventory.itemsAmount].sellPrice * 1.25));
		printf_s("\n\nУправление: \n\t[b/B] Купить/Продать [1/ЗАДАННОЕ] кол-во предмета\n\t[Стрелки] Перемещение курсора\n\t[s] Закрыть меню покупки\n\t[I] Посмотреть расширенную информацию о предмете");

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
		case KBKey::keyIU:
			if(chosenItemIndex < mainCharacter.inventory.itemsAmount)
			{
				itemInfoPrint(mainCharacter.inventory.items[chosenItemIndex].itemID);
			}
			else
			{
				itemInfoPrint(targetCharacter.inventory.items[chosenItemIndex - mainCharacter.inventory.itemsAmount].itemID);
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
	int finCoast = amount * item->sellPrice * 1.25;
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

	int finCoast = amount * item->sellPrice * 0.75;
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
	spaceCount += (inventory.capacityCurrent - inventory.itemsAmount) * 5000;	//	хардкод

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

	if(!inventory.items[itemIndex].isEquipable)
	{
		return ERR_INVENTORY_USE_EQUIP_INDEX_FAIL;
	}

	bool isMele = false;
	bool isArmor = false;

	switch(inventory.items[itemIndex].itemID)
	{
	case ItemID::oldSword:
	case ItemID::dworfAxe:
	case ItemID::volcanSword:
	case ItemID::silverSpear:
	case ItemID::goldenSword:
	case ItemID::justiceMantle:
	case ItemID::huntingGroundsSword:
	case ItemID::atlantAxe:
	case ItemID::spiritHammer:
	case ItemID::justiceHummer:
		isMele = true;
		break;
	case ItemID::leatherArmor:
	case ItemID::hunterArmor:
	case ItemID::corgArmor:
	case ItemID::chainMail:
	case ItemID::silverArmor:
	case ItemID::goldenArmor:
	case ItemID::dragonScaleArmor:
	case ItemID::godsMadeArmor:
	case ItemID::undeadKingArmor:
		isArmor = true;
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
			case ItemID::dworfAxe:
			case ItemID::volcanSword:
			case ItemID::silverSpear:
			case ItemID::goldenSword:
			case ItemID::justiceMantle:
			case ItemID::huntingGroundsSword:
			case ItemID::atlantAxe:
			case ItemID::spiritHammer:
			case ItemID::justiceHummer:
				if(isMele)
				{
					inventory.items[i].isEquiped = i == itemIndex ? true : false;
				}
				break;
			case ItemID::leatherArmor:
			case ItemID::hunterArmor:
			case ItemID::corgArmor:
			case ItemID::chainMail:
			case ItemID::silverArmor:
			case ItemID::goldenArmor:
			case ItemID::dragonScaleArmor:
			case ItemID::godsMadeArmor:
			case ItemID::undeadKingArmor:
				if(isArmor)
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
			characterModifDamageIncrease(character, inventory.items[i].dmgEffect);
			//characterModifVisionIncrease(character, inventory.items[i].visionEffect);
			characterModifHealthIncrease(character, inventory.items[i].healthEffect);
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
	case ItemID::dworfAxe:
	case ItemID::volcanSword:
	case ItemID::silverSpear:
	case ItemID::goldenSword:
	case ItemID::leatherArmor:
	case ItemID::hunterArmor:
	case ItemID::corgArmor:
	case ItemID::chainMail:
	case ItemID::silverArmor:
	case ItemID::goldenArmor:
	case ItemID::dragonScaleArmor:
	case ItemID::godsMadeArmor:
	case ItemID::undeadKingArmor:
	case ItemID::justiceMantle:
	case ItemID::huntingGroundsSword:
	case ItemID::atlantAxe:
	case ItemID::spiritHammer:
	case ItemID::justiceHummer:
		inventiryModeEquipMode(*entity.character, itemIndex);
		break;
	case ItemID::healFlaskLittle:
	case ItemID::healFlaskMedium:
	case ItemID::healFlaskLarge:
		entityCharacterGetHeal(entity, character.inventory.items[itemIndex].healEffect);
		inventoryItemRemoveByID(character.inventory, itemIndex, 1);
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

	pCharacter->spawnPoint = {worldEntity.coords.x, worldEntity.coords.y};
	pCharacter->manaBase = 0;
	pCharacter->manaModifitaion = 0;
	pCharacter->manaCurrent = pCharacter->manaBase + pCharacter->manaModifitaion;
	pCharacter->isAlive = true;

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
		pCharacter->inventory.capacityBase = 5;
		pCharacter->inventory.capacityModiffication = 0;
		pCharacter->inventory.capacityCurrent = pCharacter->inventory.capacityBase + pCharacter->inventory.capacityModiffication;
		pCharacter->damageBase = 50;
		pCharacter->damageModification = 0;
		pCharacter->damageCurrent = pCharacter->damageBase + pCharacter->damageModification;
		pCharacter->healthBase = 300;
		pCharacter->healthModification = 0;
		pCharacter->healthCurrent = pCharacter->healthBase + pCharacter->healthModification;
		pCharacter->healthReal = pCharacter->healthCurrent;
		pCharacter->visionRangeBase = 4;
		pCharacter->visionRangeModification = 0;
		pCharacter->visionRangeCurrent = pCharacter->visionRangeBase + pCharacter->visionRangeModification;
		break;
	case EntitySymb::store:
		pCharacter->killExpReward = -1000;
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
		pCharacter->visionRangeBase = 1;
		pCharacter->visionRangeModification = 4;
		pCharacter->visionRangeCurrent = pCharacter->visionRangeBase + pCharacter->visionRangeModification;
		for(int i = 2; i < (int) ItemID::_nextNotBuyable; i++)
		{
			inventoryItemAdd(pCharacter->inventory, (ItemID) i, 1);
		}
		break;
	case EntitySymb::enemyZomby:
		pCharacter->killExpReward =  50 + rand() % 10;
		pCharacter->team = Team::enemy;
		pCharacter->level = 1;
		pCharacter->inventory.itemsAmount = 0;
		pCharacter->inventory.capacityBase = 2;
		pCharacter->inventory.capacityModiffication = 0;
		pCharacter->inventory.capacityCurrent = pCharacter->inventory.capacityBase + pCharacter->inventory.capacityModiffication;
		pCharacter->damageBase = 8 + rand() % 4;
		pCharacter->damageModification = 0;
		pCharacter->damageCurrent = pCharacter->damageBase + pCharacter->damageModification;
		pCharacter->healthBase = 50;
		pCharacter->healthModification = 0;
		pCharacter->healthCurrent = pCharacter->healthBase + pCharacter->healthModification;
		pCharacter->healthReal = pCharacter->healthCurrent;
		pCharacter->visionRangeBase = 2;
		pCharacter->visionRangeModification = 0;
		pCharacter->visionRangeCurrent = pCharacter->visionRangeBase + pCharacter->visionRangeModification;
		break;
	case EntitySymb::enemySkeleton:
		pCharacter->killExpReward = 20 + rand() % 10;
		pCharacter->team = Team::enemy;
		pCharacter->level = 1;
		pCharacter->inventory.itemsAmount = 0;
		pCharacter->inventory.capacityBase = 2;
		pCharacter->inventory.capacityModiffication = 0;
		pCharacter->inventory.capacityCurrent = pCharacter->inventory.capacityBase + pCharacter->inventory.capacityModiffication;
		pCharacter->damageBase = 30 + rand() % 10;
		pCharacter->damageModification = 0;
		pCharacter->damageCurrent = pCharacter->damageBase + pCharacter->damageModification;
		pCharacter->healthBase = 125;
		pCharacter->healthModification = 0;
		pCharacter->healthCurrent = pCharacter->healthBase + pCharacter->healthModification;
		pCharacter->healthReal = pCharacter->healthCurrent;
		pCharacter->visionRangeBase = 2;
		pCharacter->visionRangeModification = 0;
		pCharacter->visionRangeCurrent = pCharacter->visionRangeBase + pCharacter->visionRangeModification;
		break;
	case EntitySymb::enemyGiant:
		pCharacter->killExpReward = 50 + rand() % 20;
		pCharacter->team = Team::enemy;
		pCharacter->level = 1;
		pCharacter->inventory.itemsAmount = 0;
		pCharacter->inventory.capacityBase = 2;
		pCharacter->inventory.capacityModiffication = 0;
		pCharacter->inventory.capacityCurrent = pCharacter->inventory.capacityBase + pCharacter->inventory.capacityModiffication;
		pCharacter->damageBase = 100 + rand() % 40;
		pCharacter->damageModification = 0;
		pCharacter->damageCurrent = pCharacter->damageBase + pCharacter->damageModification;
		pCharacter->healthBase = 1340;
		pCharacter->healthModification = 0;
		pCharacter->healthCurrent = pCharacter->healthBase + pCharacter->healthModification;
		pCharacter->healthReal = pCharacter->healthCurrent;
		pCharacter->visionRangeBase = 4;
		pCharacter->visionRangeModification = 0;
		pCharacter->visionRangeCurrent = pCharacter->visionRangeBase + pCharacter->visionRangeModification;
		break;
	case EntitySymb::enemyLarva:
		pCharacter->killExpReward = 40 + rand() % 20;
		pCharacter->team = Team::enemy;
		pCharacter->level = 1;
		pCharacter->inventory.itemsAmount = 0;
		pCharacter->inventory.capacityBase = 2;
		pCharacter->inventory.capacityModiffication = 0;
		pCharacter->inventory.capacityCurrent = pCharacter->inventory.capacityBase + pCharacter->inventory.capacityModiffication;
		pCharacter->damageBase = 90 + rand() % 15;
		pCharacter->damageModification = 0;
		pCharacter->damageCurrent = pCharacter->damageBase + pCharacter->damageModification;
		pCharacter->healthBase = 950;
		pCharacter->healthModification = 0;
		pCharacter->healthCurrent = pCharacter->healthBase + pCharacter->healthModification;
		pCharacter->healthReal = pCharacter->healthCurrent;
		pCharacter->visionRangeBase = 3;
		pCharacter->visionRangeModification = 0;
		pCharacter->visionRangeCurrent = pCharacter->visionRangeBase + pCharacter->visionRangeModification;
		break;
	case EntitySymb::enemyCorg:
		pCharacter->killExpReward = 55 + rand() % 30;
		pCharacter->team = Team::enemy;
		pCharacter->level = 1;
		pCharacter->inventory.itemsAmount = 0;
		pCharacter->inventory.capacityBase = 2;
		pCharacter->inventory.capacityModiffication = 0;
		pCharacter->inventory.capacityCurrent = pCharacter->inventory.capacityBase + pCharacter->inventory.capacityModiffication;
		pCharacter->damageBase = 120 + rand() % 30;
		pCharacter->damageModification = 0;
		pCharacter->damageCurrent = pCharacter->damageBase + pCharacter->damageModification;
		pCharacter->healthBase = 1200;
		pCharacter->healthModification = 0;
		pCharacter->healthCurrent = pCharacter->healthBase + pCharacter->healthModification;
		pCharacter->healthReal = pCharacter->healthCurrent;
		pCharacter->visionRangeBase = 5;
		pCharacter->visionRangeModification = 0;
		pCharacter->visionRangeCurrent = pCharacter->visionRangeBase + pCharacter->visionRangeModification;
		break;
	case EntitySymb::enemyBeastman:
		pCharacter->killExpReward = 50 + rand() % 40;
		pCharacter->team = Team::enemy;
		pCharacter->level = 1;
		pCharacter->inventory.itemsAmount = 0;
		pCharacter->inventory.capacityBase = 2;
		pCharacter->inventory.capacityModiffication = 0;
		pCharacter->inventory.capacityCurrent = pCharacter->inventory.capacityBase + pCharacter->inventory.capacityModiffication;
		pCharacter->damageBase = 80 + rand() % 20;
		pCharacter->damageModification = 0;
		pCharacter->damageCurrent = pCharacter->damageBase + pCharacter->damageModification;
		pCharacter->healthBase = 860;
		pCharacter->healthModification = 0;
		pCharacter->healthCurrent = pCharacter->healthBase + pCharacter->healthModification;
		pCharacter->healthReal = pCharacter->healthCurrent;
		pCharacter->visionRangeBase = 4;
		pCharacter->visionRangeModification = 0;
		pCharacter->visionRangeCurrent = pCharacter->visionRangeBase + pCharacter->visionRangeModification;
		break;
	case EntitySymb::enemyJudge:
		pCharacter->killExpReward = 250 + rand() % 100;
		pCharacter->team = Team::enemy;
		pCharacter->level = 1;
		pCharacter->inventory.itemsAmount = 0;
		pCharacter->inventory.capacityBase = 2;
		pCharacter->inventory.capacityModiffication = 0;
		pCharacter->inventory.capacityCurrent = pCharacter->inventory.capacityBase + pCharacter->inventory.capacityModiffication;
		pCharacter->damageBase = 190 + rand() % 80;
		pCharacter->damageModification = 0;
		pCharacter->damageCurrent = pCharacter->damageBase + pCharacter->damageModification;
		pCharacter->healthBase = 1900;
		pCharacter->healthModification = 0;
		pCharacter->healthCurrent = pCharacter->healthBase + pCharacter->healthModification;
		pCharacter->healthReal = pCharacter->healthCurrent;
		pCharacter->visionRangeBase = 6;
		pCharacter->visionRangeModification = 0;
		pCharacter->visionRangeCurrent = pCharacter->visionRangeBase + pCharacter->visionRangeModification;
		break;
	case EntitySymb::enemyDragon:
		pCharacter->killExpReward = 500 + rand() % 150;
		pCharacter->team = Team::enemy;
		pCharacter->level = 1;
		pCharacter->inventory.itemsAmount = 0;
		pCharacter->inventory.capacityBase = 2;
		pCharacter->inventory.capacityModiffication = 0;
		pCharacter->inventory.capacityCurrent = pCharacter->inventory.capacityBase + pCharacter->inventory.capacityModiffication;
		pCharacter->damageBase = 250 + rand() % 200;
		pCharacter->damageModification = 0;
		pCharacter->damageCurrent = pCharacter->damageBase + pCharacter->damageModification;
		pCharacter->healthBase = 1700;
		pCharacter->healthModification = 0;
		pCharacter->healthCurrent = pCharacter->healthBase + pCharacter->healthModification;
		pCharacter->healthReal = pCharacter->healthCurrent;
		pCharacter->visionRangeBase = 6;
		pCharacter->visionRangeModification = 0;
		pCharacter->visionRangeCurrent = pCharacter->visionRangeBase + pCharacter->visionRangeModification;
		break;
	case EntitySymb::enemyKri:
		pCharacter->killExpReward = 1000 + rand() % 500;
		pCharacter->team = Team::enemy;
		pCharacter->level = 1;
		pCharacter->inventory.itemsAmount = 0;
		pCharacter->inventory.capacityBase = 2;
		pCharacter->inventory.capacityModiffication = 0;
		pCharacter->inventory.capacityCurrent = pCharacter->inventory.capacityBase + pCharacter->inventory.capacityModiffication;
		pCharacter->damageBase = 1000 + rand() % 400;
		pCharacter->damageModification = 0;
		pCharacter->damageCurrent = pCharacter->damageBase + pCharacter->damageModification;
		pCharacter->healthBase = 5500;
		pCharacter->healthModification = 0;
		pCharacter->healthCurrent = pCharacter->healthBase + pCharacter->healthModification;
		pCharacter->healthReal = pCharacter->healthCurrent;
		pCharacter->visionRangeBase = 6;
		pCharacter->visionRangeModification = 0;
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
	int dropRandomizer = rand() % 100;

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
	case EntitySymb::store:
		break;
	case EntitySymb::enemyZomby:
		worldEntity.entitySymb = EntitySymb::enemyZombyDrop;
		if(dropRandomizer < 10)
		{
			inventoryItemAdd(worldEntity.character->inventory, ItemID::leatherArmor);
		}
		else if(dropRandomizer < 15)
		{
			inventoryItemAdd(worldEntity.character->inventory, ItemID::hunterArmor);
		}
		else if(dropRandomizer < 16)
		{
			inventoryItemAdd(worldEntity.character->inventory, ItemID::undeadKingArmor);
		}
		else if(dropRandomizer < 20)
		{
			inventoryItemAdd(worldEntity.character->inventory, ItemID::chainMail);
		}
		else if(dropRandomizer < 30)
		{
			inventoryItemAdd(worldEntity.character->inventory, ItemID::oldSword);
		}
		inventoryItemAdd(worldEntity.character->inventory, ItemID::gold, 10 + rand() % 10);
		break;
	case EntitySymb::enemySkeleton:
		worldEntity.entitySymb = EntitySymb::enemySkeletonDrop;
		if(dropRandomizer < 10)
		{
			inventoryItemAdd(worldEntity.character->inventory, ItemID::oldSword);
		}
		else if(dropRandomizer < 15)
		{
			inventoryItemAdd(worldEntity.character->inventory, ItemID::hunterArmor);
		}
		else if(dropRandomizer < 16)
		{
			inventoryItemAdd(worldEntity.character->inventory, ItemID::undeadKingArmor);
		}
		else if(dropRandomizer < 20)
		{
			inventoryItemAdd(worldEntity.character->inventory, ItemID::chainMail);
		}
		inventoryItemAdd(worldEntity.character->inventory, ItemID::gold, 30 + rand() % 20);
		break;
	case EntitySymb::enemyGiant:
		worldEntity.entitySymb = EntitySymb::enemyGiantDrop;
		if(dropRandomizer < 5)
		{
			inventoryItemAdd(worldEntity.character->inventory, ItemID::dragonScaleArmor);
		}
		else if(dropRandomizer < 10)
		{
			inventoryItemAdd(worldEntity.character->inventory, ItemID::atlantAxe);
		}
		else if(dropRandomizer < 15)
		{
			inventoryItemAdd(worldEntity.character->inventory, ItemID::spiritHammer);
		}
		else if(dropRandomizer < 30)
		{
			inventoryItemAdd(worldEntity.character->inventory, ItemID::dworfAxe);
		}
		else if(dropRandomizer < 35)
		{
			inventoryItemAdd(worldEntity.character->inventory, ItemID::goldenArmor);
		}
		else if(dropRandomizer < 40)
		{
			inventoryItemAdd(worldEntity.character->inventory, ItemID::silverArmor);
		}
		else if(dropRandomizer < 45)
		{
			inventoryItemAdd(worldEntity.character->inventory, ItemID::silverSpear);
		}
		else if(dropRandomizer < 50)
		{
			inventoryItemAdd(worldEntity.character->inventory, ItemID::goldenSword);
		}
		inventoryItemAdd(worldEntity.character->inventory, ItemID::gold, 200 + rand() % 100);
		break;
	case EntitySymb::enemyLarva:
		worldEntity.entitySymb = EntitySymb::enemyLarvaDrop;
		if(dropRandomizer < 10)
		{
			inventoryItemAdd(worldEntity.character->inventory, ItemID::atlantAxe);
		}
		else if(dropRandomizer < 15)
		{
			inventoryItemAdd(worldEntity.character->inventory, ItemID::goldenArmor);
		}
		else if(dropRandomizer < 20)
		{
			inventoryItemAdd(worldEntity.character->inventory, ItemID::silverArmor);
		}
		else if(dropRandomizer < 25)
		{
			inventoryItemAdd(worldEntity.character->inventory, ItemID::silverSpear);
		}
		else if(dropRandomizer < 30)
		{
			inventoryItemAdd(worldEntity.character->inventory, ItemID::goldenSword);
		}
		else if(dropRandomizer < 35)
		{
			inventoryItemAdd(worldEntity.character->inventory, ItemID::volcanSword);
		}
		inventoryItemAdd(worldEntity.character->inventory, ItemID::gold, 150 + rand() % 100);
		break;
	case EntitySymb::enemyCorg:
		worldEntity.entitySymb = EntitySymb::enemyCorgDrop;
		if(dropRandomizer < 10)
		{
			inventoryItemAdd(worldEntity.character->inventory, ItemID::corgArmor);
		}
		else if(dropRandomizer < 25)
		{
			inventoryItemAdd(worldEntity.character->inventory, ItemID::dworfAxe);
		}
		else if(dropRandomizer < 30)
		{
			inventoryItemAdd(worldEntity.character->inventory, ItemID::volcanSword);
		}
		inventoryItemAdd(worldEntity.character->inventory, ItemID::gold, 250 + rand() % 100);
		break;
	case EntitySymb::enemyBeastman:
		if(dropRandomizer < 5)
		{
			inventoryItemAdd(worldEntity.character->inventory, ItemID::huntingGroundsSword);
		}
		else if(dropRandomizer < 10)
		{
			inventoryItemAdd(worldEntity.character->inventory, ItemID::goldenArmor);
		}
		else if(dropRandomizer < 15)
		{
			inventoryItemAdd(worldEntity.character->inventory, ItemID::silverArmor);
		}
		else if(dropRandomizer < 20)
		{
			inventoryItemAdd(worldEntity.character->inventory, ItemID::silverSpear);
		}
		else if(dropRandomizer < 25)
		{
			inventoryItemAdd(worldEntity.character->inventory, ItemID::goldenSword);
		}
		inventoryItemAdd(worldEntity.character->inventory, ItemID::gold, 180 + rand() % 100);
		break;
		worldEntity.entitySymb = EntitySymb::enemyBeastmanDrop;
		break;
	case EntitySymb::enemyKri:
		if(dropRandomizer < 5)
		{
			inventoryItemAdd(worldEntity.character->inventory, ItemID::godsMadeArmor);
		}
		inventoryItemAdd(worldEntity.character->inventory, ItemID::gold, 6500 + rand() % 1000);
		worldEntity.entitySymb = EntitySymb::enemyKriDrop;
		break;
	case EntitySymb::enemyJudge:
		if(dropRandomizer < 5)
		{
			inventoryItemAdd(worldEntity.character->inventory, ItemID::godsMadeArmor);
		}
		else if(dropRandomizer < 10)
		{
			inventoryItemAdd(worldEntity.character->inventory, ItemID::justiceHummer);
		}
		else if(dropRandomizer < 15)
		{
			inventoryItemAdd(worldEntity.character->inventory, ItemID::justiceMantle);
		}
		else if(dropRandomizer < 20)
		{
			inventoryItemAdd(worldEntity.character->inventory, ItemID::goldenArmor);
		}
		else if(dropRandomizer < 25)
		{
			inventoryItemAdd(worldEntity.character->inventory, ItemID::goldenSword);
		}
		inventoryItemAdd(worldEntity.character->inventory, ItemID::gold, 1500 + rand() % 500);
		worldEntity.entitySymb = EntitySymb::enemyJudgeDrop;
		break;
	case EntitySymb::enemyDragon:
		if(dropRandomizer < 5)
		{
			inventoryItemAdd(worldEntity.character->inventory, ItemID::godsMadeArmor);
		}
		else if(dropRandomizer < 10)
		{
			inventoryItemAdd(worldEntity.character->inventory, ItemID::spiritHammer);
		}
		inventoryItemAdd(worldEntity.character->inventory, ItemID::gold, 2500 + rand() % 1000);
		worldEntity.entitySymb = EntitySymb::enemyDragonDrop;
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
				char name[ENTITY_NAME_LEN_MAX] = "Хеймид";
				strcpy_s(pEntityNew[entityAmount - 1].name, ENTITY_NAME_LEN_MAX, name);
				break;
			}
		case EntitySymb::store:
			{
				char name[ENTITY_NAME_LEN_MAX] = "Странствующий торговец";
				strcpy_s(pEntityNew[entityAmount - 1].name, ENTITY_NAME_LEN_MAX, name);
				break;
			}
		case EntitySymb::enemyZomby:
			{
				char name[ENTITY_NAME_LEN_MAX] = "Гниющий мертвец";
				strcpy_s(pEntityNew[entityAmount - 1].name, ENTITY_NAME_LEN_MAX, name);
				break;
			}
		case EntitySymb::enemySkeleton:
			{
				char name[ENTITY_NAME_LEN_MAX] = "Оживший скелет";
				strcpy_s(pEntityNew[entityAmount - 1].name, ENTITY_NAME_LEN_MAX, name);
				break;
			}
		case EntitySymb::enemyGiant:
			{
				char name[ENTITY_NAME_LEN_MAX] = "Великан";
				strcpy_s(pEntityNew[entityAmount - 1].name, ENTITY_NAME_LEN_MAX, name);
				break;
			}
		case EntitySymb::enemyLarva:
			{
				char name[ENTITY_NAME_LEN_MAX] = "Кислотная ларва";
				strcpy_s(pEntityNew[entityAmount - 1].name, ENTITY_NAME_LEN_MAX, name);
				break;
			}
		case EntitySymb::enemyCorg:
			{
				char name[ENTITY_NAME_LEN_MAX] = "Корг";
				strcpy_s(pEntityNew[entityAmount - 1].name, ENTITY_NAME_LEN_MAX, name);
				break;
			}
		case EntitySymb::enemyBeastman:
			{
				char name[ENTITY_NAME_LEN_MAX] = "Зверолюд";
				strcpy_s(pEntityNew[entityAmount - 1].name, ENTITY_NAME_LEN_MAX, name);
				break;
			}
		case EntitySymb::enemyKri:
			{
				char name[ENTITY_NAME_LEN_MAX] = "Крий";
				strcpy_s(pEntityNew[entityAmount - 1].name, ENTITY_NAME_LEN_MAX, name);
				break;
			}
		case EntitySymb::enemyJudge:
			{
				char name[ENTITY_NAME_LEN_MAX] = "Вершащий закон";
				strcpy_s(pEntityNew[entityAmount - 1].name, ENTITY_NAME_LEN_MAX, name);
				break;
			}
		case EntitySymb::enemyDragon:
			{
				char name[ENTITY_NAME_LEN_MAX] = "Дракон";
				strcpy_s(pEntityNew[entityAmount - 1].name, ENTITY_NAME_LEN_MAX, name);
				break;
			}
		case EntitySymb::camera:
			{
				char name[ENTITY_NAME_LEN_MAX] = "_Camera";
				strcpy_s(pEntityNew[entityAmount - 1].name, ENTITY_NAME_LEN_MAX, name);
				break;
			}
		case EntitySymb::spawner:
			{
				char name[ENTITY_NAME_LEN_MAX] = "Алтарь";
				strcpy_s(pEntityNew[entityAmount - 1].name, ENTITY_NAME_LEN_MAX, name);
				break;
			}
		default:
			{
				log("worldEntityAdd(): Неизветсный тип добавляемого Entity");
				char name[ENTITY_NAME_LEN_MAX] = "_Empty";
				strcpy_s(pEntityNew[entityAmount - 1].name, ENTITY_NAME_LEN_MAX, name);
				break;
			}
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
		bool isUpdateVision = entity.character->visionRangeCurrent < 11 ? true : false;
		bool isUpdateInventory = entity.character->inventory.capacityCurrent < INVENTORY_CAPACITY_MAX;
		int num;
		do
		{
			printf("Выберетите что бы вы хотели прокачать \n"
				   "\t[1] Прокачать урон на 15 едениц\n"
				   "\t[2] Прокачать здоровье на 25 едениц\n");
			if(isUpdateVision)
			{
				printf("\t[3] Прокачать диапазон видимости на 1 еденицу\n");
			}
			if(isUpdateInventory)
			{
				printf("\t[4] Прокачать вместимость инвентаря на 1 еденицу\n");
			}
			scanf_s("%i", &num);
		} while(num <= 0 || num > 4 || (!isUpdateVision && num == 3) || (!isUpdateInventory && num == 4));
		switch(num)
		{
		case 1:
			entity.character->damageModification += 15;
			break;
		case 2:
			entity.character->healthModification += 25;
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

void characterModifDamageIncrease(Character &character, int increase)
{
	character.damageModification += increase;
}

void characterModifVisionIncrease(Character &character, int increase)
{
	character.visionRangeModification += increase;
}

void characterModifHealthIncrease(Character &character, int increase)
{
	character.healthModification += increase;
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