default: # Default make, explains the steps (NOTE: @ removes the echo, just shows string)
	@echo "This make file can run via following commands:"
	@echo "make compile		# Compiles program"
	@echo "make showI		# Runs cat on input.txt"
	@echo "make exec		# Runs exec with input.txt and output.txt"
	@echo "make showO		# Runs cat on output.txt"
	@echo "make clean		# Runs rm on filecopy and output.txt"
	@echo "make main		# Runs all commands"

compile:  # Compile the program
	gcc filecopy.c -o filecopy        

showI:  # Show the contents of input.txt
	cat input.txt  

exec:  # Execute the compiled program
	./filecopy input.txt output.txt

showO:  # Show the contents of output.txt
	cat output.txt                 

clean:   # Remove the executable and output file
	rm -f filecopy output.txt

main: compile showI exec showO clean  # Run all steps      
