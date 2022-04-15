#include<unistd.h>
#include<stdio.h>

// ls-l :lista os documentos da diretoria

int main(int argc,char *argv[]){
    execl("/bin/ls","ls","-l",NULL);
    // a partir do momento que o execl foi bem sucedido nada mais neste programea 
    // é executado logo o print n vai aparecer.
    printf("Exec done");
    return 0;// se der erro
}