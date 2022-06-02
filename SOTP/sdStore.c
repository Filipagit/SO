    #include <unistd.h>
    #include <sys/wait.h>
    #include <sys/stat.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <fcntl.h>



// SERVIDOR
// ./a.out "path_ficheiro" "path_pasta_de_executaveis"

// CLIENTE
// ./a.out status

int tamArgs(char** argv,int argc){
    int i=0;
    for(int j=1;j<argc;j++){
        i+=strlen(argv[j]);
    }
    return i;
}


int main(int argc, char *argv[] ) {

    int client_to_server;
    char *myfifo = "tmp/client_to_server_fifo";

    int server_to_client;
    char *myfifo2 = "tmp/server_to_client_fifo";

    char str[BUFSIZ];

    /* write str to the FIFO */
    client_to_server = open(myfifo, O_WRONLY);
    server_to_client = open(myfifo2, O_RDONLY);

    //read(server_to_client, str,BUFSIZ);
    //int id=atoi(str);
    

    //int server_to_client_id;//escreve
    //char *myfifo3 = malloc(100 * sizeof(char));
    //sprintf(myfifo3,"tmp/server_to_client_fifo_%d",id);
    


    if(argc==1){

        write(client_to_server, "exemplo", 7);
        read(server_to_client,str,BUFSIZ);
        write(1,str,strlen(str));

    }
    else if(argc==2 && strcmp(argv[1],"status")==0){
        //printf("status\n");
        //char b[BUFSIZ];
        char* status="status";
        write(client_to_server, status, strlen(status));

        read(server_to_client, str, BUFSIZ);
        write(1,str,strlen(str));

    }
    else if(strcmp(argv[1],"proc-file")==0){

        int tam=tamArgs(argv,argc);

        char *amanda = malloc(sizeof (char*)*tam);
        int i;
        for(i=1;i<argc-1;i++){
            strcat(amanda,argv[i]);
            strcat(amanda," ");
        }
        strcat(amanda,argv[i]);


        write(client_to_server, amanda, strlen(amanda));
        

        //server_to_client_id=open(myfifo3,O_RDONLY);
        //read(server_to_client_id,str,BUFSIZ);
        
        
        while(strstr(str,"Concluded...")==NULL){//read(server_to_client,str,BUFSIZ)>0 &&
            if(strstr(str,"Pending...")!=NULL){
                write(1,str,strlen(str));
                write(1,"\n",strlen("\n"));
            }
            else if(strstr( str,"Processing...")!=NULL){
                write(1,str,strlen(str));
                write(1,"\n",strlen("\n"));
            }
            //char str1[BUFSIZ];
            read(server_to_client,str,BUFSIZ);
            //strcpy(str,str1);
            
        }
        write(1,str,strlen(str));
        write(1,"\n",strlen("\n"));

        /*printf("%s\n",str);
        while(strstr(str,"Processing...")!=NULL){
            printf("esta processing lendo novemanete\n");
            read(server_to_client,str,BUFSIZ);
        }
        //printf("NAO ESTA -> %s\n",str);
        printf("%s\n",str);*/

        //printf("\n");
        //write(client_to_server, "ola", 3);
    }

    // argv = ./sdStore proc-file teste out gcompress nop bcompress encrypt
    // argv = ./sdStore status
    // argv = ./sdStore                      cena dos exemplos

    //----------------------------------COMPLETO ATE AQUI----------------------------------//

    //perror("Write:"); //Very crude error check

    //read(server_to_client,str,sizeof(str));

    //perror("Read:"); // Very crude error check

    //printf("...received from the server: %s\n",str);
    close(client_to_server);
    close(server_to_client);
    return 0;




}

/*
    int stdin_backup = dup(0);
    int stdout_backup = dup(1);
	int i=2;
    int c = 0;
    int in;
    int out;
	int boolB=0,boolG=0,boolCry=0;
	int boolDB=0,boolDG=0,boolDCry=0;
	char* string="./sdstore status\n./sdstore proc-file priority input-filename output-filename transformation-id-1 transformation-id-2 ...\n";
	//char[] buffer="";
	if (argc==1){
		//int tam=read(1,"./sdstore status\n./sdstore proc-file priority input-filename output-filename transformation-id-1 transformation-id-2 ...",121);
		write(1,string,strlen(string));
	}
	else if (strcmp(argv[i],"status")==0){
		printf("status\n");
	}
	else if (strcmp(argv[i-1],"proc-file")==0){
        in = open(argv[i],O_RDONLY);
        out = open(argv[i+1],O_CREAT|O_TRUNC|O_WRONLY,0666);
        i+=2;
        *
		while(i<argc){
			if (strcmp(argv[i],"nop")==0){
				printf("nop  %s\n",argv[i+1]);
			}
			else if(strcmp(argv[i],"bcompress")==0 && !boolDB){
				printf("bcompress  %s\n",argv[i+1]);

				boolB=1;
			}
			else if(strcmp(argv[i],"bdecompress")==0 && !boolB){
				printf("bdecompress  %s\n",argv[i+1]);
				boolDB=1;

			}
			else if(strcmp(argv[i],"gcompress")==0 && !boolDG){
				printf("gcompress  %s\n",argv[i+1]);
				boolG=1;
			}
			else if(strcmp(argv[i],"gdecompress")==0 && !boolG){
				printf("gdecompress  %s\n",argv[i+1]);
				boolDG=1;
			}
			else if(strcmp(argv[i],"encrypt")==0 && !boolDCry){
				printf("encrypt  %s\n",argv[i+1]);
				boolCry=1;
			}
			else if(strcmp(argv[i],"decrypt")==0 && !boolCry){
				printf("decrypt  %s\n",argv[i+1]);
				boolDCry=1;
			}
			i+=2;
		}*
        while (i<argc){
            if(i==4){
                dup2(in,0);
                close(in);
                //execl(strcat("/home/miguel/Downloads/SDStore-transf/SDStore-transf/",tokens[i]),strcat("/home/miguel/Downloads/SDStore-transf/SDStore-transf/",tokens[i]),NULL);
                dup2(stdin_backup, 0);
            }
            if(i==argc-1){
                dup2(out,1);
                close(out);
                //execl(strcat("/home/miguel/Downloads/SDStore-transf/SDStore-transf/",tokens[i]),strcat("/home/miguel/Downloads/SDStore-transf/SDStore-transf/",tokens[i]),NULL);
                dup2(stdout_backup, 1);
            }
        }
	}
	return 1;
*/