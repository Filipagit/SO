#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
//imprime o id do processo pai e o do seu processo
int main(){
printf("O meu pid é: %d\n",getpid());
printf("O pid do meu pai é: %d\n",getppid());
//sleep(10); adormece o processo durante 10 seg
return 0;
}

