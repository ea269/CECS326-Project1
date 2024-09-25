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
#define BUFFER_SIZE 1024
#define STRING_SIZE 256

int main(int argc, char *argv[]) {
    if (argc != 3) {  // Checks if there more or less than 2 parameter
        printf("Please enter 2 parameters:\n");
        printf("Parameter 1: Source file.\n");
        printf("Parameter 2: Destination file.\n");
        printf("Example: filecopy source.txt destination.txt\n");
        exit(EXIT_SUCCESS);
    }

    // Piping
    int fd[2];  // f[0] - read, f[1] - write
    if (pipe(fd) == -1) {  // -1 returning from pipe indicates error
        printf("An error occured with opening the pipe\n");
        exit(EXIT_FAILURE);
    }

    // Forking
    int id = fork();  // returns 0 for child, big num for parent process
    if (id == -1) {  // -1 returning from fork indicates error
        printf("An error occured with forking\n");
        exit(EXIT_FAILURE);
    }

    if (id == 0) {  // child process
        // closes the read pipe
        close(fd[READ_END]);
        
        // open the destination file to write
        FILE *f2 = fopen(argv[2], "w");
        if (f2 == NULL) {
            printf("Error opening destination file.\n");
            exit(EXIT_FAILURE);
        }

        char buffer[BUFFER_SIZE];

        ssize_t bytes_read; // cannot declare this in while loop

        // returns num of elements read, so check if > 0
        while ((bytes_read = fread(buffer, sizeof(buffer), STRING_SIZE, f2)) > 0) {
            fwrite(buffer, sizeof(char), bytes_read, f2);
        }
        fclose(f2);
        close(fd[WRITE_END]);

    } else {  // parent process
        // closes the write pipe
        close(fd[WRITE_END]);
        
        // open the source file to read
        FILE *f1 = fopen(argv[1], "r");
        if (f1 == NULL) {
            printf("Error opening source file.\n");
            exit(EXIT_FAILURE);
        }

        char buffer[BUFFER_SIZE];

        ssize_t bytes_read; // cannot declare this in while loop
        //
        // returns num of elements read, so check if > 0
        while ((bytes_read = fread(buffer, sizeof(buffer), STRING_SIZE, f1)) > 0) {
            fwrite(buffer, sizeof(buffer), STRING_SIZE, f1);
        }
        fclose(f1);
        close(fd[READ_END]);
        wait(NULL);  // waiting on child process to finish
    }

    return 0;
}
