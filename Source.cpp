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

	srand(time(0));

#ifdef BETA
	readList("./lists/list-beta.list");
	atexit(demoLogo);
#endif // BETA

	World *pWorld = nullptr;
	worldInit(pWorld, {178, 22}, PATH_LEVEL);
	EntityAdd(pWorld->pEntity, pWorld->entityAmount, EntitySymb::store, {184,18});
	EntityAdd(pWorld->pEntity, pWorld->entityAmount, EntitySymb::store, {158,129}, true, 1);

	EntityAdd(pWorld->pEntity, pWorld->entityAmount, EntitySymb::enemyZomby, {167,7}, true, 4);
	EntityAdd(pWorld->pEntity, pWorld->entityAmount, EntitySymb::enemyZomby, {147,17}, true, 4);
	EntityAdd(pWorld->pEntity, pWorld->entityAmount, EntitySymb::enemyZomby, {147,28}, true, 4);
	EntityAdd(pWorld->pEntity, pWorld->entityAmount, EntitySymb::enemyZomby, {143,34}, true, 4);
	EntityAdd(pWorld->pEntity, pWorld->entityAmount, EntitySymb::enemyZomby, {140,143}, true, 4);
	EntityAdd(pWorld->pEntity, pWorld->entityAmount, EntitySymb::enemyZomby, {199,55}, true, 4);
	EntityAdd(pWorld->pEntity, pWorld->entityAmount, EntitySymb::enemyZomby, {174,68}, true, 4);
	EntityAdd(pWorld->pEntity, pWorld->entityAmount, EntitySymb::enemyZomby, {25,17}, true, 3);

	EntityAdd(pWorld->pEntity, pWorld->entityAmount, EntitySymb::enemySkeleton, {119,28}, true, 2);
	EntityAdd(pWorld->pEntity, pWorld->entityAmount, EntitySymb::enemySkeleton, {86,21}, true, 2);
	EntityAdd(pWorld->pEntity, pWorld->entityAmount, EntitySymb::enemySkeleton, {87,32}, true, 2);
	EntityAdd(pWorld->pEntity, pWorld->entityAmount, EntitySymb::enemySkeleton, {4,57}, true, 3);
	EntityAdd(pWorld->pEntity, pWorld->entityAmount, EntitySymb::enemySkeleton, {15,58}, true, 3);
	EntityAdd(pWorld->pEntity, pWorld->entityAmount, EntitySymb::enemySkeleton, {80,76}, true, 3);
	EntityAdd(pWorld->pEntity, pWorld->entityAmount, EntitySymb::enemySkeleton, {14,129}, true, 3);
	EntityAdd(pWorld->pEntity, pWorld->entityAmount, EntitySymb::enemySkeleton, {91,129}, true, 3);

	EntityAdd(pWorld->pEntity, pWorld->entityAmount, EntitySymb::enemyGiant, {34,24}, true, 2);
	EntityAdd(pWorld->pEntity, pWorld->entityAmount, EntitySymb::enemyGiant, {10,35}, true, 2);

	EntityAdd(pWorld->pEntity, pWorld->entityAmount, EntitySymb::enemyBeastman, {73,8}, true, 2);
	EntityAdd(pWorld->pEntity, pWorld->entityAmount, EntitySymb::enemyBeastman, {53,7}, true, 2);
	EntityAdd(pWorld->pEntity, pWorld->entityAmount, EntitySymb::enemyBeastman, {34,4}, true, 2);
	EntityAdd(pWorld->pEntity, pWorld->entityAmount, EntitySymb::enemyBeastman, {42,61}, true, 2);

	EntityAdd(pWorld->pEntity, pWorld->entityAmount, EntitySymb::enemyLarva, {8,41}, true, 2);
	EntityAdd(pWorld->pEntity, pWorld->entityAmount, EntitySymb::enemyLarva, {27,45}, true, 3);

	EntityAdd(pWorld->pEntity, pWorld->entityAmount, EntitySymb::enemyCorg, {64,51}, true, 2);
	EntityAdd(pWorld->pEntity, pWorld->entityAmount, EntitySymb::enemyCorg, {94,54}, true, 2);
	EntityAdd(pWorld->pEntity, pWorld->entityAmount, EntitySymb::enemyCorg, {57,38}, true, 2);

	EntityAdd(pWorld->pEntity, pWorld->entityAmount, EntitySymb::enemyDragon, {27,81}, true, 1);

	EntityAdd(pWorld->pEntity, pWorld->entityAmount, EntitySymb::enemyJudge, {33,108}, true, 1);
	EntityAdd(pWorld->pEntity, pWorld->entityAmount, EntitySymb::enemyJudge, {156,99}, true, 1);
	EntityAdd(pWorld->pEntity, pWorld->entityAmount, EntitySymb::enemyJudge, {36,119}, true, 1);
	EntityAdd(pWorld->pEntity, pWorld->entityAmount, EntitySymb::enemyJudge, {33,108}, true, 1);

	EntityAdd(pWorld->pEntity, pWorld->entityAmount, EntitySymb::enemyKri, {193,118});

	while(true)
	{
		worldLogic(*pWorld);
		printWorldLevel(*pWorld);
		worldInput(*pWorld);
	}

	worldDestruct(pWorld);
	return ERR_NO_ERR;
}