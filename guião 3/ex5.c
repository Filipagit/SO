#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

//executar concorrentemente uma lista de executaveis especificados como argumentos da linha de comando
int main(int argc, char**argv){
    int i,pid,ret;
    for(i=1;i<argc;i++){
    if((pid=fork())==0){
        //codigo do filho
        printf("FILHO: %d\n",getpid(),argv[i]);
         ret=execlp(argv[i],NULL);
         perror("reached return");
         _exit(ret);
    }
    
    }
    for(i=1; i<argc; i++) {
		printf("Sou o pai e estou à espera dos filhos\n");
		wait(NULL); //para esperar por todos(?)
	}
	printf("Todos os filhos executaram.\n");

	return 0;
}