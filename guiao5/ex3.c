#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

int main(){
     int pipe_fd[2];
    if(pipe(pipe_fd)<0){
        perror("erro na criacao do pipe");
        exit(1);
    }
    int pid;
    if((pid=fork())==0){
        //processo filho
        //fechamos os descritores que nao serao utilizados
        close(pipe_fd[1]);
        //cria a copia do descritor
        dup2(pipe_fd[0],1);
        close(pipe_fd[0]);
        execlp("wc","wc",NULL);
    }
    else{
        //processo pai
        close(pipe_fd[0]);
        int bytes_read;
        char buf[10];
         while((bytes_read=read(0,buf,10))>0)
             write(pipe_fd[1],buf,bytes_read);
             close(pipe_fd[1]);
             wait(NULL);

    }
    return 0;
}