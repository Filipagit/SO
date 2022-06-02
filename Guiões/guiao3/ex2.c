#include<unistd.h>
#include<stdio.h>
#include<sys/wait.h>

int main(int argc,char *argv[]){

    if(fork()==0){
        //código do processo filho
        execl("/bin/ls","ls","-l",NULL);
        _exit(0);
    }
    int status;
    wait(&status); //aguarda que o ls termine
    printf("Exec done");
    return 0;
}