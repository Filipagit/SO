#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

//repete para este pipe todas as linhas de texto lidas a partir do seu standard input.
int main(int argc,char *argv[]){
    int buff[1024];
    int bytes_read=0;
    int fd=open("fifo",O_WRONLY| O_CREAT | O_RDONLY,0644);
      while((bytes_read=read(fd,buff,1024))>0){
          write(STDOUT_FILENO,buff,bytes_read);
      } 
      close(fd);
      return 0;
}