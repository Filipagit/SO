#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */

//programa que imprima o seu identificador de processo e o do seu pai
int main(){
    printf("pid: %d\n",getpid());
    printf("pid do pai: %d\n",getppid());
    return 0;
}