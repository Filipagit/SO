#include <unistd.h> 
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//3 linha fica guardada em line agr o criterio de paragem é \n size=tamanho de lines

ssize_t readln(int fd, char *line, size_t size){
   ssize_t i=0;
       while(i<size && read(fd,&line[i],1)>0 ){
       if(line[i++]=='\n') break;
   } 
   return i;
}


//ex 4 
//ler um caracter
int readch_ex4(int fd,char *buf){
    return read(fd,buf,1);
}

ssize_t readln_ex4(int fd, char *line, size_t size){
    ssize_t i=0;
       while(i<size && readch_ex4(fd,&line[i])>0 ){
       if(line[i++]=='\n') break;
   } 
   return i;
}

//4  alternativa 
// o buf vai guardar um dado nr de bytes assim n é preciso estar constantemente ir a memoria
  #define BUFFER_SIZE 10
  char buffer[BUFFER_SIZE]; //só é acessivel nesta função 
int next_position=0;
int last_read_bytes=0;// nr max de bytes que tem disponivel para entregar ao readln

  int readch_alt(int fd,char *buf){
      //se nao tiver mais dados disponiveis 
      if(next_position == last_read_bytes){
        //ler do descritor de ficheiro(disco)
        int bytes=0;
        if((bytes=read(fd,buffer,BUFFER_SIZE))<1){
            return 1;
        }
       next_position=0;
      last_read_bytes=bytes;
      }
      //escrever um caracter em buf e atualizar o estado do buffer(next_position++)
     *buf=buffer[next_position];
     next_position++;
      return 0;
  }

ssize_t readln_alt(int fd, char *line, size_t size){
    int i=0;
    int read_bytes=0;
       while(i<size && readch_alt(fd,&line[i])==0 ){
           read_bytes++;
       if(line[i++]=='\n') break;
   } 
   return i;
}

//ex5 
void myNL(int fd,char* buf){
    int read_bytes;
    int i=0;
    while((read_bytes=readln_alt(fd,buf,BUFFER_SIZE))>0){
        i++;
        char* numC= malloc(sizeof(char)*12);
        sprintf(numC,"%d  ",i);;
        write(1,strcat(numC,buf),read_bytes+12);
        free(numC);
    }
}




