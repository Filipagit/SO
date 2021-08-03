
//determinar a existência de um determinado número inteiro nas linhas de numa matriz de
//números inteiros, em que o número de colunas é muito maior do que o número de linhas. Implemente,
//utilizando processos um programa que determine a existência de um determinado número, recebido como
//argumento, numa matriz gerada aleatoriamente.

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
	if (argc < 2) {
		printf("Usage: program <needle>\n");
		exit(-1);
	}

	pid_t pid;
	int needle = atoi(argv[1]);
	int rows = 10;
	int cols = 10000;
	int rand_max = 10000;
	int status;
	int **matrix; 

	//Allocate and populate matrix with random numbers
	printf("Generating numbers from 0 to %d...", rand_max);
	matrix = (int**) malloc(sizeof(int*) * rows);
	for(int i=0; i<rows; i++) {
		matrix[i] = (int*) malloc(sizeof(int) * cols);
		for(int j=0; j<cols; j++) {
			matrix[i][j] = rand() % rand_max;
		}
	}
	printf("Done.\n");

	for(int i=0; i<rows; i++) {
		if((pid = fork()) == 0) {
			printf("[pid %d] row: %d\n", getpid(), i);

			//start searching for the given number in row #i
			for(int j=0; j<cols; j++) {
				if(matrix[i][j] == needle) {
					_exit(i);
				}
			}
			_exit(-1);
		}
	}

	for(int i=0; i<rows; i++) {
		pid_t terminated_pid = wait(&status);

		if(WIFEXITED(status)) {
			if(WEXITSTATUS(status) < 255) //255 = -1, na representação de 3bytes
				printf("[pai] process %d exited. found number at row: %d\n", terminated_pid, WEXITSTATUS(status));
			else 
				printf("[pai] process %d exited. nothing found\n", terminated_pid);
		}
		else {
			printf("[pai] process %d exited. something went wrong\n", terminated_pid);
		}
	}
	return 0;
}



/*
linha 
vantagens: 
->procura em zona de memoria contigua
->menos overhead na criação de processos

Desvantagens:
-> menos processos podem tornar a procura mais lenta 

coluna
 vantagens: em teoria , maior nº de processos torna a procura mais rapida(+ paralelismo)
 desvantagens : 
 ->procura em zona de memoria nao contigua
 -> mais overhead na criacao de processos
 */