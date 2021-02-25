#include "RL_world_struct.h"


////////////////////////////////////////////////////////////
////////////////////FUNCTIONS_DEFINITION////////////////////
////////////////////////////////////////////////////////////


#ifdef DEBUG

void printWorldDebug(World &world)
{
	for(int i = 0; i < world.entityAmount; i++)
	{
		printf_s("[%i] %12s [%i/%i]: ", world.pEntity[i].ID, world.pEntity[i].name, world.pEntity[i].coords.x, world.pEntity[i].coords.y);
		if(world.pEntity[i].character != nullptr)
		{
			printf_s("\n\t[isAlive: %c] [DMG: %i] [HLTH: %i] [MNA: %i] [LVL: %i] [INV: %i/%i] [isVisn: %c]", world.pEntity[i].character->isAlive ? 'T' : 'F', world.pEntity[i].character->damageCurrent, world.pEntity[i].character->healthCurrent,
					 world.pEntity[i].character->manaCurrent, world.pEntity[i].character->level, world.pEntity[i].character->inventory.itemsAmount, world.pEntity[i].character->inventory.capacityCurrent, world.pEntity[i].isInRange ? 'T' : 'F');
		}
		puts("\n");
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

	pWorldNew->pEntity = nullptr;
	pWorldNew->entityAmount = 0;
	pWorldNew->mainCharacterID = EntityAdd(pWorldNew->pEntity, pWorldNew->entityAmount,
										   EntitySymb::mainCharacter, mainCharacterCoords);
	pWorldNew->cameraID = EntityAdd(pWorldNew->pEntity, pWorldNew->entityAmount,
									EntitySymb::camera, mainCharacterCoords);
	pWorldNew->cameraRange = 18;
	pWorldNew->isMapMode = false;

	pWorldNew->pCell = nullptr;
	pWorldNew->cellsColsAmount = 0;
	pWorldNew->cellsRowsAmount = 0;
	strcpy_s(pWorldNew->levelName, PATH_NAME_LEN_MAX, worldName);
	worldLoadLevel(*pWorldNew);

	worldDestruct(world);
	world = pWorldNew;

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

int printWorldLevel(const World &world)
{
	for(int i = world.pEntity[world.cameraID].coords.y - world.cameraRange / 3; i != (world.pEntity[world.cameraID].coords.y + world.cameraRange / 3) + 1; i++)
	{
		for(int j = world.pEntity[world.cameraID].coords.x - world.cameraRange; j != world.pEntity[world.cameraID].coords.x + world.cameraRange + 1; j++)
		{
			if(i < 0 || i >= world.cellsRowsAmount || j < 0 || j >= world.cellsColsAmount || !world.pCell[j][i].isReserched)
			{
				putchar((char) CellSymb::empty);
				continue;
			}
			else
			{
				putchar((char) world.pCell[j][i].cellSymb);
			}

			for(int k = 0; k < world.entityAmount; k++)
			{
				if(world.pEntity[k].isInRange && world.pEntity[k].coords.x == j && world.pEntity[k].coords.y == i && world.pEntity[k].ID != world.pEntity[world.cameraID].ID)
				{
					putchar('\b');
					putchar((char) world.pEntity[k].entitySymb);
				}
			}
		}


		putchar('\n');

	}

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
			if(!world.isMapMode)
			{
				world.pEntity[world.mainCharacterID].direction = Direction::up;
				world.pEntity[world.cameraID].direction = Direction::stay;
			}
			else
			{
				world.pEntity[world.mainCharacterID].direction = Direction::stay;
				world.pEntity[world.cameraID].direction = Direction::up;
			}
			isEOI = true;
			break;
		case KBKey::keyDownArrow:
			if(!world.isMapMode)
			{
				world.pEntity[world.mainCharacterID].direction = Direction::down;
				world.pEntity[world.cameraID].direction = Direction::stay;
			}
			else
			{
				world.pEntity[world.mainCharacterID].direction = Direction::stay;
				world.pEntity[world.cameraID].direction = Direction::down;
			}
			isEOI = true;
			break;
		case KBKey::keyLeftArrow:
			if(!world.isMapMode)
			{
				world.pEntity[world.mainCharacterID].direction = Direction::left;
				world.pEntity[world.cameraID].direction = Direction::stay;
			}
			else
			{
				world.pEntity[world.mainCharacterID].direction = Direction::stay;
				world.pEntity[world.cameraID].direction = Direction::left;
			}
			isEOI = true;
			break;
		case KBKey::keyRightArrow:
			if(!world.isMapMode)
			{
				world.pEntity[world.mainCharacterID].direction = Direction::right;
				world.pEntity[world.cameraID].direction = Direction::stay;
			}
			else
			{
				world.pEntity[world.mainCharacterID].direction = Direction::stay;
				world.pEntity[world.cameraID].direction = Direction::right;
			}
			isEOI = true;
			break;
		case KBKey::keyReturn:
			if(!world.isMapMode)
			{
				world.pEntity[world.mainCharacterID].direction = Direction::stay;
				world.pEntity[world.cameraID].direction = Direction::stay;
			}
			else
			{
				world.pEntity[world.mainCharacterID].direction = Direction::stay;
				world.pEntity[world.cameraID].direction = Direction::stay;
			}
			isEOI = true;
			break;
		case KBKey::keyM:
			world.isMapMode = !world.isMapMode;
			break;
		case KBKey::key9:
			exit(ERR_NO_ERR);
			break;
		default:
			break;	//	сообщение в UI : нет такой кнопки
		}
	} while(!isEOI);

	return ERR_NO_ERR;
}

