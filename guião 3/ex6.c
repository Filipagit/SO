#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]){
    pid_t pid;

	if((pid = fork()) == 0){
		execvp(argv[1],&(argv[1]));
	}

	wait(NULL);

    return 0;
} 