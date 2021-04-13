#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

//lista o conteudo do diretorio 
int main(int argc, char**argv){
    int ret;
    ret=execlp("ls","-l",NULL);
    return 0;// se der erro
}