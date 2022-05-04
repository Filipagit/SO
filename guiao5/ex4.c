#include <unistd.h>

//pipe[0] -> leitura pipe[1]-> escrita
//ls/etc lista o conteuo de etc 
//ls /etc | wc -l.
int main(){
  int pipe_fd[2];
  if(pipe(pipe_fd)<0){
      perror("erro na criação do pipe");
      _exit(1);
  }
  if(fork()==0){
      close(pipe_fd[0]);
      dup2(pipe_fd[1],1);
      close(pipe_fd[1]);
      execlp("ls","ls","/etc",NULL);
      _exit(1);
  }
  close(pipe_fd[1]);
  if(fork()==0){
      dup2(pipe_fd[0],0);
      close(pipe_fd[0]);
      execlp("wc","wc","-l",NULL);
      _exit(1);
  }
  close(pipe_fd[0]);
  if(wait(NULL)==-1) puts("Error");
  return 0;
  }