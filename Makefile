CC = gcc

SRC_DIR = src
LOG_DIR = logs
BUILD_DIR = build
BIN_DIR = bin

EXEC = $(BIN_DIR)/pacl
LOGS = $(wildcard $(LOG_DIR)/*.txt)

SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(SOURCES:$(SRC_DIR)%.c=$(BUILD_DIR)%.o)

CFLAGS = -g -Og -Wall -Wextra -pedantic -fsanitize=address
LDFLAGS = -g -Og -Wall -Wextra -pedantic -fsanitize=address 

.PHONY: all clean install

all: $(EXEC) #ocaml

$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC) $(LDFLAGS)
	xxd -b $(EXEC) >> logs/pacl.txt

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c 
	$(CC) -c $< -o $@ $(CFLAGS)

#ocaml: 
#	ocamlc -o bin/pacl_ocaml src/ocaml/parser.ml
#	./bin/pacl_ocaml

install:
	make
	cp bin/pacl /usr/local/bin/pacl

test:
	./bin/pacl exampmles/test.pacl
test1:
	./bin/pacl examples/1_test.pacl
test2:
	./bin/pacl examples/2_test/pacl

clean:
	-rm $(EXEC)
	-rm $(OBJECTS)
	-rm $(LOGS)
	-rm c_out/*
	-rm out/*
