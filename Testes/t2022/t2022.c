#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <sys/types.h>

//1
int mensagens(char* palavra, char* ficheiro){
    char buffer[100];
    int resultado=0;
    int br=0;

    int p[2][2];
    pipe(p[0]);
    pipe(p[1]);

    if(fork()==0){
        close(p[0][0]);
        dup2(p[0][1],1);
        execlp("grep","grep",palavra,ficheiro,NULL);
        exit(0);
    }
    wait(NULL);
    close(p[0][1]);

    if(fork()==0){
        close(p[1][0]);
        dup2(p[0][0],0);
        dup2(p[1][1],1);
        execlp("wc","wc","-l",NULL);
        exit(0);
    }
    wait(NULL);
    close(p[0][0]);
    close(p[1][1]);

    br=read(p[1][0],buffer,sizeof(buffer));
    resultado=atoi(buffer);
    close(p[1][0]);

    return resultado;
}

int main(){
    int c=mensagens("bla","fich");
    printf("%d\n",c);
    return 0;
}