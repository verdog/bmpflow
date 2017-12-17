# Compiler
CC = g++

# object file directory
ODIR = obj

# .o dependancies
_OBJ = $(ODIR)/bmpflow.o $(ODIR)/EasyBMP.o

all: bmpflow

bmpflow: $(_OBJ)
	$(CC) -o $@ $^

$(ODIR)/bmpflow.o: bmpflow.cpp
	$(CC) -g -c -o $@ $^ -Wall

$(ODIR)/EasyBMP.o: EasyBMP_1.06/EasyBMP.cpp
	$(CC) -c -o $@ $^

clean:
	rm $(ODIR)/*.o bmpflow
