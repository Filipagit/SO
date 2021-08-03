#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

//executar o comando wc(contar caracteres ) num processo filho
// o processo pai envia ao filho uma seq de linhas de texto introduzidas pelo standard output

int main(){
    int pipe_fd[2];
    if(pipe(pipe_fd)<0){
        perror("erro na criacao do pipe");
        exit(1);
    }
   int pid;
   if((pid=fork())==0){
       //fechamos os descritores que nao serao utilizados pelo processo filho
      close(pipe_fd[1]);
      //dup2->cria uma copia de um descritor
      dup2(pipe_fd[0],1);
      close(pipe_fd[0]);
      execlp("wc","wc",NULL);
   } 
   else{
       close(pipe_fd[0]);
       int bytes;
       char buf[10];
       while((bytes=read(0,buf,10))>0)
           write(pipe_fd[1],buf,bytes);
       close(pipe_fd[1]);
       wait(NULL);
   }
   return 0;
}