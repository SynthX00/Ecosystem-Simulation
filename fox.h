#pragma once
#include "fox.h"
#include "object.h"

void FoxTurn(ObjectPointer fox, int** world, int worldHeight, int worldWidth, int currentGen, ObjectPointer worldObjects);
void MoveFox(ObjectPointer fox, ObjectPointer worldObjects, int direction, int eat);
