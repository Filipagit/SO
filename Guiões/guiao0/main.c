#include <stdio.h>
#include "vetor.h"
#include "vetor.c"

#define SIZE 10 

int main(int argc, char const *argv[]){
    int i;
int v[SIZE];
fill(v,SIZE,12);
for(i=0;i<SIZE;i++)
printf("%d ",v[i]);
printf("\n");
int s[SIZE]={1,2,3,4,5,6,7,8,9,10};
int indice=find(s,SIZE,10);
if(indice==-1) printf("valor nao encontrado %d",10);
else printf("%d\n",indice);
int liminf=3;
int limsup=5;
indice=find(s+liminf,limsup-liminf+1,10);
if(indice==-1) printf("valor nao encontrado %d",10);
else printf("%d\n",indice);
return 0;
}