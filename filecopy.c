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

    int fd[2]; // file descriptors
    // fd[0] - read
    // fd[1] - write
    if (pipe(fd) == -1) { // pipe returns 0 if successful, -1 if not
        printf("An error orccured with opening the pipe\n");
        return 1;
    }
    
    int id = fork(); // when you fork fd get copied over, they get inherited
    // if you close the fd in one process, it remains open in the other, independent
    if (id == -1) { // checks for forking error
        printf("An error orccured with fork\n");
        return 2;
    }
    
    if (id == 0) { // child process
        close(fd[0]); // close read cause we not using it
        int x;
        printf("Enter a number: ");
        scanf("%d", &x);
        if (write(fd[1], &x, sizeof(int)) == -1) { // write() - fd, memory to write from, what to write
            // checking for error (-1) else returns number written
            printf("An error orccured with writing to the pipe\n");
            return 3;
        }
        close(fd[1]); // close write after done
    } else { // main process
        close(fd[1]); // close write cause we not using it
        int y;
        if (read(fd[0], &y, sizeof(int)) == -1) { // read() - fd, read into something, what to write
            // checking for error (-1), 0 end of file, returns number read 
            printf("An error orccured with reading to the pipe\n");
            return 4;
        }
        close(fd[0]); // close read after done
        printf("Got from child process %d\n", y);
    }

    // we should check for errors when writing or reading: returns num written or read, or -1 (errors)

	return 0;
}
