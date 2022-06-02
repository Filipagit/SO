#include <unistd.h>
#include <fcntl.h>
int main(){

    open("linhas.txt",O_RDONLY);\
    return 1;
}