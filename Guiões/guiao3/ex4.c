#include <sys/wait.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int mysystem(char * command){
int fork_ret,exec_ret,wait_ret,status,res;

	char *exec_args[20]; //melhoria: alocação dinâmica de memória
	char *string;
	int i = 0;

	string = strtok(command," ");

	while(string!=NULL) {

		exec_args[i] = string;
		string = strtok(NULL," ");
		i++;
	}

	exec_args[i] = NULL;

	fork_ret = fork();
	if(fork_ret == 0) {

		exec_ret = execvp(exec_args[0], exec_args);
		_exit(exec_ret);
	}
	else {
		if(fork_ret != -1) {
			wait_ret = waitpid(fork_ret,&status,0);

			if(WIFEXITED(status)) {
				res = WEXITSTATUS(status);
			}
			else res = -1;
		}
		else res = -1;
	}

	return res;
}

int main(int argc, char** argv) {

	char comando1[] = "ls -l -a -h";
	char comando2[] = "sleep 2";
	char comando3[] = "ps";
	int ret;

	printf("a executar mysystem para %s\n", comando1);
	ret = mysystem(comando1);
	printf("ret: %d\n", ret);

	printf("a executar mysystem para %s\n", comando2);
	mysystem(comando2);

	printf("a executar mysystem para %s\n", comando3);
	mysystem(comando3);

	return 0;
}