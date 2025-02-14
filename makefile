COMPILER=gcc
COMPILER_FLAGS=-g
LINKING_FLAGS=-Os -s -fno-ident -fno-asynchronous-unwind-tables

BUILD_DIR=build
SRC_DIR=src
OBJ_DIR=obj

$(BUILD_DIR)/brainfuck: $(OBJ_DIR)/main.o $(OBJ_DIR)/brainfuck.o $(OBJ_DIR)/list.o
	$(COMPILER) $^ -o $@ $(LINKING_FLAGS)

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c
	$(COMPILER) -c $^ -o $@ $(COMPILER_FLAGS)

$(OBJ_DIR)/brainfuck.o: $(SRC_DIR)/brainfuck.c
	$(COMPILER) -c $^ -o $@ $(COMPILER_FLAGS)

$(OBJ_DIR)/list.o: $(SRC_DIR)/list.c
	$(COMPILER) -c $^ -o $@ $(COMPILER_FLAGS)

clean:
	rm -f main.o 
	rm -f brainfuck.o
	rm -f list.o 