/*
27-11-19
CC4014 - Computer Science, Parallel Computing (2)
Ecosystem Simulation
Daniel Rangel up201908562
daniel.rangel96@outlook.com
*/

#include "stdlib.h"
#include "stdio.h"
#include "object.h"
#include "rabbit.h"
#include "fox.h"

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

void UpdateWorld(int** world, int r, int c, ObjectPointer worldObjects, int size){

    //Clean World
    for (int i = 0; i < r; i++){
        for (int j = 0; j < c; j++){
            world[i][j] = 0;
        }
    }
    
    //Insert Updated Positions
    for (int i = 0; i < size; i++){
        if(worldObjects[i].isDead != 1){
            if (strcmp(worldObjects[i].name, "ROCK") == 0)
                world[worldObjects[i].posX][worldObjects[i].posY] = -1;
            else if(strcmp(worldObjects[i].name, "RABBIT") == 0)
                world[worldObjects[i].posX][worldObjects[i].posY] = 1;
            else
                world[worldObjects[i].posX][worldObjects[i].posY] = 2;
        }
    } 
}

int main(){

    int GEN_PROC_RABBITS;   //number of gens 'till rabbit can procreate
    int GEN_PROC_FOXES;     //... foxes
    int GEN_FOOD_FOXES;     //number of gens for foxes to die of starvation
    int N_GEN;              //total number of gens for the ecosystem
    int R;                  //world matrix rows
    int C;                  //... columns
    int N;                  //number of initial objects in the ecosystem

    scanf("%d %d %d %d %d %d %d", &GEN_PROC_RABBITS, &GEN_PROC_FOXES, &GEN_FOOD_FOXES, &N_GEN, &R, &C, &N);

    //create world matrix
    int** world = malloc(R * sizeof(int*));
    for (int i = 0; i < R; i++){
        
        world[i] = malloc(C * sizeof(int));
    }
    
    for (int i = 0; i < R; i++){

        for (int j = 0; j < C; j++){        //world:
                                            //-1    -> cell has a rock
            world[i][j] = 0;                //0     -> cell is empty
        }                                   //1     -> cell has a rabbit
    }                                       //2     -> cell has a fox

    ObjectPointer worldObjects = malloc(N * sizeof(Object));
    for (int i = 0; i < N; i++){
        
        char _name[6];
        int _posX, _posY;
        
        scanf("%s %d %d", _name, &_posY, &_posX);
        
        ObjectPointer _obj = NULL;
        if(strcmp(_name, "FOX") == 0)
            worldObjects[i] = NewObject(_name, _posX, _posY, GEN_PROC_FOXES,GEN_FOOD_FOXES);
        else
            worldObjects[i] = NewObject(_name, _posX, _posY, GEN_PROC_RABBITS,0);
        
        //PrintObject(&worldObjects[i]);
    }

    UpdateWorld(world, R, C, worldObjects, N); // Update world map

    for (int i = 0; i < N; i++)
    {
        if (strcmp(worldObjects[i].name, "RABBIT") == 0){
            
            RabbitTurn(&worldObjects[i],world,R,C,N_GEN);
        }
    }
    

    //main loop
    for(int genCount = 0; genCount < N_GEN; genCount++){
        
        //rabbits play 1st
        

        //foxes play 2nd
        //foxes try to eat if there's nothing to eat they'll move

    }
    
    PrintWorldMatrix(world, R, C);
    //PrintObjectList(worldObjects, N);
    return 0;
}