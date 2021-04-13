#include<fcntl.h>
#define  buffer_size 1024;

//le e escreve  conseguiii
int main(int argc, char *argv[]){
    char buffer[buffer_size];
int bytes_read;
while((bytes_read=read(0,buffer,buffer_size))>0){
    write(1,buffer,bytes_read);
}
return 0;
}