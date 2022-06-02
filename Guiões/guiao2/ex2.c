#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main(){
    pid_t pid=fork();
    if(pid==0){
        //Código do filho
        printf("[FILHO] o meu pid é %d\n",getpid());
        printf("[FILHO] o pid  do meu pai é %d\n",getppid());
    }
    else{
        //Código do pai
        printf("[PAI] o meu pid é %d\n",getpid());
        printf("[PAI] o  pid do meu pai  é %d\n",getppid());
        printf("[PAI] o  pid do meu filho é %d\n",getpid());
        //sleep(30); fica zombie
    }
}