#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

//cliente 
int main(int argc, char * argv[]){
    if(argc>1){
        int fd_fifo=open("fifo",O_WRONLY,0666);
        write(fd_fifo,argv[1],(strlen(argv[1]* sizeof(char))));
        close(fd_fifo);
    }
    return 0;
}
//servidor
int servidor(){
    int fd_log=open("log.txt",O_CREAT | O_WRONLY,0644);
     int fd_fifo;
     int bytes_read,bytes_written;
     char *buffer=malloc(sizeof(char)* 1024);
     while(fd_fifo=open("fifo",O_RDONLY)>0){
         while((bytes_read=read(fd_fifo,buffer,1024))>0){
         if(bytes_written=write(fd_log,buffer,bytes_read)<=0){
             perror("escrita");
             exit(1);
         }
     }
     close(fd_fifo);
     } 
     close(fd_log);
     close(buffer);
return 0;
}
