#include <stdlib.h>
#include "vetor.h"


//inserir um valor no array
void fill(int* vector, int size, int value){
 int i;
     for(i=0;i<size;i++){
         vector[i]=value;
     }
}

//procurar  um elemento
int find(int* vector, int size, int value){
    int i;
    for(i=0;i<size;i++){
        if(vector[i]==value) return i;
    }
    return -1;
}

