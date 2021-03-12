#include "RL_world_struct.h"



////////////////////////////////////////////////////////////
////////////////////FUNCTIONS_DEFINITION////////////////////
////////////////////////////////////////////////////////////


#ifdef DEBUG
void printWorldDebug(const World &world)
{
	printf_s("Global Tick/BigTick: %i/%i\n", world.globTick, world.globBigTick);
	for(int i = 0; i < world.entityAmount; i++)
	{
		printf_s("[%i]%12s[%i/%i]", world.pEntity[i].ID, world.pEntity[i].name, world.pEntity[i].coords.x, world.pEntity[i].coords.y);
		if(world.pEntity[i].spawner != nullptr)
		{
			printf_s("(%c[%i/%i])", world.pEntity[i].spawner->entityToSpawn, world.pEntity[i].spawner->curIDs, world.pEntity[i].spawner->maxIDs);
		}
		if(world.pEntity[i].character != nullptr)
		{
			printf_s(": %s|TEAM:%i|DMG:%i|HLTH:%i/%i|MNA:%i|LVL:%i|INV:%i/%i|isVisn:%c",
					 world.pEntity[i].character->isAlive ? "ALIVE" : "DEAD", world.pEntity[i].character->team, world.pEntity[i].character->damageCurrent, world.pEntity[i].character->healthReal, world.pEntity[i].character->healthCurrent,
					 world.pEntity[i].character->manaCurrent, world.pEntity[i].character->level, world.pEntity[i].character->inventory.itemsAmount, world.pEntity[i].character->inventory.capacityCurrent, world.pEntity[i].isInRange ? 'T' : 'F');
		}
		putchar('\n');
	}
}
#endif // DEBUG

int worldInit(World *&world, Point mainCharacterCoords, const char *const worldName)
{
	World *pWorldNew = (World *) malloc(sizeof(*pWorldNew));
	if(!pWorldNew)
	{
		log("worldInit(): Ошибка выделения памяти. *pWorldNew = nullptr.");
		exit(ERR_MEMORY);
	}

	pWorldNew->globTick = -1;
	pWorldNew->globBigTick = 0;

	pWorldNew->pEntity = nullptr;
	pWorldNew->entityAmount = 0;
	pWorldNew->mainCharacterID = EntityAdd(pWorldNew->pEntity, pWorldNew->entityAmount,
										   EntitySymb::mainCharacter, mainCharacterCoords);
	pWorldNew->cameraID = EntityAdd(pWorldNew->pEntity, pWorldNew->entityAmount,
									EntitySymb::camera, mainCharacterCoords);
	pWorldNew->cameraRange = 24;

	pWorldNew->pCell = nullptr;
	pWorldNew->cellsColsAmount = 0;
	pWorldNew->cellsRowsAmount = 0;
	strcpy_s(pWorldNew->levelName, PATH_NAME_LEN_MAX, worldName);
	worldLoadLevel(*pWorldNew);

	for(int i = 0; i < CAMERA_RANGE_MAX * 2 - 1; i++)
	{
		for(int j = 0; j < CONDITION_STR_ONELINE_MAX; j++)
		{
			pWorldNew->ConditionString[i][j] = '\0';
		}
	}

	worldDestruct(world);
	world = pWorldNew;

	worldReserchArea(*world, {167, 0}, {255,48});

	return ERR_NO_ERR;
}

int worldDestruct(World *&world)
{
	if(!world)
	{
		return ERR_NO_ERR;
	}

	for(int i = 0; i < world->entityAmount; i++)
	{
		EntityRemove(world->pEntity, world->entityAmount, world->pEntity[i].ID);
	}
	for(int i = 0; i < world->cellsColsAmount; i++)
	{
		free(world->pCell[i]);
	}
	free(world->pCell);

	free(world);
	world = nullptr;

	return ERR_NO_ERR;
}

