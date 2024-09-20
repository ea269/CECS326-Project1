/**
 * filecopy.c
 *
 * This program copies files using a pipe.
 *
 */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

#define READ_END 0
#define WRITE_END 1

int main(int argc, char *argv[]) {
	if (argc != 3) {// Checks if there more or less than 2 parameter
		printf("Please enter 2 parameters:\n");
		printf("Parameter 1: Source file.\n");
		printf("Parameter 2: Destination file.\n");
        printf("Example: filecopy source.txt destination.txt\n");
		exit(EXIT_SUCCESS);
	}
    
    // Read/Write file
    FILE *f1;
    FILE *f2;
    
    f1 = fopen(argv[1], "r");
    f2 = fopen(argv[2], "w");

    // Piping
    int fd[2];
    pipe(fd);

    // Forking
    int id = fork();

    if (id == 0) { // child process 
        close(fd[1]);
        read(fd[0], READ_END, f2);
        close(fd[1]);
    } else { // parent process
        close(fd[1]);
        read(fd[0], f1, WRITE_END);
        close(fd[0]);
    }
    
	return 0;
}
