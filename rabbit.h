#pragma once
#include "rabbit.h"
#include "object.h"

void RabbitTurn(ObjectPointer rabbit, int** world, int worldHeight, int worldWidth, int currentGen, ObjectPointer worldObjects, int myIndex, int size);
void RabbitCheckCells(ObjectPointer rabbit, int** world, int worldHeight, int worldWidth, int* outAvailableCells, int* outCellCount);
void RabbitMove(ObjectPointer rabbit, int direction, ObjectPointer worldObjects, int myIndex, int size);
void RabbitCheckConflicts(ObjectPointer rabbit, int myIndex, ObjectPointer worldObjects, int size);