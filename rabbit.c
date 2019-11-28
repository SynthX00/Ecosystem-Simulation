#include "rabbit.h"

void RabbitTurn(ObjectPointer rabbit, int** world, int worldHeight, int worldWidth, int currentGen, ObjectPointer worldObjects, int* outCurrentObjectIndex){

    //Are there empty cells around?
    int availableCellCount;
    int availableCells[4];
    CheckCells(rabbit, world,worldHeight, worldWidth, availableCells, &availableCellCount);

    //If cells are available, Move to an empty cell according to the common criteria
    if(availableCellCount > 0){
        //Move
        
        printf("Rabbit %d:%d -- ", rabbit->posX, rabbit->posY);
        for (int i = 0; i < availableCellCount; i++)
        {
            printf("%d ", availableCells[i]);
        }
        printf("\nGO DIR -> %d\n\n",availableCells[((currentGen + rabbit->posX + rabbit->posY)%availableCellCount)]);
        printf("\n");

        
        Move(rabbit, availableCells[((currentGen + rabbit->posX + rabbit->posY)%availableCellCount)], worldObjects, outCurrentObjectIndex);
    }

    //Endturn
    rabbit->age++;
    rabbit->timeProcLeft--;
    rabbit->timeProcLeft = rabbit->timeProcLeft <= 0 ? 0 : rabbit->timeProcLeft;
}

int* CheckCells(ObjectPointer rabbit, int** world, int worldHeight, int worldWidth, int* outAvailableCells, int* outCellCount){

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
    return outAvailableCells;
}

void Move(ObjectPointer rabbit, int direction, ObjectPointer worldObjects, int* outCurrentObjectIndex){
    
    //check if will procreate in this move
    if(rabbit->timeProcLeft == 0){
        //create new rabbit
        worldObjects[*outCurrentObjectIndex] = NewObject("RABBIT", rabbit->posX, rabbit->posY, rabbit->timeToProc, 0);
        *outCurrentObjectIndex++;

        rabbit->timeProcLeft = rabbit->timeToProc;
    }

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
}