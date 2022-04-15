#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

/*
Modifique novamente o programa inicial de modo a que seja executado o comando wc, sem argumentos,
depois do redireccionamento dos descritores de entrada e saı́da. Note que, mais uma vez, as associações
– e redireccionamentos – de descritores de ficheiros são preservados pela primitiva exec().
*/
int main(int argc, char* argv[]){
    int imp=open("/etc/passwd",O_RDONLY);
    int outp=open("saida.txt",O_CREAT | O_TRUNC | O_WRONLY,0644);
    int err=open("erros.txt",O_CREAT | O_TRUNC | O_WRONLY,0644);
    //faz a copia
    int i=dup2(imp,0);
    int o=dup2(outp,1);
    int e=dup2(err,2);
   //fecha o original 
    close(imp);
    close(outp);
    close(err);

    execlp("wc","wc",NULL);
    /* Agora aparecem nos ficheiros o resultado da execucao de comando wc.
    Além disso, não temos nada no erros.txt porque nao ha erros. Portanto 
    foram redirecionados os resultados.
    Agora não escrevemos nos ficheiros os standard input, output e error.*/
    return 0;
}