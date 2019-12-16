#include "fox.h"

void FoxTurn(ObjectPointer fox, int** world, int worldHeight, int worldWidth, int currentGen, ObjectPointer worldObjects, int myIndex, int size){

    if (fox->age > 0){
        //Are any rabbits around me?
        int availableCellCount;
        int availableCells[4];
        FoxCheckCells(fox, 1, world, worldHeight, worldWidth, availableCells, &availableCellCount);

        //If so move and eat one of them
        if(availableCellCount > 0){
            //move to hunt
            if(fox->age > 0)
                FoxMove(fox, 1, availableCells[((currentGen + fox->posX + fox->posY)%availableCellCount)], worldObjects, myIndex, size);
        }//Else try to move to an empty space
        else{

            if(fox->age > 0){
                fox->timeStarveLeft--;
                fox->timeStarveLeft = fox->timeStarveLeft <= 0 ? 0 : fox->timeStarveLeft;
            }

            //check starvation
            if(fox->timeStarveLeft <= 0){
                    fox->isDead = 1;
                    return;
            }
            
            FoxCheckCells(fox, 0, world, worldHeight, worldWidth, availableCells, &availableCellCount);
            if (availableCellCount > 0){
                if(fox->age > 0)
                    FoxMove(fox, 0, availableCells[((currentGen + fox->posX + fox->posY)%availableCellCount)], worldObjects, myIndex, size);
            }
        }

        //Endturn
    
        fox->timeProcLeft--;
        fox->timeProcLeft = fox->timeProcLeft <= 0 ? 0 : fox->timeProcLeft;
        fox->age++;
    }

}

void FoxCheckCells(ObjectPointer fox, int hunt, int** world, int worldHeight, int worldWidth, int* outAvailableCells, int* outCellCount){
    
    int index = 0;

    //north
    if(fox->posY > 0){
        if(world[fox->posX][fox->posY-1] == hunt){
            outAvailableCells[index] = 0;
            index++;
        }
    }

    //east
    if(fox->posX < worldWidth-1){
        if(world[fox->posX+1][fox->posY] == hunt){
            outAvailableCells[index] = 1;
            index++;
        }
    }

    //south
    if(fox->posY < worldHeight-1){
        if(world[fox->posX][fox->posY+1] == hunt){
            outAvailableCells[index] = 2;
            index++;
        }
    }

    //west
    if(fox->posX > 0){
        if(world[fox->posX-1][fox->posY] == hunt){
            outAvailableCells[index] = 3;
            index++;
        }
    }

    *outCellCount = index++;
}

void FoxMove(ObjectPointer fox, int hunt, int direction, ObjectPointer worldObjects, int myIndex, int size){

    //check if will procreate this move
    if(fox->timeProcLeft <= 0){
        #pragma omp critical
        {
            for (int i = myIndex; i < size; i++)
            {
                if(strcmp(worldObjects[i].name, "EMPTY") == 0){
                    //create new fox
                    
                    worldObjects[i] = NewObject("FOX", fox->posX, fox->posY, fox->timeToProc, fox->timeToStarve, 0);
                    fox->timeProcLeft = fox->timeToProc + 1;
                    
                    break;
                }
            }
        }
    }

    switch (direction)
    {
    case 0:
        fox->posY--;
        break;
    case 1:
        fox->posX++;
        break;
    case 2:
        fox->posY++;
        break;
    case 3:
        fox->posX--;
        break;
    }

    if (hunt == 1){
        for (int i = 0; i < size; i++){
            if(strcmp(worldObjects[i].name, "EMPTY") == 0){
                break;
            }else if(worldObjects[i].posX == fox->posX && worldObjects[i].posY == fox->posY && worldObjects[i].isDead == 0 && strcmp(worldObjects[i].name, "RABBIT") == 0){
                worldObjects[i].isDead = 1;
                fox->timeStarveLeft = fox->timeToStarve;
            }
        }
    }
}

void FoxCheckConflicts(ObjectPointer fox, int myIndex, ObjectPointer worldObjects, int size){
    
    for (int i = 0; i < size; i++){
        
        if(myIndex != i){
            if((worldObjects[i].posX == fox->posX) && (worldObjects[i].posY == fox->posY) && worldObjects[i].isDead == 0){
                if (worldObjects[i].timeProcLeft > fox->timeProcLeft){
                    worldObjects[i].isDead = 1;
                }else if(worldObjects[i].timeProcLeft == fox->timeProcLeft && worldObjects[i].timeStarveLeft <= fox->timeStarveLeft){
                    worldObjects[i].isDead = 1;
                }
            }
        }
    }
}