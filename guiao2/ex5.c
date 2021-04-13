#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>


//programa que crie uma descendência em profundidade de dez processos, ou seja, o
//processo cria um filho, este filho cria outro, e assim por diante até ao décimo nı́vel de descendência.
//Cada processo deverá imprimir o seu PID e o PID do seu pai.

int main(){
    int i;
    pid_t pid;
    int status;
    for(i=1;i<=10;i++){
        if((pid=fork())==0){
            //processo filho 
            printf("[%d]-SON #%d;my father is %d\n",i,getpid(),getppid());
        }
        else{
            //processo pai 
            pid_t terminated_pid=wait(&status);
            printf("[%d]-FATHER #%d; my son is %d\n",i,getpid(),terminated_pid);
            _exit(0);
        }
    }
    _exit(0);
    return 0;
}