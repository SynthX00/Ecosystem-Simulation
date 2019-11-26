#pragma once
#include "object.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

struct Object{

    char name[6];
    int posX, posY;
    int timeToProc, timeProcLeft, age;
    int timeToStarve, timeStarveLeft;

    struct Object* next;
};

typedef struct Object Object, *ObjectPointer;

ObjectPointer NewObject(char* s, int x, int y, int tProc, int tStarve);
ObjectPointer AppendObject(ObjectPointer head, ObjectPointer obj);
void DeleteObject(ObjectPointer head, char* name, int x, int y);

void PrintObject(ObjectPointer obj);
void PrintObjectList(ObjectPointer head);