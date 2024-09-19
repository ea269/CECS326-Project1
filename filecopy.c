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
    /*
	if (argc != 3) // Checks if there more or less than 2 parameter {
		printf("Please enter 2 parameters:\n");
		printf("Parameter 1: Source file.\n");
		printf("Parameter 2: Destination file.\n");
        printf("Example: filecopy source.txt destination.txt\n");
		exit(EXIT_SUCCESS);
	}
    */

    printf("Forking will happen soon..\n");
    
    int id = fork();
    // clone the calling process, creating an exact copy
    // fork returns -1 for errors 0 for new processes (child)
    printf("Fork id is %d\n", id);
    
    // each fork () is 2^n execution from there
    if (id != 0) { // will only fork if its in main process (how we get odd number of forks)
        fork();
    }

    if (id == 0) { // 0 = chilid
        printf("Child Process\n");
    } else { // a big random number = main
        printf("Main Process\n");
    }

    printf("Hello world\n");

	return 0;
}
