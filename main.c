/*
27-11-19
CC4014 - Computer Science, Parallel Computing (2)
Ecosystem Simulation
Daniel Rangel up201908562
daniel.rangel96@outlook.com
*/

#include "omp.h"
#include "stdlib.h"
#include "stdio.h"
#include "object.h"
#include "rabbit.h"
#include "fox.h"

#define NUMTHREADS 16

void PrintWorldMatrix(int** world, int r, int c){

    for (int i = 0; i < c+2; i++)
        printf("-");
    printf("\n");

    for (int i = 0; i < r; i++){
        printf("|");
        for (int j = 0; j < c; j++){
            switch (world[j][i])
            {
            case -1:
                printf("*");
                break;
            case 1:
                printf("R");
                break;
            case 2:
                printf("F");
                break;
            default:
                printf(" ");
                break;
            }
        }
        printf("|");
        printf("\n");
    }

    for (int i = 0; i < c+2; i++)
        printf("-");
    printf("\n");
}

void PrintWorldDescription(int** world, int r, int c, ObjectPointer worldObjects, int size){
    
    for (int y = 0; y < r; y++){
        for (int x = 0; x < c; x++){
            
            for (int i = 0; i < size; i++){

                if(strcmp(worldObjects[i].name, "EMPTY") == 0){
                    break;
                }else if(worldObjects[i].posX == x && worldObjects[i].posY == y && worldObjects[i].isDead == 0){
                    printf("%s %d %d\n", worldObjects[i].name, y, x);
                }
            }
        }
    }
}

void UpdateWorld(int** world, int r, int c, ObjectPointer worldObjects, int size){

    //Clean World
    #pragma omp parallel for num_threads(NUMTHREADS)
        for (int i = 0; i < r; i++){
            for (int j = 0; j < c; j++){
                world[i][j] = 0;
            }
        }
    
    //Insert Updated Positions
    #pragma omp parallel for num_threads(NUMTHREADS)
        for (int i = 0; i < size; i++){
            if(worldObjects[i].isDead == 0 && strcmp(worldObjects[i].name, "EMPTY") != 0){
                if (strcmp(worldObjects[i].name, "ROCK") == 0)
                    world[worldObjects[i].posX][worldObjects[i].posY] = -1;
                else if(strcmp(worldObjects[i].name, "RABBIT") == 0)
                    world[worldObjects[i].posX][worldObjects[i].posY] = 1;
                else
                    world[worldObjects[i].posX][worldObjects[i].posY] = 2;
            }
        } 
}

ObjectPointer CheckWorldObjectsArray(int worldWidth, int worldHeight, ObjectPointer worldObjects, int size, int *outNewSize){

    //if the array is already the max size (number of cells available) there wont be any need to expand the array
    /* if (size >= (worldWidth * worldHeight))
        return worldObjects; */
    
    //check if more than half of the array has been ocupied
    int count = 0;
    for (int i = 0; i < size; i++){
        if (strcmp(worldObjects[i].name, "EMPTY") != 0)
            count++;
    }

    //printf("COUNT %d-------------size div 2 %d\n", count, (size/2));

    if(count>(size/2)){
        //alloc a new array with further space for possible new objects
        int nSize = /*(size*2) >=  (worldWidth * worldHeight) ? (worldWidth * worldHeight) :  */(size*2);
        ObjectPointer newArray = malloc(nSize * sizeof(Object));
        memcpy(newArray, worldObjects, size * sizeof(Object));
        for(int i = size; i < nSize; i++)
            newArray[i] = InitObject();
        
        free(worldObjects);
        *outNewSize = nSize;
        return newArray;
    }

    return worldObjects;
}