int worldLoadLevel(World &world)
{
	world.pCell = (Cell **) malloc(sizeof(*world.pCell) * MAP_WIDTH_MAX);

	if(!world.pCell)
	{
		log("worldLoadLevel(): не получилось выделить память. **pCell = nullptr");
		exit(ERR_MEMORY);
	}

	for(int i = 0; i < MAP_WIDTH_MAX; i++)
	{
		world.pCell[i] = (Cell *) malloc(sizeof(**world.pCell) * MAP_HEIGTH_MAX);

		if(!world.pCell)
		{
			log("worldLoadLevel(): не получилось выделить память. *pCell = nullptr");
			exit(ERR_MEMORY);
		}
	}

	char ptrLevelLine[MAP_WIDTH_MAX]{};

	FILE *fLevel = nullptr;
	if(fopen_s(&fLevel, world.levelName, "r"))
	{
		log("worldLoadLevel(): не получилось открыть файл с уровнем. *fLevel = nullptr");
		exit(ERR_FILE);
	}

	int row = 0;
	int col = 0;

	while(!feof(fLevel))
	{

		char endSymb;
		bool isEmpty = false;

		do
		{

			endSymb = '\0';

			if(!fgets(ptrLevelLine, MAP_WIDTH_MAX, fLevel))
			{
				isEmpty = true;
			}
			else
			{
				isEmpty = false;
			}

			if(strchr(ptrLevelLine, '\n'))
			{
				endSymb = '\n';
			}

			if(strchr(ptrLevelLine, endSymb) == ptrLevelLine)
			{
				isEmpty = true;
			}

		} while(isEmpty && !feof(fLevel));

		if(!isEmpty)
		{
			col = 0;
		}

		for(; ptrLevelLine[col] != endSymb && !isEmpty; col++)
		{
			world.pCell[col][row].cellSymb = (CellSymb) ptrLevelLine[col];
			world.pCell[col][row].isInRange = false;
			world.pCell[col][row].isReserched = false;

			switch((CellSymb) ptrLevelLine[col])
			{
			case CellSymb::ground:
				world.pCell[col][row].isGhost = true;
				break;
			case CellSymb::stone:
				world.pCell[col][row].isGhost = false;
				break;
			case CellSymb::wall:
				world.pCell[col][row].isGhost = false;
				break;
			case CellSymb::empty:
				world.pCell[col][row].isGhost = true;
				break;
			default:
				log("worldLoadLevel(): Получен неизвестный CellSymb");
				world.pCell[col][row].isGhost = true;
				break;
			}
		}

		if(!isEmpty)
			row++;
	}

	fclose(fLevel);

#ifdef DEBUG

	char *tempStr = (char *) malloc(col + 1);

	for(int rw = 0; rw < row; rw++)
	{
		for(int cl = 0; cl < col; cl++)
		{
			tempStr[cl] = (char) world.pCell[cl][rw].cellSymb;
		}
		tempStr[col] = '\0';
		log(tempStr, PATH_LOG_MAP);
	}

	free(tempStr);
	log("---------------------------------------------------", PATH_LOG_MAP);

#endif // DEBUG

	world.cellsRowsAmount = row;
	world.cellsColsAmount = col;

	return ERR_NO_ERR;
}

int printWorldLevel(const World &world, bool attackMode, Point attackPoint)
{
	system("cls");
	// Хэндл консоли ( если не понятно - гуглите/забейте )
	static HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	int textAttr = NULL;

	for(int i = world.pEntity[world.cameraID].coords.y - world.cameraRange / CAMERA_RANGE_Y_DEVIDER, curStr = 0; i != (world.pEntity[world.cameraID].coords.y + world.cameraRange / CAMERA_RANGE_Y_DEVIDER) + 1; i++, curStr++)
	{
		for(int j = world.pEntity[world.cameraID].coords.x - world.cameraRange; j != world.pEntity[world.cameraID].coords.x + world.cameraRange + 1; j++)
		{
			textAttr = NULL;
			if(i < 0 || i >= world.cellsRowsAmount || j < 0 || j >= world.cellsColsAmount || !world.pCell[j][i].isReserched)
			{
				textAttr = FOREGROUND_INTENSITY & ~FOREGROUND_RED & ~FOREGROUND_GREEN & ~FOREGROUND_BLUE;
				if(i >= -1 && i <= world.cellsRowsAmount && j >= -1 && j <= world.cellsColsAmount)
				{
					if(i > 0 && j != -1 && j != world.cellsColsAmount && world.pCell[j][i - 1].isReserched)
					{
						textAttr |= COMMON_LVB_GRID_HORIZONTAL;
					}
					if(i < world.cellsRowsAmount - 1 && j != -1 && j != world.cellsColsAmount && world.pCell[j][i + 1].isReserched)
					{
						textAttr |= COMMON_LVB_UNDERSCORE;
					}
					if(j > 0 && i != -1 && i != world.cellsRowsAmount && world.pCell[j - 1][i].isReserched)
					{
						textAttr |= COMMON_LVB_GRID_LVERTICAL;
					}
					if(j < world.cellsColsAmount - 1 && i != -1 && i != world.cellsRowsAmount && world.pCell[j + 1][i].isReserched)
					{
						textAttr |= COMMON_LVB_GRID_RVERTICAL;
					}
				}

				SetConsoleTextAttribute(hStdout, textAttr);
				putchar((char) CellSymb::empty);
				continue;
			}
			else
			{
				if(world.pCell[j][i].isInRange)
				{
					SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				}
				else
				{
					SetConsoleTextAttribute(hStdout, FOREGROUND_BLUE);
				}
				putchar((char) world.pCell[j][i].cellSymb);
				for(int k = 0; k < world.entityAmount; k++)
				{
					if((world.pEntity[k].isInRange || world.pEntity[k].spawner != nullptr) && world.pEntity[k].coords.x == j && world.pEntity[k].coords.y == i && world.pEntity[k].ID != world.pEntity[world.cameraID].ID)
					{
						putchar('\b');
						switch(world.pEntity[k].entitySymb)
						{
						case EntitySymb::mainCharacter:
							SetConsoleTextAttribute(hStdout, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
							break;
						case EntitySymb::store:
							SetConsoleTextAttribute(hStdout, FOREGROUND_GREEN | FOREGROUND_INTENSITY | COMMON_LVB_UNDERSCORE);
							break;
						case EntitySymb::enemyZombyDrop:
						case EntitySymb::enemySkeletonDrop:
						case EntitySymb::enemyGiantDrop:
						case EntitySymb::enemyLarvaDrop:
						case EntitySymb::enemyCorgDrop:
						case EntitySymb::enemyBeastmanDrop:
						case EntitySymb::enemyKriDrop:
						case EntitySymb::enemyJudgeDrop:
						case EntitySymb::enemyDragonDrop:
							SetConsoleTextAttribute(hStdout, FOREGROUND_RED | COMMON_LVB_UNDERSCORE);
							break;
						case EntitySymb::enemyZomby:
						case EntitySymb::enemySkeleton:
						case EntitySymb::enemyGiant:
						case EntitySymb::enemyLarva:
						case EntitySymb::enemyCorg:
						case EntitySymb::enemyBeastman:
						case EntitySymb::enemyKri:
						case EntitySymb::enemyJudge:
						case EntitySymb::enemyDragon:
							SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_INTENSITY | COMMON_LVB_UNDERSCORE);
							break;
						default:
							break;
						}
						putchar((char) world.pEntity[k].entitySymb);
					}
				}

			}
			if(attackMode && attackPoint.y == i && attackPoint.x == j)
			{
				putchar('\b');
				putchar('*');
			}
		}
		SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		worldPrintLevelUI(world.ConditionString, curStr);
		putchar('\n');
	}
#ifdef DEBUG
	SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	printWorldDebug(world);
#endif // DEBUG
	return ERR_NO_ERR;
}

