#include <unistd.h> 
#include <fcntl.h>
#include <stdio.h>
//2 cat : td o que lê ele replica 
#define MAX_BUFFER 1024

int main(int argc, char *argv[]){
   char buffer[MAX_BUFFER];
   int bytes_read;
   while((bytes_read= read(0,buffer,MAX_BUFFER))>0){
       write(1,buffer,bytes_read);
   }
   printf("Terminei.\n");
   return 0;
}

//testar: ./mycat  jddsfng   para sair  ctrl d 
// se fizer ctrl c nao imprime o terminei  termina de facto o programa morreu nem chega a imprimir a ult linha 

//fazer 3 4 e  5 

//3 linha fica guardada em line agr o criterio de paragem é \n 
//4 pega num ficheiro de texto e numera as linhas para cada linha lida imprime o nr da linha e a linha que se leu 
//5 otmimizar a 3 para ler mais caracteres de cada vez



 