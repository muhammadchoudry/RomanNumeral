#Relevant directories
SRC_DIR = ./src
INC_DIR = ./include
BIN_DIR = ./bin
LIB_DIR = ./lib
OBJ_DIR = ./obj
TEST_DIR = ./test

#The includes
INCLUDES = -I $(INC_DIR)
LIBRARIES = -L $(LIB_DIR)

# the compiler: gcc for C program, define as g++ for C++
CC = gcc

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g -Wall

all: RomanCalculator TestAdd testsuite

#Create a static library for RomanCalculator
RomanCalculator:
	$(CC) $(CFLAGS) -c -o $(OBJ_DIR)/RomanCalculator.o $(SRC_DIR)/RomanCalculator.c
	ar rs $(LIB_DIR)/libromancalculator.a $(OBJ_DIR)/RomanCalculator.o

#Create a test application 
TestAdd:
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBRARIES) -o $(BIN_DIR)/TestAdd $(SRC_DIR)/TestAdd.c lib/libromancalculator.a
	
#Create a test application 
testsuite:
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBRARIES) -o $(BIN_DIR)/testsuite $(TEST_DIR)/testsuite.c lib/libromancalculator.a `pkg-config --cflags --libs check`

#Clean command
clean:
	-rm $(BIN_DIR)/*
	-rm $(LIB_DIR)/*
	-rm $(OBJ_DIR)/*

#Print variables for debugging purposes
print-%:
	@echo $*=$($*)