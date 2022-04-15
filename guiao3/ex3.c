#include<unistd.h>
#include<stdio.h>
#include<sys/wait.h>

int main(int argc,char *argv[]){
pid_t pid;
int nproc=10;
int status,i;
   for(i=1;i<nproc;i++){
       if(fork()==0){
        //código do processo filho
        execlp(argv[i],argv[i],NULL);
        perror("exec");
         _exit(i);
    }
   }
    
    for(i=1; i<nproc; i++) {
		pid_t terminated_pid=wait(&status);
        //se o filho retornou entao WIFEXITED retorna True
        //se o filho retornou -1 entao WIFEXITED retorna True e WEXITSTATUS retorna 255(-1)
        if(WIFEXITED(status)){
            printf("[pai] process %d exited exit code: %d\n",terminated_pid,WEXITSTATUS(status));
        }
        else {
             printf("[pai] process %d exited \n",terminated_pid);
        }
    }
	return 0;
}
    