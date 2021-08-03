#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

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
     /*  ler uma linha a partir do seu standard input e repeti-la nos
     descritores de output e error usando directamente read() e write() */

     char buffer[10];
     int bytes=0;
     while((bytes=read(0,&buffer,10))>0){
         write(1,&buffer,bytes);
         write(2,&buffer,bytes);
     }
     return 0;
}