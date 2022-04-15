#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
/*
Modifique o programa anterior de modo a que, depois de realizar os redireccionamentos, seja criado um
novo processo que realize operações de leitura e escrita. Observe o conteúdo dos ficheiros. Repare que o
processo filho “nasce” com as mesmas associações de descritores de ficheiros do processo pai.
*/
int main(int argc, char* argv[]){
   int imp=open("/etc/passwd",O_RDONLY);
    int outp=open("saida.txt",O_CREAT | O_TRUNC | O_WRONLY,0644);
    int err=open("erros.txt",O_CREAT | O_TRUNC | O_WRONLY,0644);
    //faz a copia
    int i=dup2(imp,0);
    int o=dup2(outp,1);
    int e=dup2(err,2);
   //fecha o original 
    close(imp);
    close(outp);
    close(err);

    char buffer[1024];
    int bytes=0;
    pid_t pid=fork();
    if(pid==0){
        //processo filho
         while((bytes=read(0,&buffer,10))>0){
         write(1,&buffer,bytes);
         write(2,&buffer,bytes);
     }
     else{
         wait(NULL);
     }
     return 0;
    }
}