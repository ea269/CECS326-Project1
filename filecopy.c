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
    //FILE *f1;
    //FILE *f2;
    
    FILE *f1 = fopen(argv[1], "r");
    FILE *f2 = fopen(argv[2], "w");

    // Piping
    int fd[2]; // f[0] - read, f[1] - write
    if (pipe(fd) == -1) { // -1 returning from pipe indicates error
        printf("An error occured with opening the pipe\n");
    }

    // Forking
    int id = fork(); // returns 0 for child process, a big num for parent process
    if (id == -1) { // -1 returning from fork indicates error
        printf("An error occured with forking\n");
    }

    if (id == 0) { // child process 
        int y;
        read(fd[0], &y, READ_END);
        write(fd[1], f2, &y);
        close(fd[0]);
        close(fd[1]);
    } else { // parent process
        int x;
        read(fd[0], &x, f1);
        write(fd[1], WRITE_END, &x);
        close(fd[0]);
        close(fd[1]);
    }
    
	return 0;
}
