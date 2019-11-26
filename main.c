/*

    PERGUNTAR AO STOR O FACTO DO X E O Y ESTAREM INVERTIDOS

*/

#include "stdlib.h"
#include "stdio.h"
#include "object.h"
#include "fox.h"

void PrintWorldMatrix(int** world, int r, int c){

    for (int i = 0; i < c+2; i++)
        printf("-");
    printf("\n");
    for (int i = 0; i < r; i++){
        printf("|");
        for (int j = 0; j < c; j++){
            switch (world[i][j])
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

    ObjectPointer worldObjects = NULL;
    for (int i = 0; i < N; i++){
        
        char _name[6];
        int _posX, _posY;
        
        scanf("%s %d %d", _name, &_posX, &_posY);
        
        ObjectPointer _obj = NULL;
        if(strcmp(_name, "RABBIT") == 0)
            _obj = NewObject(_name, _posY, _posX, GEN_PROC_RABBITS,0);
        else
            _obj = NewObject(_name, _posY, _posX, GEN_PROC_FOXES,GEN_FOOD_FOXES);
        
        if (strcmp(_name, "ROCK") == 0)
            world[_posX][_posY] = -1;
        else if(strcmp(_name, "RABBIT") == 0)
            world[_posX][_posY] = 1;
        else
            world[_posX][_posY] = 2;
        
        worldObjects = AppendObject(worldObjects, _obj);
    }

    //testestestestetsetsetsetestsetsetestsetsetsetsetsetsetsetseestsetset
    /* ObjectPointer aux = worldObjects;
    while (aux != NULL)
    {
        if(strcmp(aux->name, "FOX") == 0){
            FoxTurn(aux, world, R, C, 0, worldObjects);
        }
        aux = aux->next;
    } */
    //testestestestetsetsetsetestsetsetestsetsetsetsetsetsetsetseestsetset

    //main loop
    for(int genCount = 0; genCount < N_GEN; genCount++){
        
        //rabbits play 1st
        

        //foxes play 2nd
        //foxes try to eat if there's nothing to eat they'll move

    }
    
    PrintWorldMatrix(world, R, C);
    PrintObjectList(worldObjects);
    return 0;
}