int worldInput(World &world)
{
	bool isEOI = false;	//	isEOI демонстрирует закончен ли ввод. (EOI - End of input)

	do
	{
		switch((KBKey) _getch())
		{
		case KBKey::keyUpArrow:
			world.pEntity[world.mainCharacterID].direction = Direction::up;
			isEOI = true;
			break;
		case KBKey::keyDownArrow:
			world.pEntity[world.mainCharacterID].direction = Direction::down;
			isEOI = true;
			break;
		case KBKey::keyLeftArrow:
			world.pEntity[world.mainCharacterID].direction = Direction::left;
			isEOI = true;
			break;
		case KBKey::keyRightArrow:
			world.pEntity[world.mainCharacterID].direction = Direction::right;
			isEOI = true;
			break;
		case KBKey::keyReturn:
			world.pEntity[world.mainCharacterID].direction = Direction::stay;
			isEOI = true;
			break;
		case KBKey::keyM:
			worldMapMode(world);
			printWorldLevel(world);
			break;
		case KBKey::keyA:
			worldCharacterAttack(world, world.pEntity[world.mainCharacterID], isEOI);
			printWorldLevel(world);
			break;
		case KBKey::keyI:
			entityInventoryMode(world.pEntity[world.mainCharacterID]);
			printWorldLevel(world);
			break;
		case KBKey::keyE:
			worldEntityCharacterDropLogic(world, world.pEntity[world.mainCharacterID]);
			printWorldLevel(world);
			break;
		case KBKey::keyS:
			worldEntityCharacterShopLogic(world, world.pEntity[world.mainCharacterID]);
			printWorldLevel(world);
			break;
		case KBKey::key9:
			exit(ERR_NO_ERR);
			break;
		default:
			break;
		}
	} while(!isEOI);

	return ERR_NO_ERR;
}

int worldLogic(World &world)
{
	// Entity - эвенты
	for(int i = 0; i < world.entityAmount; i++)
	{
		// Entity.Character - эвенты
		if(world.pEntity[i].character != nullptr)
		{
			world.pEntity[i].character->damageCurrent = world.pEntity[i].character->damageBase + world.pEntity[i].character->damageModification;
			world.pEntity[i].character->healthCurrent = world.pEntity[i].character->healthBase + world.pEntity[i].character->healthModification;
			world.pEntity[i].character->manaCurrent = world.pEntity[i].character->manaBase + world.pEntity[i].character->manaModifitaion;
			world.pEntity[i].character->visionRangeCurrent = world.pEntity[i].character->visionRangeBase + world.pEntity[i].character->visionRangeModification;
			world.pEntity[i].character->inventory.capacityCurrent = world.pEntity[i].character->inventory.capacityBase + world.pEntity[i].character->inventory.capacityModiffication;
			if(world.pEntity[i].character->healthReal > world.pEntity[i].character->healthCurrent)
			{
				world.pEntity[i].character->healthReal = world.pEntity[i].character->healthCurrent;
			}
			if(world.pEntity[i].character->healthReal < 0)
			{
				world.pEntity[i].character->healthReal = 0;
			}

			//	Entity.MainCharacter - эвенты
			if(world.pEntity[i].ID == world.mainCharacterID)
			{
				if(!world.pEntity[i].character->isAlive)
				{
					exit(ERR_NO_ERR);
				}

				entityLevelUpLogic(world.pEntity[i]);
			}
			//	Entity.!MainCharacter - эвенты
			else
			{
				if(world.pEntity[i].character->isAlive)
				{
					worldAiLogic(world, world.pEntity[i]);
				}
			}
		}

		world.pEntity[world.cameraID].coords = world.pEntity[world.mainCharacterID].coords;

		// Entity.Spawner - эвенты
		if(world.pEntity[i].spawner != nullptr)
		{
			worldEntitySpawnerLogic(world, world.pEntity[i].ID);
		}

		worldDirectionLogic(world, world.pEntity[i]);

	}
	worldIncreaseHistoryTime(world.globTick, world.globBigTick);
	worldUILogic(world);
	worldVisionLogic(world);
	if(world.globTick % 32 == 0)
	{
		worldEmptyCharacterClear(world);
	}


	return ERR_NO_ERR;
}