int main(int argc, char *argv[]){

    int GEN_PROC_RABBITS;   //number of gens 'till rabbit can procreate
    int GEN_PROC_FOXES;     //... foxes
    int GEN_FOOD_FOXES;     //number of gens for foxes to die of starvation
    int N_GEN;              //total number of gens for the ecosystem
    int R;                  //world matrix rows
    int C;                  //... columns
    int N;                  //number of initial objects in the ecosystem

    double timestamp;

    scanf("%d %d %d %d %d %d %d", &GEN_PROC_RABBITS, &GEN_PROC_FOXES, &GEN_FOOD_FOXES, &N_GEN, &R, &C, &N);

    //create world matrix
    int** world = malloc(R * sizeof(int*));
    for (int i = 0; i < R; i++)
        world[i] = malloc(C * sizeof(int));

    #pragma omp parallel for num_threads(NUMTHREADS)
        for (int i = 0; i < R; i++){
            for (int j = 0; j < C; j++){        //world:
                                                //-1    -> cell has a rock
                world[i][j] = 0;                //0     -> cell is empty
            }                                   //1     -> cell has a rabbit
        }                                       //2     -> cell has a fox

    //Get world objects
    ObjectPointer worldObjects = malloc((N*2) * sizeof(Object));
    int objectsArraySize = N*2;
    //int currentObjectsCount = N;
    
    #pragma omp parallel for num_threads(NUMTHREADS)
        for (int i = 0; i < objectsArraySize; i++)
            worldObjects[i] = InitObject();

    for (int i = 0; i < N; i++){
        
        char _name[6];
        int _posX, _posY;
        
        scanf("%s %d %d", _name, &_posY, &_posX);
        
        ObjectPointer _obj = NULL;
        if(strcmp(_name, "FOX") == 0)
            worldObjects[i] = NewObject(_name, _posX, _posY, GEN_PROC_FOXES,GEN_FOOD_FOXES,1);
        else
            worldObjects[i] = NewObject(_name, _posX, _posY, GEN_PROC_RABBITS,0,1);
    }

    UpdateWorld(world, R, C, worldObjects, N); // Update world map
    worldObjects = CheckWorldObjectsArray(R, C, worldObjects, objectsArraySize, &objectsArraySize);

    //printf("Generation 0\n");
    //PrintWorldMatrix(world, R, C);
    //PrintObjectList(worldObjects, objectsArraySize,0);
    //printf("\n%d\n", objectsArraySize);

    double time = omp_get_wtime();

    //main loop
    int genCount;
    for(genCount = 0; genCount < N_GEN; genCount++){
        //printf("\nGeneration %d\n", genCount+1);
        //fprintf(stderr, "GEN: %d\n", genCount);
        //rabbits' turn
        
        #pragma omp parallel for num_threads(NUMTHREADS)
        for (int i = 0; i < objectsArraySize; i++){
            if (strcmp(worldObjects[i].name, "RABBIT") == 0 && worldObjects[i].isDead == 0){
                RabbitTurn(&worldObjects[i],world,R,C,genCount, worldObjects, i, objectsArraySize);
            }
        }

        #pragma omp parallel for num_threads(NUMTHREADS)
        for (int i = 0; i < objectsArraySize; i++){
            if (strcmp(worldObjects[i].name, "RABBIT") == 0 && worldObjects[i].isDead == 0 && worldObjects[i].age == 0){
                worldObjects[i].age++;
            }
        }

        for (int i = 0; i < objectsArraySize; i++){
            if (strcmp(worldObjects[i].name, "RABBIT") == 0 && worldObjects[i].isDead == 0){
                RabbitCheckConflicts(&worldObjects[i], i, worldObjects,objectsArraySize);
            }
        }

        UpdateWorld(world, R, C, worldObjects, objectsArraySize); // Update world map
        //PrintWorldMatrix(world, R, C);

        //foxes' turn
        #pragma omp parallel for num_threads(NUMTHREADS)
        for (int i = 0; i < objectsArraySize; i++){
            if (strcmp(worldObjects[i].name, "FOX") == 0 && worldObjects[i].isDead == 0){
                FoxTurn(&worldObjects[i],world,R,C,genCount, worldObjects, i, objectsArraySize);
            }
        }

        #pragma omp parallel for num_threads(NUMTHREADS)
        for (int i = 0; i < objectsArraySize; i++){
            if (strcmp(worldObjects[i].name, "FOX") == 0 && worldObjects[i].isDead == 0 && worldObjects[i].age == 0){
                worldObjects[i].age++;
            }
        }

        for (int i = 0; i < objectsArraySize; i++){
            if (strcmp(worldObjects[i].name, "FOX") == 0 && worldObjects[i].isDead == 0){
                FoxCheckConflicts(&worldObjects[i], i, worldObjects,objectsArraySize);
            }
        }

        UpdateWorld(world, R, C, worldObjects, objectsArraySize); // Update world map

        //PrintWorldMatrix(world, R, C);
        //PrintObjectList(worldObjects, objectsArraySize,0);
        

        //verify if there's any need to expand the object array
        worldObjects = CheckWorldObjectsArray(R, C, worldObjects, objectsArraySize, &objectsArraySize);
        //printf("\n%d   %d\n", objectsArraySize,currentObjectsCount);
    }

    fprintf(stderr, "Total time: %f\n", omp_get_wtime() - time);
    
    //PrintWorldMatrix(world, R, C);
    //PrintObjectList(worldObjects, objectsArraySize,0);

    //paralelize with summation
    int sum = 0;
    for (int i = 0; i < objectsArraySize; i++){

        if(worldObjects[i].isDead == 0)
            sum++;
    }
    
    //PrintObjectList(worldObjects, objectsArraySize,0);
    printf("%d %d %d %d %d %d %d\n", GEN_PROC_RABBITS, GEN_PROC_FOXES, GEN_FOOD_FOXES, (N_GEN - genCount), R, C, sum);
    PrintWorldDescription(world, R, C, worldObjects, objectsArraySize);
    return 0;
}