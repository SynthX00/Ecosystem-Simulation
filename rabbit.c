#include "rabbit.h"

void RabbitTurn(ObjectPointer rabbit, int** world, int worldHeight, int worldWidth, int currentGen, ObjectPointer worldObjects, int* outCurrentObjectIndex){

    //Are there empty cells around?
    int availableCellCount;
    int availableCells[4];
    RabbitCheckCells(rabbit, world,worldHeight, worldWidth, availableCells, &availableCellCount);

    //If cells are available, Move to an empty cell according to the common criteria
    if(availableCellCount > 0){
        //Move
        if(rabbit->age > 0)
            RabbitMove(rabbit, availableCells[((currentGen + rabbit->posX + rabbit->posY)%availableCellCount)], worldObjects, outCurrentObjectIndex);
    }

    //Endturn
    if(rabbit->age > 0){
        rabbit->timeProcLeft--;
        rabbit->timeProcLeft = rabbit->timeProcLeft <= 0 ? 0 : rabbit->timeProcLeft;
    }
    rabbit->age++;
}

void RabbitCheckCells(ObjectPointer rabbit, int** world, int worldHeight, int worldWidth, int* outAvailableCells, int* outCellCount){

    //int outAvailableCells = malloc(4*sizeof(int));
    int index = 0;

    //north
    if(rabbit->posY > 0){
        if(world[rabbit->posX][rabbit->posY-1] == 0){
            outAvailableCells[index] = 0;
            index++;
        }
    }

    //east
    if(rabbit->posX < worldWidth-1){
        if(world[rabbit->posX+1][rabbit->posY] == 0){
            outAvailableCells[index] = 1;
            index++;
        }
    }

    //south
    if(rabbit->posY < worldHeight-1){
        if(world[rabbit->posX][rabbit->posY+1] == 0){
            outAvailableCells[index] = 2;
            index++;
        }
    }

    //west
    if(rabbit->posX > 0){
        if(world[rabbit->posX-1][rabbit->posY] == 0){
            outAvailableCells[index] = 3;
            index++;
        }
    }

    *outCellCount = index++;
}

void RabbitMove(ObjectPointer rabbit, int direction, ObjectPointer worldObjects, int* outCurrentObjectIndex){
    
    //check if will procreate in this move
    if(rabbit->timeProcLeft <= 0){
        #pragma omp critical(proc)
        {
            //create new rabbit
            worldObjects[(*outCurrentObjectIndex)] = NewObject("RABBIT", rabbit->posX, rabbit->posY, rabbit->timeToProc, 0,0);
            (*outCurrentObjectIndex)++;
            rabbit->timeProcLeft = rabbit->timeToProc + 1;
        }
    }

    int prevX, prevY;
    prevX = rabbit->posX; prevY = rabbit->posY;
    
    switch (direction)
    {
    case 0:
        rabbit->posY--;
        break;
    case 1:
        rabbit->posX++;
        break;
    case 2:
        rabbit->posY++;
        break;
    case 3:
        rabbit->posX--;
        break;
    }

    //printf("moved from : %d::%d -> %d::%d\n", prevX, prevY, rabbit->posX, rabbit->posY);
}

///The Rabbit that has to wait longer to procreate will die off
void RabbitCheckConflicts(ObjectPointer rabbit, int myIndex, ObjectPointer worldObjects, int size){
    
    for (int i = 0; i < size; i++){
        
        if(myIndex != i){
            if((worldObjects[i].posX == rabbit->posX) && (worldObjects[i].posY == rabbit->posY) && (worldObjects[i].isDead) == 0){
                if (worldObjects[i].timeProcLeft >= rabbit->timeProcLeft){
                    //printf("rabbit %d::%d is killed\n", worldObjects[i].posX, worldObjects[i].posY);
                    worldObjects[i].isDead = 1;
                }
            }
        }
    }
}