int worldAiLogic(World &world, Entity &entity)
{
	if(entity.character == nullptr)
	{
		return ERR_AI_POINTER_ACCESS;
	}

	bool soLong = false;
	if(abs(world.pEntity[world.mainCharacterID].coords.x - entity.coords.x) > CAMERA_RANGE_MAX || abs(world.pEntity[world.mainCharacterID].coords.y - entity.coords.y) > CAMERA_RANGE_MAX)
	{
		soLong = true;
	}
	bool agressive = false;

	//	Обработка врагов
	if(entity.character->team == Team::enemy)
	{
		//	В зоне отрисовки
		if(!soLong)
		{
			for(int visionX = entity.coords.x - entity.character->visionRangeCurrent; visionX <= entity.coords.x + entity.character->visionRangeCurrent; visionX++)
			{
				for(int visionY = entity.coords.y - entity.character->visionRangeCurrent; visionY <= entity.coords.y + entity.character->visionRangeCurrent; visionY++)
				{
					if(visionX == world.pEntity[world.mainCharacterID].coords.x && visionY == world.pEntity[world.mainCharacterID].coords.y)
					{
						agressive = true;
					}
				}
			}
			worldAiLogicChooseAction(world, entity, agressive);
		}
	}
	//	Обработка нейтралов
	else if(entity.character->team == Team::neutral)
	{
		worldAiLogicChooseAction(world, entity, agressive);
	}
	//	Обработка союзников
	else if(entity.character->team == Team::ally)
	{
		worldAiLogicChooseAction(world, entity, agressive);
	}

	return ERR_NO_ERR;
}

void worldAiLogicChooseAction(World &world, Entity &entity, bool agressive)
{
	int mX = world.pEntity[world.mainCharacterID].coords.x;
	int mY = world.pEntity[world.mainCharacterID].coords.y;
	int eX = entity.coords.x;
	int eY = entity.coords.y;

	Direction newDirection = Direction::stay;
	if(agressive)
	{
		bool canAttack = abs(mX - eX) == 1 ? abs(mY - eY) == 0 ? true : false : abs(mY - eY) == 1 && abs(mX - eX) == 0 ? true : false;

		if(canAttack)
		{
			bool trash;
			worldCharacterAttack(world, entity, trash, {mX, mY});
			return;
		}

		if(eX < mX)
		{
			if(eY < mY)
			{
				newDirection = rand() % 2 ? Direction::down : Direction::right;
			}
			else if(eY > mY)
			{
				newDirection = rand() % 2 ? Direction::up : Direction::right;
			}
			else
			{
				newDirection = Direction::right;
			}
		}
		else if(eX > mX)
		{
			if(eY < mY)
			{
				newDirection = rand() % 2 ? Direction::down : Direction::left;
			}
			else if(eY > mY)
			{
				newDirection = rand() % 2 ? Direction::up : Direction::left;
			}
			else
			{
				newDirection = Direction::left;
			}
		}
		else
		{
			if(eY < mY)
			{
				newDirection = Direction::down;
			}
			else if(eY > mY)
			{
				newDirection = Direction::up;
			}
			else
			{
				newDirection = Direction::stay;
			}
		}
	}
	else
	{
		bool soLongFromSpawnPoint = true;
		for(int x = eX - entity.character->visionRangeCurrent; x <= eX + entity.character->visionRangeCurrent; x++)
		{
			for(int y = eY - entity.character->visionRangeCurrent; y <= eY + entity.character->visionRangeCurrent; y++)
			{
				if(y == entity.character->spawnPoint.y && x == entity.character->spawnPoint.x)
				{
					soLongFromSpawnPoint = false;
					break;
				}
			}
		}

		if(!soLongFromSpawnPoint)
		{

			switch(rand() % 8)
			{
			case 0: newDirection = Direction::down; break;
			case 1: newDirection = Direction::up; break;
			case 2: newDirection = Direction::left; break;
			case 3: newDirection = Direction::right; break;
			default: break;
			}
		}
		else
		{
			if(eX < entity.character->spawnPoint.x)
			{
				if(eY < entity.character->spawnPoint.y)
				{
					newDirection = rand() % 2 ? Direction::down : Direction::right;
				}
				else if(eY > entity.character->spawnPoint.y)
				{
					newDirection = rand() % 2 ? Direction::up : Direction::right;
				}
				else
				{
					newDirection = Direction::right;
				}
			}
			else if(eX > entity.character->spawnPoint.x)
			{
				if(eY < entity.character->spawnPoint.y)
				{
					newDirection = rand() % 2 ? Direction::down : Direction::left;
				}
				else if(eY > entity.character->spawnPoint.y)
				{
					newDirection = rand() % 2 ? Direction::up : Direction::left;
				}
				else
				{
					newDirection = Direction::left;
				}
			}
			else
			{
				if(eY < entity.character->spawnPoint.y)
				{
					newDirection = Direction::down;
				}
				else if(eY > entity.character->spawnPoint.y)
				{
					newDirection = Direction::up;
				}
				else
				{
					newDirection = Direction::stay;
				}
			}
		}
	}

	entity.direction = newDirection;
}

