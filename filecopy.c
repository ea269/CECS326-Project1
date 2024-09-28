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
#define BUFFER_SIZE 25

int main(int argc, char *argv[]) {
    if (argc != 3) {  // Checks if there more or less than 2 parameter
        printf("Please enter 2 parameters:\n");
        printf("Parameter 1: Source file.\n");
        printf("Parameter 2: Destination file.\n");
        printf("Example: filecopy input.txt output.txt\n");
        exit(EXIT_FAILURE);
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
        close(fd[WRITE_END]);

        // Lets user know what process is currently running
        //printf("Running child process...\n");

       // open the destination file to write
        FILE *f2 = fopen(argv[2], "w");
        if (f2 == NULL) {
            printf("Error opening destination file.\n");
            exit(EXIT_FAILURE);
        } /*else {  // comfirm to user source opened
            printf("Destination file opened.\n");
        }*/

        char buffer[BUFFER_SIZE];
        ssize_t bytes_read;  // NOTE: cannot declare this in while loop

        // Read from the pipe and write to the destination file
        while ((bytes_read = read(fd[READ_END], buffer, BUFFER_SIZE)) > 0) {
            // check if the right num of bytes is written
            if (fwrite(buffer, sizeof(char), bytes_read, f2) != bytes_read) {
                printf("Error writing to destination file.\n");
                exit(EXIT_FAILURE);
            }         
        }
        // NOTE: Both read and writing have to be in a while loop

        if (bytes_read == -1) {
            printf("Could not read from the pipe.");
            exit(EXIT_FAILURE);
        }

        //printf("Child process done.\n");
        fclose(f2);
        close(fd[READ_END]);

        printf("File successfully copied from %s to %s.\n\n", argv[1], argv[2]);


    } else {  // parent process
        // closes the write pipe
        close(fd[READ_END]);

        //  lets user know what process is running
        //printf("Running Parent process...\n");

        // open the source file to read
        FILE *f1 = fopen(argv[1], "r");

        // check for error when opening source
        if (f1 == NULL) {
            printf("Error opening source file.\n");
            exit(EXIT_FAILURE);
        } /*else {  // comfirm to user source opened
            printf("Source file opened.\n");
        }*/

        char buffer[BUFFER_SIZE];
        ssize_t bytes_read;  // cannot declare this in while loop

        // read from source file and write to pipe
        while ((bytes_read = fread(buffer, sizeof(char), BUFFER_SIZE, f1)) > 0) {  // checks if bytes are to be read, returns 0 if EOF, or error
            if (write(fd[WRITE_END], buffer, bytes_read) == -1) {
                printf("Could not write from source file to pipe.");
                exit(EXIT_FAILURE);
            } 
        }
        // NOTE: you only need to write once, checking for error also writes to pipe either way

        //printf("Parent process done.\n");
        fclose(f1);
        close(fd[WRITE_END]);
        wait(NULL);  // waiting on child process to finish
    }

    return 0;
}
