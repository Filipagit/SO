#include <sys/types.h>
#include <sys/stat.h>

//Programa 1 
// Cria um pipe com o nome fifo 
int main(int argc,char *argv[]){
    mkfifo("fifo",0644);
    return 0;
}