void worldUILogic(World &world)
{
	char tmpLevel[16], tmpExp[16], tmpNextLevelExp[16];
	_itoa_s(world.pEntity[world.mainCharacterID].character->level, tmpLevel, 16, 10);
	_itoa_s(world.pEntity[world.mainCharacterID].character->expa, tmpExp, 16, 10);
	_itoa_s(world.pEntity[world.mainCharacterID].character->nextLevelExp, tmpNextLevelExp, 16, 10);
	strcpy_s(world.ConditionString[0], ENTITY_NAME_LEN_MAX, world.pEntity[world.mainCharacterID].name);
	strcat_s(world.ConditionString[0], CONDITION_STR_ONELINE_MAX, ", LVL: ");
	strcat_s(world.ConditionString[0], CONDITION_STR_ONELINE_MAX, tmpLevel);
	strcat_s(world.ConditionString[0], CONDITION_STR_ONELINE_MAX, ", EXP: ");
	strcat_s(world.ConditionString[0], CONDITION_STR_ONELINE_MAX, tmpExp);
	strcat_s(world.ConditionString[0], CONDITION_STR_ONELINE_MAX, "/");
	strcat_s(world.ConditionString[0], CONDITION_STR_ONELINE_MAX, tmpNextLevelExp);

	char tmpHealth[16], tmpHealthReal[16], tmpDamage[16], tmpVisionRange[16];
	_itoa_s(world.pEntity[world.mainCharacterID].character->healthCurrent, tmpHealth, 16, 10);
	_itoa_s(world.pEntity[world.mainCharacterID].character->healthReal, tmpHealthReal, 16, 10);
	_itoa_s(world.pEntity[world.mainCharacterID].character->damageCurrent, tmpDamage, 16, 10);
	_itoa_s(world.pEntity[world.mainCharacterID].character->visionRangeCurrent, tmpVisionRange, 16, 10);
	strcpy_s(world.ConditionString[1], CONDITION_STR_ONELINE_MAX, "HP: ");
	strcat_s(world.ConditionString[1], CONDITION_STR_ONELINE_MAX, tmpHealthReal);
	strcat_s(world.ConditionString[1], CONDITION_STR_ONELINE_MAX, "/");
	strcat_s(world.ConditionString[1], CONDITION_STR_ONELINE_MAX, tmpHealth);
	strcat_s(world.ConditionString[1], CONDITION_STR_ONELINE_MAX, ", DMG: ");
	strcat_s(world.ConditionString[1], CONDITION_STR_ONELINE_MAX, tmpDamage);
	strcat_s(world.ConditionString[1], CONDITION_STR_ONELINE_MAX, ", VSN: ");
	strcat_s(world.ConditionString[1], CONDITION_STR_ONELINE_MAX, tmpVisionRange);
}

void worldUIStrAdd(char(&ConditionString)[CAMERA_RANGE_MAX * 2 - 1][CONDITION_STR_ONELINE_MAX], const char *newString)
{
	for(int i = CAMERA_RANGE_MAX * 2 - 2; i > 2; i--)
	{
		strcpy_s(ConditionString[i], CONDITION_STR_ONELINE_MAX, ConditionString[i - 1]);
	}
	strcpy_s(ConditionString[2], CONDITION_STR_ONELINE_MAX, newString);
}

void worldVisionLogic(World &world)
{
	for(int q = 0; q < world.entityAmount; q++)
	{
		world.pEntity[q].isInRange = false;
	}

	for(int i = world.pEntity[world.cameraID].coords.y - world.cameraRange / CAMERA_RANGE_Y_DEVIDER; i != (world.pEntity[world.cameraID].coords.y + world.cameraRange / CAMERA_RANGE_Y_DEVIDER) + 1; i++)
	{
		for(int j = world.pEntity[world.cameraID].coords.x - world.cameraRange; j != world.pEntity[world.cameraID].coords.x + world.cameraRange + 1; j++)
		{
			if(i < 0 || i >= world.cellsRowsAmount || j < 0 || j >= world.cellsColsAmount)
			{
				continue;
			}
			world.pCell[j][i].isInRange = false;
		}
	}

	for(int curY = world.pEntity[world.mainCharacterID].coords.y, _i = 0; curY <= world.pEntity[world.mainCharacterID].coords.y + world.pEntity[world.mainCharacterID].character->visionRangeCurrent; curY++, _i++)
	{
		for(int curX = world.pEntity[world.mainCharacterID].coords.x; curX <= world.pEntity[world.mainCharacterID].coords.x + world.pEntity[world.mainCharacterID].character->visionRangeCurrent - _i; curX++)
		{
			int reversedY = curY - 2 * abs(world.pEntity[world.mainCharacterID].coords.y - curY);
			int reversedX = curX - 2 * abs(world.pEntity[world.mainCharacterID].coords.x - curX);

			for(int q = 0; q < world.entityAmount; q++)
			{
				if((world.pEntity[q].coords.x == curX && world.pEntity[q].coords.y == curY) || (world.pEntity[q].coords.x == reversedX && world.pEntity[q].coords.y == curY) ||
				   (world.pEntity[q].coords.x == curX && world.pEntity[q].coords.y == reversedY) || (world.pEntity[q].coords.x == reversedX && world.pEntity[q].coords.y == reversedY))
				{
					world.pEntity[q].isInRange = true;
				}
			}
			world.pCell[curX][curY].isReserched = true;
			world.pCell[curX][curY].isInRange = true;


			if(reversedX < world.cellsColsAmount && reversedX >= 0)
			{
				world.pCell[reversedX][curY].isReserched = true;
				world.pCell[reversedX][curY].isInRange = true;

				if(reversedY < world.cellsRowsAmount && reversedY >= 0)
				{
					world.pCell[reversedX][reversedY].isReserched = true;
					world.pCell[reversedX][reversedY].isInRange = true;
				}
			}
			if(reversedY < world.cellsRowsAmount && reversedY >= 0)
			{
				world.pCell[curX][reversedY].isReserched = true;
				world.pCell[curX][reversedY].isInRange = true;
			}
		}
	}
}

