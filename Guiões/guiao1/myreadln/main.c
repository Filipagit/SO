#include <unistd.h> 
#include <fcntl.h>
#include "readln.h"
#include <stdio.h>

#define MAX_BUF 10
int main(int argc,char const * argv[]){
     int fd=open("linhas.txt",O_RDONLY);
    char buf[MAX_BUF];
    //ex 1 a 4 
    //int bytes_read=0;
    //while((bytes_read=readln(fd,buf,MAX_BUF))>0){
     //write(1,buf,bytes_read);
     //ex 5 
     myNL(fd,buf);  
    //}
    close(fd);
    return 0;
}