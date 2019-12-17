#include "object.h"

Object InitObject(){

    Object emptyObject;
    char *s = "EMPTY";
    memcpy(emptyObject.name,s,6*sizeof(char));
    emptyObject.posX = -1;
    emptyObject.posY = -1;
    emptyObject.isDead = -1;
    emptyObject.timeToProc = -1;
    emptyObject.timeProcLeft = -1;
    emptyObject.age = -1;
    emptyObject.timeToStarve = -1;
    emptyObject.timeStarveLeft = -1;

    return emptyObject;
}

Object NewObject(char* s, int x, int y, int tProc, int tStarve, int startingAge){

    Object newObject;

    memcpy(newObject.name,s,7*sizeof(char));
    newObject.posX = x;
    newObject.posY = y;
    newObject.isDead = 0;
    
    if(strcmp(s, "ROCK") != 0){

        newObject.timeToProc = tProc;
        newObject.timeProcLeft = tProc;
        newObject.age = startingAge;

        if (strcmp(s, "FOX") == 0){
            
            newObject.timeToStarve = tStarve;
            newObject.timeStarveLeft = tStarve;
        }
    }

    return newObject;
}

void PrintObject(ObjectPointer obj){

    printf("Name:%s Position:%d::%d\n", obj->name, obj->posX, obj->posY);
    printf("Dead: %s\n", obj->isDead == 0?"No":"Yes");
    if(strcmp(obj->name, "ROCK") != 0){

        printf("ProcLeft:%d Age:%d\n", obj->timeProcLeft, obj->age);
        
        if (strcmp(obj->name, "FOX") == 0){

            printf("FoodLeft:%d\n", obj->timeStarveLeft);
        }
        
    }
    printf("\n");
}

void PrintObjectList(ObjectPointer worldObjects, int size, int all){

    for (int i = 0; i < size; i++){
        if(all == 0){
            if(strcmp(worldObjects[i].name, "EMPTY") != 0 /* && worldObjects[i].isDead == 0 */){
                PrintObject(&worldObjects[i]);
            }
        }
        else
            PrintObject(&worldObjects[i]);
    }
}