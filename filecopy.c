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
    FILE *f1 = fopen(argv[1], "r");
    FILE *f2 = fopen(argv[2], "w");
    
    f1 = fopen(argv[1], "r");
    f2 = fopen(argv[2], "w");

	//piping
	int fd[2]; // f[0] -read, f[1]- write
	if (pipe(fd) == -1) { // -1 returing from pipe indicates error
		printf("An error occured with opening the pipe\n");
		exit(EXIT_FAILURE);
		}

	if (id == -1) {  // -1 returning from fork indicates error
	    printf("An error occured with forking\n");
		exit(EXIT_FAILURE);
	}

    // Forking
    int id = fork();

    if (id == 0) { // child process
		 close(fd[READ_END]);
		 if (fwrite(fd[WRITE_END], f2, EOF) == -1) { // -1: error, 0 end of file, returns number written
			printf("An error occured with child writing to the pipe\n");
			exit(EXIT_FAILURE);
		 }
		 close(fd[WRITE_END])

	} else { // main process
		close(fd[WRITE_END]);
        if (fread(fd[READ_END], f1, size) == -1) {  // -1: error, 0 end of file, returns number read
			printf("An error occured with parent writing to the pipe\n");
			exit(EXIT_FAILURE);
		}
		close(fd[READ_END]);
    }

    printf("File successfully copied %d", argv[1], "to%d", argv[2]); 
	return 0;
}
