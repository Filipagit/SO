//programa que crie um processo filho. Pai e filho devem imprimir o seu identificador de
//processo e o do seu pai. O pai deve ainda imprimir o PID do seu filho.  conseguii
int main (){
    pid_t pid;
    if((pid=fork())==0){
        //codigo do filho
        printf("[FILHO] pid: %d\n",getpid());
        printf("[FILHO] pid do pai: %d\n",getppid());
    }
    else{
        //codigo do pai 
        printf(" pid: %d\n",getpid());
        printf("pid do pai: %d\n",getppid());
        printf("pid do filho: %d\n",pid);
    }
    return 0;
}