void worldIncreaseHistoryTime(int &tick, int &bigTick)
{
	if(tick == 65535)
	{
		bigTick += 1;
		tick = 0;
	}
	else
	{
		tick += 1;
	}
}

int worldDirectionLogic(World &world, Entity &entity)
{
	Point toGoPoint{0, 0};
	int stepSize = entity.ID == world.cameraID ? 10 : 1;

	switch(entity.direction)
	{
	case Direction::up:
		toGoPoint = {entity.coords.x, entity.coords.y - stepSize};
		break;
	case Direction::down:
		toGoPoint = {entity.coords.x, entity.coords.y + stepSize};
		break;
	case Direction::left:
		toGoPoint = {entity.coords.x - stepSize, entity.coords.y};
		break;
	case Direction::right:
		toGoPoint = {entity.coords.x + stepSize, entity.coords.y};
		break;
	case Direction::stay:
		toGoPoint = {entity.coords.x, entity.coords.y};
		break;
	default:
		log("worldLogic(): Получено не существующее Direction");
		break;
	}

	entity.direction = Direction::stay;

	if(world.cameraID == entity.ID)
	{
		worldEntityGoto(world, entity, toGoPoint, true);
	}
	else
	{
		worldEntityGoto(world, entity, toGoPoint);
	}

	return ERR_NO_ERR;
}

void worldMapMode(World &world)
{
	bool isMapMode = true;

	while(isMapMode)
	{
		switch((KBKey) _getch())
		{
		case KBKey::keyUpArrow:
			world.pEntity[world.cameraID].direction = Direction::up;
			break;
		case KBKey::keyDownArrow:
			world.pEntity[world.cameraID].direction = Direction::down;
			break;
		case KBKey::keyLeftArrow:
			world.pEntity[world.cameraID].direction = Direction::left;
			break;
		case KBKey::keyRightArrow:
			world.pEntity[world.cameraID].direction = Direction::right;
			break;
		case KBKey::keyM:
			isMapMode = false;
			break;
#ifdef DEBUG
		case KBKey::keyReturn:
			isMapMode = false;
			worldEntityGoto(world, world.pEntity[world.mainCharacterID], world.pEntity[world.cameraID].coords, true);
			break;
#endif // DEBUG
		case KBKey::key9:
			exit(ERR_NO_ERR);
			break;
		default:
			break;
		}

		worldDirectionLogic(world, world.pEntity[world.cameraID]);
		system("cls");
		printWorldLevel(world);
	}

	world.pEntity[world.cameraID].coords = world.pEntity[world.mainCharacterID].coords;
	world.pEntity[world.cameraID].direction = Direction::stay;
}

void worldCharacterHit(World &world, Entity &attacker, Entity &victim)
{
	if(victim.character->team != Team::enemy && attacker.ID == world.mainCharacterID)
	{
		worldUIStrAdd(world.ConditionString, "Атаковать возможно только вражеские войска!");
	}
	else if(!victim.character->isAlive && attacker.ID == world.mainCharacterID)
	{
		worldUIStrAdd(world.ConditionString, "Атаковать возможно только живые войска!");
	}
	else
	{
		victim.character->healthReal -= attacker.character->damageCurrent;
		char tmp[64];
		char tmp2[16];
		if(victim.character->healthReal <= 0)
		{
			characterExpIncrease(*attacker.character, victim.character->killExpReward);
			if(attacker.ID == world.mainCharacterID)
			{
				strcpy_s(tmp, 64, "Вы получили ");
				_itoa_s(victim.character->killExpReward, tmp2, 16, 10);
				strcat_s(tmp, 64, tmp2);
				strcat_s(tmp, 64, " EXP");
				worldUIStrAdd(world.ConditionString, tmp);
			}
			else if(victim.ID == world.mainCharacterID)
			{
				worldUIStrAdd(world.ConditionString, "Вы умерли");
			}
			entityCharacterDie(victim);
		}
		else
		{
			if(attacker.ID == world.mainCharacterID)
			{
				strcpy_s(tmp, 64, "У противника осталось ");
				_itoa_s(victim.character->healthReal, tmp2, 16, 10);
				strcat_s(tmp, 64, tmp2);
				strcat_s(tmp, 64, " HP");
				worldUIStrAdd(world.ConditionString, tmp);
			}
			else if(victim.ID == world.mainCharacterID)
			{
				strcpy_s(tmp, 64, "Противник нанес вам ");
				_itoa_s(attacker.character->damageCurrent, tmp2, 16, 10);
				strcat_s(tmp, 64, tmp2);
				strcat_s(tmp, 64, " DMG");
				worldUIStrAdd(world.ConditionString, tmp);
			}
		}
	}
}

