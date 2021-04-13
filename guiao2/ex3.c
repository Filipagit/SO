//programa que crie dez processos filhos que deverão executar sequencialmente. Para este
//efeito, os filhos podem imprimir o seu PID e o do seu pai, e finalmente, terminarem a sua execução com
//um valor de saı́da igual ao seu número de ordem (e.g.: primeiro filho criado termina com o valor 1). O
//pai deverá imprimir o código de saı́da de cada um dos seus filhos.
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
//quaseee
int main(){
    pid_t pid;
    int status;
    int i;
    for(i=1;i<=10;i++){
     if((pid=fork())==0){
         //processo filho 
         printf("my pid%d;my father pid %d\n",getpid(),getppid());
         _exit(i);
     }
     else{
         //processo pai 
         pid_t terminated_pid=wait(&status);
         if(WIFEXITED(status)){// se correu tudo bem 
         printf("FATHER: son with pid %d terminated with status %d\n",terminated_pid,WEXITSTATUS(status));

         }
          else{
              printf("ocorreu um erro\n");
          }
     }
    }
    return 0;
}
