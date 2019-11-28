#pragma once
#include "rabbit.h"
#include "object.h"

void RabbitTurn(ObjectPointer rabbit, int** world, int worldHeight, int worldWidth, int currentGen, ObjectPointer worldObjects, int* currentObjectIndex);
int* CheckCells(ObjectPointer rabbit, int** world, int worldHeight, int worldWidth, int* outAvailableCells, int* outCellCount);
void Move(ObjectPointer rabbit, int direction, ObjectPointer worldObjects, int* outCurrentObjectIndex);
void CheckConflicts(ObjectPointer rabbit, ObjectPointer worldObjects, int size);