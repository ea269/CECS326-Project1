# CECS326-Project1

A file-copying program named filecopy.c that utilizes ordinary pipes for inter-process communication.
The program when compiled will be passed two parameters:

- the name of the file to be copied
- the name of the destination file

However since it is a big process, you can you the Makefile.
To get started just enter 'make' into your terminal, to show the make commands.
Or follow these below:

# Compiles program

- make compile

# Runs cat on input.txt

- make showI

# Runs exec with input.txt and output.txt

- make exec

# Runs cat on output.txt

- make showO

# Runs rm on filecopy and output.txt

- make clean

# Runs all commands

- make main
