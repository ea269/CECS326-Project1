# Some varaibles for easier changing
CC = gcc
INPUT = input.txt
OUTPUT = output.txt
EXEC = filecopy

default: # Default make, explains the steps (NOTE: @ removes the echo, just shows string)
	@echo "This make file can run via following commands:"
	@echo "make compile		# Compiles program"
	@echo "make showI		# Runs cat on input.txt"
	@echo "make exec		# Runs exec with input.txt and output.txt"
	@echo "make showO		# Runs cat on output.txt"
	@echo "make clean		# Runs rm on filecopy and output.txt"
	@echo "make main		# Runs all commands"

compile:  # Compile the program
	$(CC) filecopy.c -o $(EXEC) 

showI:  # Show the contents of input.txt
	cat input.txt  

exec:  # Execute the compiled program (NOTE: $() is how you call variables, like javascript)
	./$(EXEC) $(INPUT) $(OUTPUT)

showO:  # Show the contents of output.txt
	cat $(OUTPUT)

clean:   # Remove the executable and output file
	rm -f $(EXEC) $(OUTPUT)

main: compile showI exec showO clean  # Run all steps      
