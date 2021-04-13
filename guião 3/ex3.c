
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

//imprime a lista de argumentos recebidos na linha de comandos 
int main(int argc, char**argv){
    int i;
    for(i=0;i<argc;i++){
        write(1,argv[i],strlen(argv[i]));
        write(1,"\n",1);
    }
    return 0;
}