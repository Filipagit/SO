#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

//modificar o ex1 de modo que a leitura do pipe seja realizada enquanto nao for detetada nenhuma situacao de end of file
//ie quando nenhum processo(filho e pai) tem o descritor de escrita aberto

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
    int bytes =0;
     while(read(pipe_fd[0],buf,10)>0){
         write(1,buf,bytes);
     }
    _exit(0);
}
else{
    close(pipe_fd[0]);
   
   for(size_t i=0; i< 3; i++) write(pipe_fd[1],str,strlen(str)+1);
    close(pipe_fd[1]);
    wait(NULL)
}
return 0;
}