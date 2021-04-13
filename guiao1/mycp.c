#include <fcntl.h>

// copiar arquivos e diretorios 

int main(int argc,char* argv[]){
    int buffer_size=1024;
    int fd_read ,fd_write;
    if((fd_read=open(argv[1],O_RDONLY)==-1){
        perror("open");//diz o erro que esta a acontecer
        return -1;
    }
    if(fd_write=open(argv[2], O_CREAT | O_TRUNC | O_WRONLY,0640)==-1){
        perror("open");
        return -1;
    }
    ssize_t read_bytes;
    ssize_t writen_bytes=0;
     char *buffer = (char *)malloc(sizeof(char) * buffer_size);
       while((read_bytes=read(fd_read,buffer,buffer_size))>0){
           writen_bytes+=write(fd_write,buffer,read_bytes);
       }
       close(fd_read);
       close(fd_write);
       free(buffer);
       printf("copied bytes: %ld bytes\n",writen_bytes);
    return  writen_bytes;  
}
