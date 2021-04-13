#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

//imprimir a lista de argumentos de uma lista qualquer de argumentos 
 int main(int argc,char** argv){
     int ret;
     ret=execvp("./ex3",argv);
     return ret;
 }