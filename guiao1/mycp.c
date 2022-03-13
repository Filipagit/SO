#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h> 
#include <fcntl.h>
#include <errno.h> 

//1 cp: recebe um ficheiro de origem e outro de destino e copia o de origem para o destino
#define MAX_BUF 1024*1024
int main(int argc, char *argv[]){
 printf("argv[0]: %s\n",argv[0]);
 printf("argv[1]: %s\n",argv[1]);//caminho para o ficheiro origem
 printf("argv[2]: %s\n",argv[2]);//caminho para o ficheiro destino

 //memoria estatica 
 char buffer[MAX_BUF];
 //memoria dinamica
 //char * buffer =malloc(MAX_BUF);
 int fd_origem,fd_destino;
   if((fd_origem = open(argv[1], O_RDONLY))== -1){
     printf("Msg: %s,Nr:%d\n",strerror(errno),errno); // ajudar a perceber o erro 
     //alternativa
     perror("erro no open origem"); 
     return -1;
     //testar : ./mycp shshhs => coisa que nao existe 
   } 
   if((fd_destino=open(argv[2], O_WRONLY | O_CREAT | O_TRUNC ,0640))==-1){
       perror("erro no open destino");
       return -1;
   }
   int bytes_read;
   while((bytes_read = read(fd_origem,buffer,MAX_BUF))>0){
       write(fd_destino,buffer,bytes_read);
   }
   //free(buffer);
  close(fd_origem);
  close(fd_destino);

  return 0;

}
//fazer uma makefile 
//testar:make  -> clear  -> mycp ficheiros.pdf teste.pdf -> ls 
//para a 2 parte : clear -> time ./mycp ficheiros.pdf teste1.pdf

// se o tamanho do buffer for pequeno demora mais tempo pq estamos a ir ao disco pegar num caracter trazer em  memoria e pegar nesse caracter e trazer pra disco
//estamos a desaproveitar a largura de banda , para 1 gasta o mm tempo que na memoria dinamica a ir buscar mais
