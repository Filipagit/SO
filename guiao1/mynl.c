#include <sys/types.h>
#include <unistd.h>		/* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h>		/* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdio.h>


#define BUFFER_SIZE 1000

//lista as linhas 
int my_nl(){
	int nl = 0, s_read = 0, s_write = 0, off_set;
	char buf[BUFFER_SIZE];

	off_set = sprintf(buf, "%i | ", nl++);
	while((s_read = readln(STDIN_FILENO, buf + off_set, BUFFER_SIZE - off_set)) > 0){
	 	if((s_write = write(STDOUT_FILENO, buf, s_read + off_set)) == -1){
	 		perror("Error writing\n"); 
	 		return 1;
	 	}
	 	else
	 		if(s_write < s_read){
	 			perror("Couldn't write everything\n");
	 			return 1;
	 		}
	 		else
	 			off_set = sprintf(buf, "%i | ", nl++);
	}
	if(s_read == -1){
		perror("Error reading\n");
		return 1;
	}

	return 0;
	
}