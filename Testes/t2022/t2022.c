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

//2 
int autores_que_usaram(char* palavra, int n, char* autores[n]){
    pid_t pid[n];
    int res=0;
    int i,aux=0;

    for(i=0;i<n;i++){
        if((pid[i]==fork())==0){
     aux=mensagens(palavra,autores[i]);
     exit(aux);
    }
}
for(i=0;i<n;i++){
    int status;
    pid_t aux= waitpid(pid[i],&status,0);
       if(WIFEXITED(status)){
           if(WEXITSTATUS(status)) res++;
       }
       else{
           char buff[256];
           int bytes=sprintf(buff,"Erro no ficheiro: %d\n",i);
           write(2,buff,bytes);
       }
}
return res;
}

int main(){
    int c=mensagens("bla","fich");
    printf("%d\n",c);
    return 0;
}