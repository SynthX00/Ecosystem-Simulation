#pragma once
#include "object.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

struct Object{

    char name[6];
    int index;
    int isDead;
    int posX, posY;
    int timeToProc, timeProcLeft, age;
    int timeToStarve, timeStarveLeft;
};

typedef struct Object Object, *ObjectPointer;

Object InitObject();
Object NewObject(int index, char* s, int x, int y, int tProc, int tStarve, int startingAge);

void PrintObject(ObjectPointer obj);
void PrintObjectList(ObjectPointer worldObjects, int size, int all);