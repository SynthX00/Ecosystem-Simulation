#pragma once
#include "rabbit.h"
#include "object.h"

void RabbitTurn(ObjectPointer rabbit, int** world, int worldHeight, int worldWidth, int currentGen, ObjectPointer worldObjects, int* currentObjectIndex);
void RabbitCheckCells(ObjectPointer rabbit, int** world, int worldHeight, int worldWidth, int* outAvailableCells, int* outCellCount);
void RabbitMove(ObjectPointer rabbit, int direction, ObjectPointer worldObjects, int* outCurrentObjectIndex);
void RabbitCheckConflicts(ObjectPointer rabbit, ObjectPointer worldObjects, int size);