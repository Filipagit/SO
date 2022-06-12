Implemente um programa que corre em rondas sequenciais. Em cada ronda deverão ser executadas 100 instâncias concorrentes do comando cmd (sem argumentos). Cada ronda deve terminar no máximo após 20 segundos, devendo eventuais
instâncias do comando ainda a executar serem forçadas a terminar. Ao fim de cada ronda, o programa deverá escrever o
número de vezes que o comando executou completamente nessa ronda (sem ser interrompido). Ao ser interrompido com
SIGINT, o programa deverá escrever o número de rondas finalizadas, abortar a ronda em curso e terminar.

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <sys/types.h>

int normal_exit=0;
int pids[100];

void timeout_handler(){
    int i;
    for(i=0;i<100;i++){
       if(pids[i]>0) kill(pids[i],SIGKILL);
    }
    printf("Normal exit: %d\n",normal_exit);
    exit(0);
}

void sigint_handler(int signum){
    printf("Normal exit:%d\n",normal_exit);
    exit(1);
}

int main() {

    if (signal(SIGALRM, timeout_handler) == SIG_ERR) {

        perror("signal");
        exit(1);

    }

    if (signal(SIGINT, sigint_handler) == SIG_ERR) {

        perror("signal");
        exit(1);

    }

    for (int i = 0; i < 100; i++) 
        if ((pids[i] = fork()) == 0) {

            execlp("grep", "grep", "\"COCKPIT\"", "beeMovieScript.txt", NULL);
            perror("execlp");
            _exit(1);

        }

    alarm(TIME_LIMIT);
    
    int status;
    for (int i = 0; i < 100; i++) {

        wait(&status);
        if (WEXITSTATUS(status) == 0 || WEXITSTATUS(status) == 1) 
            normal_exit++;

    }

    printf("Normal exits: %d\n", normal_exit);

    return 0;

}