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
	if (argc != 3) { // Checks if there more or less than 2 parameter 
		printf("Please enter 2 parameters:\n");
		printf("Parameter 1: Source file.\n");
		printf("Parameter 2: Destination file.\n");
        printf("Example: filecopy source.txt destination.txt\n");
		exit(EXIT_SUCCESS);
	}


    // Understanding arguments
    printf("argc: %d\n", argc);
    
    printf("argv[0]=%s\n", argv[0]);
    printf("argv[1]=%s\n", argv[1]);
    printf("argv[2]=%s\n", argv[2]);
    

    // Reading from file, displaying to terminal
    FILE *fh;
    fh = fopen(argv[1], "r");

    if (fh != NULL) { // check if there is an error
        char c;
        while ((c = fgetc(fh)) != EOF) { // fgetc takes in a fh, return each char in sequence each time its called
            putchar(c); // take that char and display to terminal
        }
        fclose(fh);
    } else {
        printf("Error opening file.\n");
    }

    // Write file
    FILE *fh2;

    fh2 = fopen(argv[2], "w");

    fputs("A text to input into destination file\n", fh2);
    
    fclose(fh2);

	return 0;
}
