#include "object.h"

ObjectPointer NewObject(char* s, int x, int y, int tProc, int tStarve){

    ObjectPointer nObject = NULL;
    nObject = malloc(sizeof(Object));

    if(nObject != NULL){

        memcpy(nObject->name,s,6*sizeof(char));
        nObject->posX = x;
        nObject->posY = y;

        if(strcmp(s, "ROCK") != 0){

            nObject->timeToProc = tProc;
            nObject->timeProcLeft = tProc;
            nObject->age = 0;

            if (strcmp(s, "FOX") == 0){
                
                nObject->timeToStarve = tStarve;
                nObject->timeStarveLeft = tStarve;
            }
        }

        nObject->next = NULL;
    }

    return nObject;
}

ObjectPointer AppendObject(ObjectPointer head, ObjectPointer obj){

    ObjectPointer aux = head;
    if (aux == NULL){
        return obj;
    }else{

        while (aux->next != NULL){
            
            aux = aux->next;
        }
        aux->next = obj;
    }

    return head;
}

void DeleteObject(ObjectPointer head, char* name, int x, int y){

    ObjectPointer aux = head;
    ObjectPointer prev = NULL;
    
    if(aux == NULL) return;
    if(strcmp(aux->name, name) == 0 && aux->posX == x && aux->posY == y){
        
    }
    while (next != NULL){

        if(strcmp(next->name, name) == 0 && next->posX == x && next->posY == y){
            break;
        }
        aux = next;
        next = aux->next;
    }
    aux->next = next->next;
    free(next);
}

void PrintObject(ObjectPointer obj){

    printf("NAME:%s POS:%d::%d\n", obj->name, obj->posX, obj->posY);

    if(strcmp(obj->name, "ROCK") != 0){

        printf("PROCLEFT:%d AGE:%d\n", obj->timeProcLeft, obj->age);
        
        if (strcmp(obj->name, "FOX") == 0){

            printf("FOODLEFT:%d\n", obj->timeStarveLeft);
        }
        
    }
    printf("\n");
}

void PrintObjectList(ObjectPointer head){

    if(head != NULL){
        ObjectPointer aux = head;
        while (aux != NULL){
            
            PrintObject(aux);
            aux = aux->next;
        }
    }else{
        printf("List is Empty.\n");
    }
}