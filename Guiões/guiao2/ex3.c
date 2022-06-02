#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main(){
  int i;
  int status;
  pid_t rf;
    for(i=0;i<10;i++){
        if((rf=fork()==0)){
            //Código do filho
            printf("O meu pid%d;pid do meu pai é %d\n",getpid(),getppid());
            _exit(1);
        }
        else{
         //Codigo do pai
         pid_t pidt=wait(&status);
          if(WIFEXITED(status)){
              printf("filho com o pid %d terminou com status%d\n",pidt,WEXITSTATUS(status));
          }
          else printf("erro\n");
        }
    }
    return 0;
}