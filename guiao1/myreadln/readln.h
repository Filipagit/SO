#include <unistd.h> 
#include <fcntl.h>
#include <stdio.h>

ssize_t readln(int fd, char *line, size_t size);
ssize_t readln_ex4(int fd, char *line, size_t size);
ssize_t readln_alt(int fd, char *line, size_t size);
