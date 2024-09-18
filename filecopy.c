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

#define READ_END 0
#define WRITE_END 1

int main(int argc, char *argv[])
{
	if (argc != 3) //Checks if there more or less than 2 parameter
	{
		cout <<"Please enter 2 parameters: " << endl;
		cout <<"	Parameter 1: source file"<< endl;
		cout <<"	parameter 2: destination file"<< endl;
		exit(EXIT_SUCCESS);
	}
	return 0;
	/*
	Your code is here
	*/
}
