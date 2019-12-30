CC = gcc # Compiler to use
OPTIONS = -O2 -g -Wall  # -g for debug, -O2 for optimise and -Wall additional messages
INCLUDES = -I . # Directory for header file
OBJS = poker # List of objects to be build
.PHONY: all clean # To declare all, clean are not files

all: ${OBJS}

${OBJS}: poker.c
	@echo "Building.." # To print "Building.." message
	${CC} ${OPTIONS} ${INCLUDES} -o ${OBJS} poker.c
 
clean:
	@echo "Cleaning up.."
	rm -rf *.o # - prefix for ignoring errors and continue execution
	rm -rf poker
