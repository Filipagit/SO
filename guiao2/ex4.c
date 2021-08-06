#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

//programa que crie dez processos filhos que deverão executar em concorrência. O pai
//deverá esperar pelo fim da execução de todos os seus filhos, imprimindo os respectivos códigos de saı́da.

int main(){
    int i;
    pid_t pid;
    int status;
    for(i=1;i<=10;i++){
        if((pid=fork())==0){
            //processo filho
            printf("my pid%d;my father pid %d\n",getpid(),getppid());
            _exit(i);
        }
    }
    for(i=1;i<=10;i++){
        printf("novo ciclo: %d\n",i);
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

 
