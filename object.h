#pragma once
#include "object.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

struct Object{

    char name[6];
    int isDead;
    int posX, posY;
    int timeToProc, timeProcLeft, age;
    int timeToStarve, timeStarveLeft;
};

typedef struct Object Object, *ObjectPointer;

ObjectPointer NewObject(char* s, int x, int y, int tProc, int tStarve);

void PrintObject(ObjectPointer obj);
void PrintObjectList(ObjectPointer head);