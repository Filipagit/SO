#include <signal.h>
#include <sys/types.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, const char* argv[]){
    
    if(argc < 3){
        perror("Lack of arguments");
        exit(1);
    }
    
  int total_files = argc - 2;
    const char ** filenames = argv + 2;
    int pids[total_files];
    pid_t pid;

    for(int i = 0; i < total_files; i++){
        if((pid = fork()) == 0){
            if(execlp("grep", "grep", argv[1], filenames[i], NULL) < 0){
                perror("Execlp");
                exit(1);
            }
        }
        pids[i] = pid;
    }

    int flag = 1;
    int status;

    while(flag && (pid = wait(&status)))
        flag = WEXITSTATUS(status);
    
    if(flag){
        perror("Not found");
        exit(1);
    }

    for(int i = 0; i < total_files; i++){
        if(pid != pids[i] && pids[i] > 0){
            kill(pids[i], SIGKILL);
            if(waitpid(pids[i], &status, 0) > 0){
                if(WIFEXITED(status))
                    printf("grep %d finished.\n", pids[i]);
                else
                    printf("grep %d was killed.\n", pids[i]);
            }
        }
    }

    return 0;
}