int worldCharacterAttack(World &world, Entity &entity, bool &isEOI, Point attackPoint)
{
	if(entity.ID == world.mainCharacterID)
	{
		attackPoint = {entity.coords.x, entity.coords.y - 1};
		while(true)
		{
			system("cls");
			printWorldLevel(world, true, attackPoint);
			switch((KBKey) _getch())
			{
			case KBKey::keyUpArrow:
				attackPoint = {entity.coords.x, entity.coords.y - 1};
				break;
			case KBKey::keyDownArrow:
				attackPoint = {entity.coords.x, entity.coords.y + 1};
				break;
			case KBKey::keyRightArrow:
				attackPoint = {entity.coords.x + 1, entity.coords.y};
				break;
			case KBKey::keyLeftArrow:
				attackPoint = {entity.coords.x - 1, entity.coords.y};
				break;
			case KBKey::keyReturn:
				for(int i = 0; i < world.entityAmount; i++)
				{
					if(world.pEntity[i].character != nullptr && world.pEntity[i].coords.x == attackPoint.x && world.pEntity[i].coords.y == attackPoint.y)
					{
						worldCharacterHit(world, entity, world.pEntity[i]);
					}
				}
				isEOI = true;
				return ERR_NO_ERR;
				break;
			case KBKey::keyA:
				isEOI = false;
				return ERR_NO_ERR;
				break;
			default:
				break;
			}

		}
	}
	else
	{
		for(int i = 0; i < world.entityAmount; i++)
		{
			if(world.pEntity[i].character != nullptr && world.pEntity[i].coords.x == attackPoint.x && world.pEntity[i].coords.y == attackPoint.y)
			{
				worldCharacterHit(world, entity, world.pEntity[i]);
			}
		}
	}

	return ERR_NO_ERR;
}

int worldEntitySpawnerLogic(World &world, int spawnerID)
{
	int spawnerIndex = 0;
	for(; spawnerIndex < world.entityAmount; spawnerIndex++)
	{
		if(world.pEntity[spawnerIndex].ID == spawnerID)
		{
			break;
		}
	}

	bool needSpawn = world.pEntity[spawnerIndex].spawner->maxIDs > world.pEntity[spawnerIndex].spawner->curIDs;

	for(int i = (world.pEntity[spawnerIndex].coords.x - 2); i <= (world.pEntity[spawnerIndex].coords.x + 2) && needSpawn; i++)
	{
		for(int j = (world.pEntity[spawnerIndex].coords.y - 2); j <= (world.pEntity[spawnerIndex].coords.y + 2) && needSpawn; j++)
		{
			if(i >= 0 && j >= 0 && i < world.cellsColsAmount && j < world.cellsRowsAmount && world.pCell[i][j].isGhost == true)
			{
				if(rand() % 100 == 0)
				{
					world.pEntity[spawnerIndex].spawner->IDs[world.pEntity[spawnerIndex].spawner->curIDs++] = EntityAdd(world.pEntity, world.entityAmount, world.pEntity[spawnerIndex].spawner->entityToSpawn, {i,j});
					needSpawn = false;
				}
			}
		}
	}

	for(int i = 0; i < world.entityAmount; i++)
	{
		for(int j = 0; j < world.pEntity[spawnerIndex].spawner->curIDs; j++)
		{
			if(world.pEntity[i].ID == world.pEntity[spawnerIndex].spawner->IDs[j] && !world.pEntity[i].character->isAlive && world.pEntity[i].character->inventory.itemsAmount <= 0)
			{
				world.pCell[world.pEntity[i].coords.x][world.pEntity[i].coords.y].isGhost = true;
				EntityRemove(world.pEntity, world.entityAmount, world.pEntity[i].ID);
				for(int _i = j; _i < world.pEntity[spawnerIndex].spawner->maxIDs - 1; _i++)
				{
					world.pEntity[spawnerIndex].spawner->IDs[_i] = world.pEntity[spawnerIndex].spawner->IDs[_i + 1];
				}
				world.pEntity[spawnerIndex].spawner->curIDs--;
			}
		}
	}

	return ERR_NO_ERR;
}

