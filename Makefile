#Relevant directories
LIB = lib
OBJ = obj

SRC_DIR = ./src
INC_DIR = ./include
BIN_DIR = ./bin
LIB_DIR = ./${LIB}
OBJ_DIR = ./${OBJ}
TEST_DIR = ./test

#The includes
INCLUDES = -I $(INC_DIR)
LIBRARIES = -L $(LIB_DIR)

#Debugmode
DEBUG = -DDEBUGMODE=1

# the compiler: gcc for C program, define as g++ for C++
CC = gcc

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g -Wall

all: RomanCalculator RomanCalculator_debug testsuite

#Create a static library for RomanCalculator
RomanCalculator:
	mkdir -p ${OBJ}
	mkdir -p ${LIB}
	$(CC) $(CFLAGS) -c -o $(OBJ_DIR)/RomanCalculator.o $(SRC_DIR)/RomanCalculator.c
	ar rs $(LIB_DIR)/libromancalculator.a $(OBJ_DIR)/RomanCalculator.o
	
RomanCalculator_debug:
	mkdir -p ${OBJ}
	mkdir -p ${LIB}
	$(CC) $(CFLAGS) -c -o $(OBJ_DIR)/RomanCalculator_debug.o $(SRC_DIR)/RomanCalculator.c $(DEBUG)
	ar rs $(LIB_DIR)/libromancalculator_debug.a $(OBJ_DIR)/RomanCalculator_debug.o
	
#Create a test suite
testsuite:
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBRARIES) -o $(BIN_DIR)/testsuite $(TEST_DIR)/testsuite.c lib/libromancalculator.a `pkg-config --cflags --libs check`

#Clean command
clean:
	-rm $(BIN_DIR)/testsuite
	-rm $(LIB_DIR)/*
	-rm $(OBJ_DIR)/*

#Print variables for debugging purposes
print-%:
	@echo $*=$($*)
