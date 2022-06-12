#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <sys/types.h>

//1 
#define BUFFER_SIZE 1024
#define ENTRY_SIZE 50

char ** parse_entry (char ** position) {
    return NULL;
}

int servidor() {

    int fd_pipe, fd_write;
    fd_pipe = open("fifo", O_RDONLY);
    if (fd_pipe < 0) {
        perror("open");
        exit(1);

    }

    ssize_t bytes_read;
    char * buffer = malloc(sizeof(char) * BUFFER_SIZE);
    char ** parsed;
    char * write_string = malloc(sizeof(char) * ENTRY_SIZE);

    while((bytes_read = read(fd_pipe, buffer, BUFFER_SIZE)) > 0) {

        while((parsed = parse_entry(&buffer))) {

            snprintf(write_string, ENTRY_SIZE, "%s %s %s\n", parsed[0], parsed[1], parsed[2]);
            fd_write = open(parsed[2], O_CREAT | O_APPEND | O_WRONLY, 0644);
            if (fd_write < 0) {

                perror("open");
                exit(1);

            }
            write(fd_write, buffer, BUFFER_SIZE);
            close(fd_write);

        }

    }

    free(buffer);
    free(write_string);

    return 0;

}

//2
int vacinados(char* regiao, int idade){
    char idade_s[6];
    sprintf(idade_s,"%d",idade)
    int pipes[2];
    if(pipe(pipes)<0){
        perror("erro na criação do pipe");
        exit(1);
    }
    if(fork()==0){
        close(pipes[0]);
        dup2(pipes[1],STDOUT_FILENO);
        close(pipes[1]);
        execlp("grep","grep",idade_s,regiao,NULL);
    }
    close(pipes[1]);
    int pipes2[2];
    if(pipe(pipes2)<0){
        perror("erro na criação do pipe");
    }
    if(fork()==0){
        close(pipes2[0]);
        dup2(pipes[0],STDIN_FILENO);
        close(pipes[0]);
        dup2(pipes2[1],STDOUT_FILENO);
        close(pipes2[1]);
        execlp("wc","wc","-l",NULL);
    }
    close(pipes[0]);
    close(pipes2[1]);
    int bytes_read=0;
    char buff[1024];
    bytes_read=read(pipes2[0],buff,1024);
    close(pipes2[0]);
    buf[bytes_read]=0;
    return atoi(buff);
}

//3
bool vacinado(char* cidadao) {
    int pid[9];
    int i;
    for(i=0;i<9;i++){
        if((pid[i]=fork())==0){
            char ficheiro[9];
            sprintf(ficheiro, "regiao_%d", i);
            execlp("grep", "grep", cidadao, ficheiro, NULL);
        }
    }
    int status;
    bool b = false;
    while (wait(&status) != -1) {
        if (WIFEXITED(status)) {
            if (WEXITSTATUS(status) == 0) {
                b = true;
                for (int i = 0; i < 9; i++) {
                    kill(pid[i], SIGKILL);
                }
            }
        }
    }
    return b;
}
   