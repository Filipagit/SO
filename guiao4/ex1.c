#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

int main(int argc,char* argv[]){
    //abre os ficheiros
   int passfd=open("/etc/passwd",O_RDONLY);
   int saifd=open("saida.txt",O_CREAT|O_TRUNC|O_WRONLY,0666);
   int errfd=open("erros.txt",O_CREAT|O_TRUNC|O_WRONLY,0666);

   //faz a copia
   int r1=dup2(passfd,0);
   int r2=dup2(saifd,1);
   int r3=dup2(errfd,2);
    
    //fecha os originais
   close(passfd);
   close(saifd);
   close(errfd);
   char buffer[10];
   int bytes_read=0;
   while((bytes_read=read(0,&buffer,10))>0){
       write(1,&buffer,bytes_read);
       write(2,&buffer,bytes_read);
   }
   return 0;
}