int worldLogic(World &world)
{
	// Entity - эвенты
	for(int i = 0; i < world.entityAmount; i++)
	{
		// Привязка камеры к основному персонажу. Режим карты.
		if(!world.isMapMode)
		{
			world.pEntity[world.cameraID].coords = world.pEntity[world.mainCharacterID].coords;
		}

		// Передвижение Entity
		switch(world.pEntity[i].direction)
		{
		case Direction::up:
			if(world.pCell[world.pEntity[i].coords.x][world.pEntity[i].coords.y - 1].isGhost)
			{
				world.pCell[world.pEntity[i].coords.x][world.pEntity[i].coords.y - 1].isGhost = false;
				world.pCell[world.pEntity[i].coords.x][world.pEntity[i].coords.y].isGhost = true;
				world.pEntity[i].coords.y -= 1;
			}
			break;
		case Direction::down:
			if(world.pCell[world.pEntity[i].coords.x][world.pEntity[i].coords.y + 1].isGhost)
			{
				world.pCell[world.pEntity[i].coords.x][world.pEntity[i].coords.y + 1].isGhost = false;
				world.pCell[world.pEntity[i].coords.x][world.pEntity[i].coords.y].isGhost = true;
				world.pEntity[i].coords.y += 1;
			}
			break;
		case Direction::left:
			if(world.pCell[world.pEntity[i].coords.x - 1][world.pEntity[i].coords.y].isGhost)
			{
				world.pCell[world.pEntity[i].coords.x - 1][world.pEntity[i].coords.y].isGhost = false;
				world.pCell[world.pEntity[i].coords.x][world.pEntity[i].coords.y].isGhost = true;
				world.pEntity[i].coords.x -= 1;
			}
			break;
		case Direction::right:
			if(world.pCell[world.pEntity[i].coords.x + 1][world.pEntity[i].coords.y].isGhost)
			{
				world.pCell[world.pEntity[i].coords.x + 1][world.pEntity[i].coords.y].isGhost = false;
				world.pCell[world.pEntity[i].coords.x][world.pEntity[i].coords.y].isGhost = true;
				world.pEntity[i].coords.x += 1;
			}
			break;
		case Direction::stay:
			if(world.pCell[world.pEntity[i].coords.x][world.pEntity[i].coords.y].isGhost)
			{
				world.pCell[world.pEntity[i].coords.x][world.pEntity[i].coords.y].isGhost = false;
			}
			break;
		default:
			log("worldLogic(): Получено не существующее Direction");
			break;
		}

		// Entity.Character - эвенты
		if(world.pEntity[i].character != nullptr)
		{
			//	Entity.Character MainCharacter - эвенты
			if(world.pEntity[i].ID == world.mainCharacterID)
			{
				//	Сис-ма изучения карты, вижн на Entity
				for(int q = 0; q < world.entityAmount; q++)
				{
					world.pEntity[q].isInRange = false;
				}

				for(int curY = world.pEntity[i].coords.y, _i = 0; curY <= world.pEntity[i].coords.y + world.pEntity[i].character->visionRangeCurrent; curY++, _i++)
				{
					for(int curX = world.pEntity[i].coords.x; curX <= world.pEntity[i].coords.x + world.pEntity[i].character->visionRangeCurrent - _i; curX++)
					{
						int tmpY = curY - 2 * abs(world.pEntity[i].coords.y - curY);
						int tmpX = curX - 2 * abs(world.pEntity[i].coords.x - curX);



						for(int q = 0; q < world.entityAmount; q++)
						{
							if((world.pEntity[q].coords.x == curX && world.pEntity[q].coords.y == curY) || (world.pEntity[q].coords.x == tmpX && world.pEntity[q].coords.y == curY) ||
							   (world.pEntity[q].coords.x == curX && world.pEntity[q].coords.y == tmpY) || (world.pEntity[q].coords.x == tmpX && world.pEntity[q].coords.y == tmpY))
							{
								world.pEntity[q].isInRange = true;
							}
						}

						world.pCell[curX][curY].isReserched = true;


						if(tmpX < world.cellsColsAmount && tmpX >= 0)
						{
							world.pCell[tmpX][curY].isReserched = true;

							if(tmpY < world.cellsRowsAmount && tmpY >= 0)
							{
								world.pCell[tmpX][tmpY].isReserched = true;
							}
						}

						world.pCell[curX][tmpY].isReserched = true;
					}
				}
			}
		}
	}

	return ERR_NO_ERR;
}