#include "fox.h"

void FoxTurn(ObjectPointer fox, int** world, int worldHeigth, int worldWidth, int currentGen, ObjectPointer worldObjects){

    int possibleDir[4]; //pos0 -> north..pos1 -> east..pos2 -> south..pos3 -> west
                        // 0 - empty
                        // 1 - food
                        //-1 - impassable (occupied or end of the world)

    fox->timeStarveLeft--;
    if(fox->timeStarveLeft == 0)
        //FoxDie(fox, worldObjects);

    //check adjacent cells (north, east, south, west)
    //north
    if (fox->posY == 0){
        possibleDir[0] = -1;
    }
    else{
        switch (world[fox->posY-1][fox->posX])
        {
        case -1:    //rock
            possibleDir[0] = -1;
            break;
        case 0:
            possibleDir[0] = 0;
            break;
        case 1:     //rabbit
            possibleDir[0] = 1;
            break;
        case 2:     //fellow fox
            possibleDir[0] = -1;
            break;
        }
    }
    
    //east
    if (fox->posX == worldWidth-1){
        possibleDir[1] = -1;
    }
    else{
        switch (world[fox->posY][fox->posX+1])
        {
        case -1:    //rock
            possibleDir[1] = -1;
            break;
        case 0:     //empty
            possibleDir[1] = 0;
            break;
        case 1:     //rabbit
            possibleDir[1] = 1;
            break;
        case 2:     //fellow fox
            possibleDir[1] = -1;
            break;
        }
    }

    //south
    if (fox->posY == worldHeigth-1){
        possibleDir[2] = -1;
    }
    else{
        switch (world[fox->posY+1][fox->posX])
        {
        case -1:    //rock
            possibleDir[2] = -1;
            break;
        case 0:     //empty
            possibleDir[2] = 0;
            //printf("%d::%d    %d\n",fox->posX ,fox->posY+1 ,world[fox->posX][fox->posY+1]);
            break;
        case 1:     //rabbit
            possibleDir[2] = 1;
            break;
        case 2:     //fellow fox
            possibleDir[2] = -1;
            break;
        }
    }

    //west
    if (fox->posX == 0){
        possibleDir[3] = -1;
    }
    else{
        switch (world[fox->posY][fox->posX-1])
        {
        case -1:    //rock
            possibleDir[3] = -1;
            break;
        case 0:     //empty
            possibleDir[3] = 0;
            break;
        case 1:     //rabbit
            possibleDir[3] = 1;
            break;
        case 2:     //fellow fox
            possibleDir[3] = -1;
            break;
        }
    }
    
    //check if there are multiple empty cells or with rabbits
    int countR = 0;
    int countE = 0;
    for (int i = 0; i < 4; i++){
        
        if(possibleDir[i] == 1)
            countR++;
        if(possibleDir[i] == 0)
            countE++;
    }
    
    int* positions;
    if(countR >1){  //more than 1 rabbit available

        //use criteria for selection adjacent cell
        positions = malloc(countR * sizeof(int));
        int _index = 0;

        for (int i = 0; i < 4; i++){
            if(possibleDir[i] == 1){
                positions[_index];
                _index++;
            }
        }
        
        int dir = (currentGen + fox->posX + fox->posY) % (countR-1);
        MoveFox(fox, worldObjects, dir, 1); //obj, world, direction, eat (yes no)

    }
    else if(countR == 1){

        for (int i = 0; i < 4; i++){
            
            if (possibleDir[i] == 1){
                
                MoveFox(fox, worldObjects, possibleDir[i], 1);
                break;
            }
        }
    }
    else if(countE >1){    //more than 1 empty space to choose from

        //use criteria for selection adjacent cell
        positions = malloc(countE * sizeof(int));
        int _index = 0;

        for (int i = 0; i < 4; i++){
            if(possibleDir[i] == 0){
                positions[_index];
                _index++;
            }
        }
        
        int dir = (currentGen + fox->posX + fox->posY) % (countE-1);
        MoveFox(fox, worldObjects, dir, 0); //obj, world, direction, eat (yes no)
    }
    else if(countE ==1){

        for (int i = 0; i < 4; i++){
            
            if (possibleDir[i] == 0){
                
                MoveFox(fox, worldObjects, possibleDir[i], 0);
                break;
            }
        }
    }

    fox->age++;    
}

void MoveFox(ObjectPointer fox, ObjectPointer worldObjects, int direction, int eat){

    fox->timeProcLeft--;
    if (fox->timeProcLeft == 0){

        fox->timeProcLeft = fox->timeToProc;
        //create new fox
        ObjectPointer newFox = NewObject("FOX", fox->posX, fox->posY, fox->timeToProc, fox->timeToStarve);
        worldObjects = AppendObject(worldObjects, newFox);
    }

    //move
    //direction 0-north 1-east 2-south 3-west
    if (eat == 1){
        
    }
    
}