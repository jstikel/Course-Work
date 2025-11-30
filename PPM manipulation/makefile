#Josh Stikeleather
#CPSC 2310 002
#jstikel@clemson.edu

#This is our compiler and flags
CC=gcc
CFLAGS=-Wall -Wextra

#All object files needed for the final executable
OBJS=driver.o ppm.o shapes.o

#The default target
all: output

#links all object files into the final executable
output: $(OBJS)
	$(CC) $(CFLAGS) -o output $(OBJS) -lm

#compliation rules for each .c file
driver.o: driver.c ppm.h shapes.h
ppm.o: ppm.c ppm.h shapes.h
shapes.o: shapes.c shapes.h ppm.h

#Runs the program when you type "make run"
run: output
	./output

#Cleans the folder of all output and .o files
clean:
	rm -f *.o output output.ppm