#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

//criar um pipe anonimo e de seguida um processo filho
//pai envia uma linha de texto atraves do descritor de escrita
//filho recebe uma linha para o respetivo descritor de leitura

//pipe[0] -> leitura pipe[1]-> escrita
//pai para filho
int main(){
    int pipe_fd[2];
    if(pipe(pipe_fd <0)){
        perror("erro ao criar o pipe");
        exit(1);
    }
//criar o processo filho
int pid=-1;
if((pid=fork())==0){
    //herda os descritores do pipe 
    //fechamos os descritores que nao serao utilizados pelo processo filho
    close(pipe_fd[1]);
    char buf[10];
    int bytes = read(pipe_fd[0],buf,10);
    close(pipe_fd[0]);
    write(STDOUT_FILENO,buf,bytes);
    _exit(0);
}
else{
    char * str="teste";
    write(pipe_fd[1],str,strlen(str));
    close(pipe_fd[1]);
    wait(NULL)
}
return 0;
}