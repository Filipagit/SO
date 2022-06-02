//
// Created by miguel on 07-05-2022.

#ifndef SOTP_MAIN_SDSTORED_H
#define SOTP_MAIN_SDSTORED_H
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

typedef struct {
    char *type;
    int cap;
}Transform;

typedef struct task{
    int id;
    char *t;
    char *in;
    char *out;
    int status; //0->acabado 1->pendente 2-> em processamento
} *Task;
#endif //SOTP_MAIN_SDSTORED_H

int runPipedCommands(int commands, char *tokens[],char*input,char*output,char *path);
Transform *readln2(int fd, char *line, size_t size,Transform *tr);
int setmax(Transform* tr);
char** toks(char* buf,int tam,char** toks);
int contaEspacos(char* buf);
int number_instances_max(char *ty);
void init_transform(Transform ts);
void free_transform(Transform a);
void add_task(char *m,char*in,char *out);
int tasks_finish();
void signal_sigterm(int s);