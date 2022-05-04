#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

//wc - print newline, word, and byte counts for each file

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
   execlp("wc","wc",NULL);
   return 0;
}
/*
com a utilização do exec no ficheiro de saida aparece o resultado da execucao do comando wc.
Não temos erros logo o ficheiro erros.txt encontra se vazio.
Agora nao escrevemos nos ficheiros os standard input ,output e error.
*/
