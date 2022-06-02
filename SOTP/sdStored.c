#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stdio.h>

#include "sdStored.h"

#define SIZE 1000
#define BUFF 1000
#define bufsize 100000

int nop_max=0,bcompress_max=0, gcompress_max = 0, encrypt_max=0,bdecompress_max=0,gdecompress_max=0,decrypt_max = 0;
int nop=0,bcompress=0,gcompress=0,encrypt=0,bdecompress=0,gdecompress=0,decrypt = 0;

int idGeral=0;
int num_tasks=0;
Task task[200];
Transform tr;
//executa varios pipes e redirects por ex: ./bcompress <input | ./encrypt | ./gcompress > out
int runPipedCommands(int commands, char *tokens[],char*input,char*output,char *path) {
    //printf("Inicio de runPipedCommands\n");

    int numPipes = commands -1;

    int status;
    int i;
    pid_t pid;
    int testin = open(input,O_RDONLY);
    int fd = open(output, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    int in = dup(0);
    int out= dup(1);
    
    if(commands == 0){
        return -1;
    }
    if(numPipes != commands-1){
        return -1;
    }
    if(numPipes==0){
        int res = dup2(testin, 0);
        res = dup2(fd, 1);
        if(!(pid = fork())) {
            execlp(tokens[0],tokens[0],NULL);
            _exit(1);
        }
        dup2(in,0);
        dup2(out, 1);
        return 0;
    }

    int pipefds[2*numPipes];

    for(i = 0; i < (numPipes); i++){
        if(pipe(pipefds + i*2) < 0) {
            perror("couldn't pipe");
            exit(EXIT_FAILURE);
        }
    }
    int res = dup2(testin, 0);


    res = dup2(pipefds[1], 1);
    

    //printf("Meio de runPipedCommands\n");


    if(!(pid = fork())) {
        execlp(tokens[0]
                ,tokens[0],NULL);
        _exit(1);
    }
    else{
        int waitret = wait(&status);
    }

    dup2(in,0);
    dup2(out, 1);

    int inf = dup(0);
    int outf= dup(1);

    int j = 2;
    int index = 4;
    int f=1;
    while(f!=commands) {

        pid = fork();
        if(pid == 0) {



            if(f!= commands-1){
                if(dup2(pipefds[j + 1], 1) < 0){
                    perror("dup2");
                    exit(EXIT_FAILURE);
                }
            }

            
            if(f != 0 ){
                if(dup2(pipefds[j-2], 0) < 0){
                    perror(" dup2");///j-2 0 j+1 1
                    exit(EXIT_FAILURE);

                }
            }
            
            if(f==commands-1){
                dup2(fd,1);
            }

            for(i = 0; i < 2*numPipes; i++){
                close(pipefds[i]);
            }
            if( execlp(tokens[f], tokens[f],NULL) < 0 ){
                perror("error");
                exit(EXIT_FAILURE);
            }
        } else if(pid < 0){
            perror("error");
            exit(EXIT_FAILURE);
        }
        j+=2;
        f+=1;
        //printf("Ciclo while de runPipedCommands\n");
    }


   

    for(i = 0; i < 2 * numPipes; i++){
        close(pipefds[i]);
    }

    for(i = 0; i < numPipes + 1; i++){
        wait(&status);}


    dup2(inf,0);
    dup2(outf, 1);
    
    return 0;

}


//retorna as transformações todas permitidas num array de structs(possivelmente muito complicado)
Transform *readln2(int fd, char *line, size_t size,Transform *tra) {
    static char buffer[BUFF];
    static ssize_t ptr_read;
    ssize_t n_read, ptr_write = 0;
    int numlin = 0;

    // ainda existem dados no buffer
    if (ptr_read  > 0) {
        while (ptr_read < size && buffer[ptr_read] != '\n') {}
    }

    while( (n_read = read(fd, buffer, BUFF)) ) {
        for (ptr_read = 0; ptr_read < n_read && ptr_write < size; ptr_read++) {
            line[ptr_write++] = buffer[ptr_read];
            if(buffer[ptr_read]=='\n'){
                numlin++;
            }
        }
    }
    char*lines[numlin];
    char *lin= strtok(buffer,"\n");
    int i = 0;
    while( lin != NULL && i<numlin ) {
        lines[i] = lin;
        lin = strtok(NULL, "\n");
        i++;
    }
    tra = malloc(sizeof(Transform)*numlin);
    for ( i = 0;i<numlin;i++){
        Transform a;
        char *temp = strtok(lines[i]," ");
        a.type = temp;
        temp = strtok(NULL," ");
        a.cap = atoi(temp);
        tra[i] = a;
        //printf("%s\n",a.type);

    }
    return tra;
}


int setmax(Transform* tra){
    for(int i=0;i<7;i++){
        if(strcmp(tra[i].type,"nop")==0)
            nop_max = tra[i].cap;
        else if(strcmp(tra[i].type,"gcompress")==0)
            gcompress_max = tra[i].cap;
        else if(strcmp(tra[i].type,"bcompress")==0)
            bcompress_max=tra[i].cap;
        else if(strcmp(tra[i].type,"bdecompress")==0)
            bdecompress_max = tra[i].cap;
        else if(strcmp(tra[i].type,"gdecompress")==0)
            gdecompress_max = tra[i].cap;
        else if(strcmp(tra[i].type,"decrypt")==0)
            decrypt_max = tra[i].cap;
        else if(strcmp(tra[i].type,"encrypt")==0)
            encrypt_max = tra[i].cap;
    }
}

char* descricao(char** toks, int tam){
    char* ret=malloc((22 * tam * sizeof(char))+tam);
    for(int i = 0; i<tam-1 ; i++ ){
        ret=strcat(ret , toks[i]);
        ret=strcat(ret , " ");
    }
    ret = strcat(ret, toks[tam-1]);
    return ret;
} 

char** toks(char* buf,int tam,char** toks){
    toks=malloc(sizeof(char*) * tam);
    char* p = strtok(strdup(buf), " ");
    int i=0;
    while (p != NULL){
        toks[i++] = p;
        p = strtok (NULL, " ");
    }
    return toks;
}



int contaEspacos(char* buf){
    int i=0;
    int n = strlen(buf);
    for(int j=0;j<n;j++){
        if(buf[j]==' '){
            i++;
        }
    }
    return i;
}


int ismax(char **c,int tam){
    for (int i=0;i<tam;i++){
        if(number_instances_max(c[i])==1)
            return 1;
    }
    return 0;
}

//vê se  o numero de instancias a correr está no limite maximo
int number_instances_max(char *trans){
    if(strcmp(trans,"nop")==0){
        if(nop_max == nop) return 1;
        else return 0;
    }
    else  if(strcmp(trans,"encrypt")==0){
        if(encrypt_max == encrypt) return 1;
        else return 0;
    }
    else  if(strcmp(trans,"decrypt")==0){
        if(decrypt_max == decrypt) return 1;
        else return 0;
    }
    else  if(strcmp(trans,"bcompress")==0){
        if(bcompress_max == bcompress) return 1;
        else return 0;
    }
    else  if(strcmp(trans,"bdecompress")==0){
        if(bdecompress_max == bdecompress) return 1;
        else return 0;
    }
    else  if(strcmp(trans,"gcompress")==0){
        if(nop_max == nop) return 1;
        else return 0;
    }
    else  if(strcmp(trans,"gdecompress")==0){
        if(gdecompress_max == gdecompress) return 1;
        else return 0;
    }

}


char* status (){
    char *st ; 
    if (num_tasks>0){
        st = malloc (   (num_tasks * 1000)   *sizeof (char));
    }
    else {
        st = malloc (   10000   *sizeof (char));
    }
    

    for (int i = 0;i<num_tasks && (task[i]->status)!=0;i++){
        
        char *filein = task[i]->in;
        char *fileout = task[i]->out;
        char *transfo = task[i]->t;
        char* t = "task";
        strcat(st,t);
        strcat(st,"#");
        char*id;
        sprintf(id,"%d",i);
        strcat(st,id);
        strcat(st,":");
        strcat(st," ");
        strcat(st,filein);
        strcat(st," ");
        strcat(st,fileout);
        strcat(st," ");
        strcat(st,transfo);
        strcat(st,"\n");

    }


    char *a = malloc(100 * sizeof(char));
    sprintf(a,"transf nop:%d/%d(running/max)\n",nop,nop_max);
    char *b=malloc(100 * sizeof(char));
    sprintf(b,"transf bcompress:%d/%d(running/max)\n",bcompress,bcompress_max);
    char *c = malloc(100 * sizeof(char));
    sprintf(c,"transf bdecompress:%d/%d(running/max)\n",bdecompress,bdecompress_max);
    char *d = malloc(100* sizeof(char));
    sprintf(d,"transf gcompress:%d/%d(running/max)\n",gcompress,gcompress_max);
    char *e =  malloc(100 *sizeof(char));
    sprintf(e,"transf gdecompress:%d/%d(running/max)\n",gdecompress,gdecompress_max);
    char*f=malloc(100* sizeof(char));
    sprintf(f,"transf encrypt:%d/%d(running/max)\n",encrypt,encrypt_max);
    char*g=malloc(100* sizeof(char));
    sprintf(g,"transf decrypt:%d/%d(running/max)\n",decrypt,decrypt_max);
    

    strcat(st,a);
    strcat(st,b);
    strcat(st,c);
    strcat(st,d);
    strcat(st,e);
    strcat(st,f);
    strcat(st,g);


return st;
}


void atualizaMaxsInc(char* descricao, int tam){
    char ** tran = toks(descricao,tam,tran);
    for(int i=0; i<tam ; i++){
        if(strcmp("bcompress",tran[i])==0){
            bcompress++;
        }
        else if(strcmp("nop",tran[i])==0){
            nop++;
        }
        else if(strcmp("bdecompess",tran[i])==0){
            bdecompress++;
        }
        else if(strcmp("gcompress",tran[i])==0){
            gcompress++;
        }
        else if(strcmp("gdecompress",tran[i])==0){
            gdecompress++;
        }
        else if(strcmp("encrypt",tran[i])==0){
            encrypt++;
        }
        else if(strcmp("decrypt",tran[i])==0){
            decrypt++;
        }
    }
}

void atualizaMaxsDec(char* descricao, int tam){
    char ** tran = toks(descricao,tam,tran);
    for(int i=0; i<tam ; i++){
        if(strcmp("bcompress",tran[i])==0){
            bcompress--;
        }
        else if(strcmp("nop",tran[i])==0){
            nop--;
        }
        else if(strcmp("bdecompess",tran[i])==0){
            bdecompress--;
        }
        else if(strcmp("gcompress",tran[i])==0){
            gcompress--;
        }
        else if(strcmp("gdecompress",tran[i])==0){
            gdecompress--;
        }
        else if(strcmp("encrypt",tran[i])==0){
            encrypt--;
        }
        else if(strcmp("decrypt",tran[i])==0){
            decrypt--;
        }
    }
}


void init_transform(Transform ts){
    ts.cap=0;
}

void free_transform(Transform a){
    free(a.type);
    //free((a.cap));
}

void add_task(char *m,char*in,char*out){
    Task ta = malloc(sizeof(struct task));
    ta->t = strdup(m);
    ta->status = 1; //coloca em pendente
    ta->in = in;
    ta->out = out;
    task[num_tasks] = ta;
    num_tasks++;
}
//função para verificar se todas as tasks terminaram
int tasks_finish(){
    int i=0;
    while(i<num_tasks){
        //se ainda tem tasks pendentes ou em processamento
        if(task[i]->status==1 || task[i]->status==2) return 0;
        i++;
    }
    return 1;
}
void signal_sigterm(int s){
    while(!tasks_finish()){
        //enquanto não estiverem terminadas todas as tasks adormecer 5 segundos
        sleep(5);
    }
    //ja terminaram todas as tasks
    kill(getpid(),SIGTERM);
}

int main(int argc, char *argv[] ){
    //argv[1] = "limites";
    //argv[2] = "transforms/";

    int stado;
    char * caminho="/home/miguel/UNI/2º ano/2º semestre/Sistemas Operativos/TP_21_22/Trabalho/SOTP-main/";//"/home/miguel/UNI/2º ano/2º semestre/Sistemas Operativos/TP_21_22/Trabalho/SOTP-main/"
    int fild = open( argv[1] , O_RDONLY);
    char **n_read;
    char line[SIZE];
    char **linhas;

    Transform  *t = readln2(fild, line, SIZE, t);//a ler direito

    char *string="./sdstore status\n./sdstore proc-file priority input-filename output-filename transformation-id-1 transformation-id-2 ...\n";

    //le as transformações do ficheiro e guarda num array.
    setmax(t);

    char buf[BUFSIZ];
    int server_to_client;//escreve
    char *myfifo2 = "tmp/server_to_client_fifo";
    //sprintf(stringID,"%d",idGeral);  

    int client_to_server;//lê
    char *myfifo = "tmp/client_to_server_fifo";
        
        
    mkfifo(myfifo2, 0666);
    mkfifo(myfifo,0666);

    while(1){
        //cria pipes entre cliente e servidor
       
       client_to_server = open(myfifo, O_RDONLY);
        server_to_client = open(myfifo2, O_WRONLY);
        
        //char* stringID=malloc(10 * sizeof(char));
        //sprintf(stringID,"%d",idGeral);

        //write(server_to_client,stringID,strlen(stringID));
        //idGeral++;
        
        if (fork()==0){
            read(client_to_server, buf, BUFSIZ); 

            if (strcmp("exit",buf)==0)
            {
                write(1,"Server OFF.\n",strlen("Server OFF.\n"));
                break;
            }

            else if (strcmp("exemplo",buf)==0){
                write(server_to_client,string,strlen(string));
                memset(buf, 0, sizeof(buf));
            }
            else if(strcmp("status",buf)==0){
                
                char* stats = status();
                write(server_to_client, stats , strlen (stats));
                memset(buf, 0, sizeof(buf));
            }
            else if(strstr(buf,"proc-file")!=NULL) {
                /*int server_to_client_id;//escreve
                char *myfifo3 = malloc(100 * sizeof(char));
                sprintf(myfifo3,"tmp/server_to_client_fifo_%d",idGeral);
                mkfifo(myfifo3, 0666);
                server_to_client_id=open(myfifo3,O_WRONLY);*/
                
                int tam = contaEspacos(buf) + 1;
                char **re = toks(buf,tam,re);
                char **tokens = malloc(sizeof(char*) * (tam-3));
                int index = 0;
                for (int i = 3;i<tam;i++){
                    tokens[index] = re[i];
                    index++;
                }
                    
                Task ta = malloc(sizeof(struct task));
                    
                ta-> in = re[1];
                ta-> out = re[2];
                ta-> t = descricao(tokens,tam-3);
                ta-> id = idGeral;
                ta->status=1;
                    
                task[num_tasks] = ta;
                num_tasks++;
                int pip[2];
                if(pipe(pip)<0){
                    perror("pipe");
                }
                int flag = 0;
                while(flag == 0){
                    write(server_to_client,"Pending...",strlen("Pending..."));
                    
                    ta->status=1;
                    if(ismax(tokens,tam-3)==0){
                        flag = 1;
                    }
                }
                if(flag==1){
                    write(server_to_client,"Processing...",strlen("Processing..."));
                    ta->status=2;
                    atualizaMaxsInc(ta->t,tam-3);
                    char* resARG=malloc(1000 * sizeof(char));
                    for(int i=2;i<argc-1;i++){
                        resARG=strcat(resARG,strdup(argv[i]));
                        resARG=strcat(resARG," ");
                    }
                    resARG=strcat(resARG,strdup(argv[argc-1]));
                    for(int i=0; i<tam-3 ; i++){
                        char* path=malloc(1000*sizeof(char));
                        path = strcpy(path,strdup(resARG));
                        strcat(path,strdup(tokens[i]));
                        tokens[i]=path;
                        
                    }
                    if(fork()==0){
                        runPipedCommands(tam-3,tokens,re[1],re[2],caminho);///home/miguel/UNI/2º ano/2º semestre/Sistemas Operativos/TP_21_22/Trabalho/SOTP-main/
                        exit(0);
                    }
                    else{
                        wait(&stado);//&stado
                    }
                    write(server_to_client,"Concluded...",strlen("Concluded..."));
                    
                    ta->status=0;
                    atualizaMaxsDec(ta->t,tam-3);
                }
                        
                for(int i=0; task[i]; i++){
                    if(task[i]->id==ta->id){
                        for(int j=i; j<num_tasks; j++){
                            task[j]=task[j+1];
                        }
                        break;
                    }
                }     
                num_tasks--;
                memset(buf, 0, sizeof(buf));
                
                
            }
        
        }
        /* clean buf from any data */
        else {
            wait(NULL);
            memset(buf, 0, sizeof(buf));
        }
    }

//./sdStore proc-file test toumaisquefddirmoum bcompress nop gcompress encrypt nop

    close(client_to_server);
    close(server_to_client);

    unlink(myfifo);
    unlink(myfifo2);
    return 0;

}


/*----------------------------------------------------------------
   if(fork()!=0){//pai
               
              int flag = 0;
              while(flag==0){
                  
                  if(pend==true) 
                  {write(server_to_client,"Pending...\n",strlen("pending...\n"));
                  pend = false;}
                  
                  if(ismax(tokens,tam-3)==0) {
                      atualizaMaxsInc(ta->t,tam-3);
                      write(server_to_client,"crl",3);
                      flag = 1;
                      }

              }
                  
                  runPipedCommands(tam-3,tokens,re[1],re[2]);
                  write(server_to_client,"Processing...\n",strlen("Processing...\n"));
                  close(pipes[0]);
                  write(pipes[1],"run",strlen("run"));
                  close(pipes[1]);
                  wait(NULL);//wait filho
                  write(server_to_client,"Concluded.\n",strlen("Concluded\n"));
                               
              } 
              else{//filho
                close(pipes[1]);
                char *buf= malloc(3 * sizeof(char));
                read(pipes[0],buf,3);
                close(pipes[0]);
                if(strcmp(buf,"run")==0){
                     runPipedCommands(tam-3,tokens,re[1],re[2]);
                     atualizaMaxsDec(ta->t,tam-3);
                
                exit(0);
              }     

            }*/