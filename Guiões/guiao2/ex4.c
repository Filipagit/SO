#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main(){
  int i;
  int status;
  pid_t rf;
  for(i=0;i<10;i++){
      if((rf=fork())==0){
          printf("[FILHO] o meu pid é %d; o pid do meu pai é %d\n",getpid(),getppid());
          _exit(i);
      }
  }
  for(i=0;i<10;i++){
      printf("Novo ciclo: %d\n",i);
      pid_t terminated_pid=wait(&status);
      if(WIFEXITED(status)){
          printf("[PAI] o meu pid é %d status %d\n",terminated_pid,WEXITSTATUS(status));
          printf("[PAI] o pid do meu filho é %d status %d\n",terminated_pid,WEXITSTATUS(status));
      }
      else{
          printf("Erro\n");
      }
  }
  return 0;
}