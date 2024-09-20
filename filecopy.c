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
        close(fd[0]);
        if (write(fd[1], f2, READ_END) == -1) { // -1: error, 0 end of file, returns number written
            printf("An error occured with writing to the pipe\n");
        }
        close(fd[1]);
    } else { // parent process
        close(fd[1]);
        if (read(fd[0], WRITE_END, f1)) { // -1: error, 0 end of file, returns number read
            printf("An error occured with writing to the pipe\n");
        }
        close(fd[0]);
    }
    
	return 0;
}
