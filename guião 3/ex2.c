#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
//lista o conteudo do diretorio do processo filho conseguii
 int main(int argc, char**argv){
     int ret,pid,status;
     if((pid=fork())==0){
        //codigo do filho
        printf("FILHO: %d\n",getpid());
        ret=execvp("ls","-l",NULL);
        _exit(ret);
 }
 else {
      printf("PAI: %d\n",getpid());
       pid_t terminated_pid=wait(&status);
         if(WIFEXITED(status)){// se correu tudo bem 
         printf("FATHER: son with pid %d terminated with status %d\n",terminated_pid,WEXITSTATUS(status));
         }
         else{
              printf("ocorreu um erro\n");
         }
 }
 return 0;
 }