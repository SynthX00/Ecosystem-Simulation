#pragma once
#include "fox.h"
#include "object.h"

void FoxTurn(ObjectPointer fox, int** world, int worldHeight, int worldWidth, int currentGen, ObjectPointer worldObjects, int* currentObjectIndex);
void FoxCheckCells(ObjectPointer fox, int hunt, int** world, int worldHeight, int worldWidth, int* outAvailableCells, int* outCellCount);
void FoxMove(ObjectPointer fox, int hunt, int direction, ObjectPointer worldObjects, int* outCurrentObjectIndex);
void FoxCheckConflicts(ObjectPointer fox, int myIndex, ObjectPointer worldObjects, int size);
