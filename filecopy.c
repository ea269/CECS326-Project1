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
    
    int id = fork();
    int n;

    if (id == 0) { // child process
        n = 1;
    } else { // parent process
        n = 6;
    }

    if (id != 0) { // if we are in main process 
        wait(NULL);
    }
    
    // wait() // doing this here just stops all process
    
    int i;
    for (i = n; i < n + 5; i++) {
        printf("%d ", i); // normally this buffers so it  would wait for the whole process to run this loop and then print
        fflush(stdout); // this prints it out as soon as it runs in every single iteration
        usleep(10000); // found an error, where fflush doesnt print out each iteration, might be due to os
        // usleep just allows more time for the os to switch betweeen proceess allowing it to be mixed like this:
        // this is without wait() 
        // with just printf() 6 7 8 9 10 \n 1 2 3 4 5 
        // with fflush() 6 1 7 2 8 3 9 4 10 5
    }

    if (id != 0) {
        printf("\n");
    }

	return 0;
}