void worldEntityGoto(World &world, Entity &entity, Point toGoPoint, bool isGhost)
{
	toGoPoint.x = toGoPoint.x < 0 ? 0 : toGoPoint.x >= world.cellsColsAmount ? world.cellsColsAmount - 1 : toGoPoint.x;
	toGoPoint.y = toGoPoint.y < 0 ? 0 : toGoPoint.y >= world.cellsRowsAmount ? world.cellsRowsAmount - 1 : toGoPoint.y;

	if(isGhost || world.pCell[toGoPoint.x][toGoPoint.y].isGhost)
	{
		if(!isGhost)
		{
			world.pCell[entity.coords.x][entity.coords.y].isGhost = true;
			world.pCell[toGoPoint.x][toGoPoint.y].isGhost = false;
		}
		else
		{
			if(entity.ID != world.cameraID)
			{
				world.pCell[entity.coords.x][entity.coords.y].isGhost = true;
			}
		}
		entity.coords = toGoPoint;
	}
}

int worldPrintLevelUI(const char(&ConditionString)[CAMERA_RANGE_MAX * 2 - 1][CONDITION_STR_ONELINE_MAX], int curY)
{

	if(curY > 3)
	{
		fputs(ConditionString[curY - 2], stdout);
	}
	else if(curY < 2)
	{
		fputs(ConditionString[curY], stdout);
	}
	else
	{
		switch(curY)
		{
		case 2:
			break;
		case 3:
			fputs("\tСтрока состояния:", stdout);
			break;
		default:
			log("printLevelUI(): неизвестный curY");
			return ERR_NO_ERR;
			break;
		}
	}
	return ERR_NO_ERR;
}

void worldEntityCharacterDropLogic(World &world, Entity &mainEntity)
{
	bool isLocalEOI = false;
	while(!isLocalEOI)
	{
		bool wasTarget = false;
		int targetIndex = 0;

		for(int characterX = mainEntity.coords.x - 1; characterX <= mainEntity.coords.x + 1; characterX++)
		{
			for(int characterY = mainEntity.coords.y - 1; characterY <= mainEntity.coords.y + 1; characterY++)
			{
				for(int targetEntity = 0; targetEntity < world.entityAmount; targetEntity++)
				{
					if(world.pEntity[targetEntity].character == nullptr)
					{
						continue;
					}

					if(!world.pEntity[targetEntity].character->isAlive && world.pEntity[targetEntity].character->inventory.itemsAmount > 0 &&
					   world.pEntity[targetEntity].coords.x == characterX && world.pEntity[targetEntity].coords.y == characterY)
					{
						wasTarget = true;
						targetIndex = targetEntity;
					}
				}
			}
		}

		if(wasTarget)
		{
			entityInventoryModeDrop(mainEntity, world.pEntity[targetIndex], isLocalEOI);
		}
		else
		{
			worldUIStrAdd(world.ConditionString, "Нечего забирать!");
			isLocalEOI = true;
		}
	}
}

void worldEntityCharacterShopLogic(World &world, Entity &mainEntity)
{
	bool isLocalEOI = false;
	while(!isLocalEOI)
	{
		bool wasTarget = false;
		int targetIndex = 0;

		for(int characterX = mainEntity.coords.x - 1; characterX <= mainEntity.coords.x + 1; characterX++)
		{
			for(int characterY = mainEntity.coords.y - 1; characterY <= mainEntity.coords.y + 1; characterY++)
			{
				for(int targetEntity = 0; targetEntity < world.entityAmount; targetEntity++)
				{
					if(world.pEntity[targetEntity].character == nullptr)
					{
						continue;
					}

					if(world.pEntity[targetEntity].entitySymb == EntitySymb::store &&
					   world.pEntity[targetEntity].coords.x == characterX && world.pEntity[targetEntity].coords.y == characterY)
					{
						wasTarget = true;
						targetIndex = targetEntity;
					}
				}
			}
		}

		if(wasTarget)
		{
			entityInventoryModeStore(mainEntity, world.pEntity[targetIndex], isLocalEOI);
		}
		else
		{
			worldUIStrAdd(world.ConditionString, "По близости нет торговцев!");
			isLocalEOI = true;
		}
	}
}

void worldEmptyCharacterClear(World &world)
{
	for(int i = 0; i < world.entityAmount; i++)
	{
		if(world.pEntity[i].character != nullptr && world.pEntity[i].character->inventory.itemsAmount <= 0 && !world.pEntity[i].character->isAlive && i != world.mainCharacterID)
		{
			EntityRemove(world.pEntity, world.entityAmount, world.pEntity[i].ID);
		}
	}
}

void worldEntityListLogic(char array[LIST_LEN_MAX][LIST_ROWS_MAX], int rowsCount)
{
	system("cls");

	for(int i = 0; i < rowsCount; i++)
	{
		printf("%s", array[i]);
	}
}

void worldReserchArea(World &world, Point leftHightPoint, Point rightLowPoint)
{
	if(leftHightPoint.x < 0 || leftHightPoint.x >= world.cellsColsAmount || leftHightPoint.y < 0 || leftHightPoint.y >= world.cellsRowsAmount)
	{
		log("worldReserchArea(): переданы невозможные значения.");
		return;
	}

	for(int x = leftHightPoint.x; x <= rightLowPoint.x; x++)
	{
		for(int y = leftHightPoint.y; y <= rightLowPoint.y; y++)
		{
			world.pCell[x][y].isReserched = true;
		}
	}
}