#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

//Program 1
//criacao de um pipe  c nome
int createFifo(){
    mkfifo("fifo",0644);
    return 0;
}

//Program 2 
// repete para o pipe todas as linhas de texto lidas a partir do standard imput
int stdinToFifo(){
    int buffer[1024];
    int bytes_read=0;
    int fd= open("fifo", O_WRONLY | O_CREAT | O_RDONLY,0644);
    while((bytes_read=read(0,buffer,1024))>0){
        write(fd,buffer,bytes_read);
    }
    close(fd);
    return 0;
}

//Program 3
//repete para o standard output todas as linhas lidas a partir do pipe

int fifoToStdout(){
    int buffer[1024];
    int bytes_read=0;
    int fd=open("fifo",O_RDONLY);
    while((bytes_read=read(fd,buffer,1024)>0)){
        write(1,buffer,bytes_read);
    }
    close(fd);
    return 0;
}