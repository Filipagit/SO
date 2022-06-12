#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <sys/types.h>

#define BUFF_SIZE 1024;
//1 
// $ grep VmPeak /proc/[pid]/memstats | cut -d" " -f4 executa 10x sequencial
int main(int argc,char* argv[]){
    if(argc<2){
        perror("argumentos");
        exit(1);
    }
    int i;
    int count[10];
    for(i=0;i<10;i++){
        pid_t pid;
        if((pid==fork())==0){
            execp(argv[1],argv+1);
            perror("execvp");
            _exit(1);
        }
        int pipe_fd[2][2];
        if(pipe(pipe_fd[0])<0){
            perror("pipe");
            exit(1);
        }
        char * pid_string = malloc(BUFF_SIZE);

        if(fork()==0){
            close(pipe_fd[0][0]);
            dup2(pipe_fd[0][1],STDOUT_FILENO);
            close(pipe_fd[0][1]);
            snprintf(pid_string,BUFF_SIZE,"/proc/%d/memstats",pid);
            execlp("grep","grep","VmPeak",pid_string,NULL);
            perror("Exec");
            _exit(1);
        }
        free(pid_string);
        close(pipe_fd[0][1]);

         if(pipe(pipe_fd[1])<0){
            perror("pipe");
            exit(1);
        }
        if(fork()==0){
            close(pipe_fd[0][1]);
            close(pipe_fd[1][0]);
            dup2(pipe_fd[0][0],STDIN_FILENO);
            close(pipe_fd[0][0]);
            dup2(pipe_fd[1][1],STDOUT_FILENO);
            close(pipe_fd[1][1]);
            execlp("cut","cut","-d","-f4",NULL);
            perror("Exec");
            _exit(1);
        }
        close(pipe_fd[0][0]);
        close(pipe_fd[1][1]);
        //um wait por cada fork
        wait(NULL);
        wait(NULL);
        wait(NULL);

        char* buff=malloc(BUFF_SIZE);
        ssize_t bytes_read=read(pipe_fd[0][0],buff,BUFF_SIZE);
        close(pipe_fd[1][0]);
        if(!bytes_read){
            perror("fail");
            exit(1);
        }
   count[i] = atoi(buffer);

        free(buffer);

    }

    int average, highest = 0, smallest = count[0];

    for (int i = 0; i < N_EXECUTIONS; i++) {

        average += count[i];
        if (count[i] > highest) highest = count[i];
        else if (count[i] < smallest) smallest = count[i];

    }

    char * message = malloc(BUFFER_SIZE);
    snprintf(message, BUFFER_SIZE, "memoria: %d %d %d\n", smallest, average, highest);
    write(STDOUT_FILENO, message, strlen(message));
    free(message);

    return 0;
}

