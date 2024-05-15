compiler = pacl
grapher = grapher


compiler_sources = $(wildcard src/compiler/*.c)
grapher_sources = $(wildcard src/grapher/*.c)

compiler_objects = $(compiler_sources:.c=.o)
grapher_objects = $(grapher_sources:.c=.o)

flags = -g -Wall

all: compiler grapher

clean:
	-rm bin/*
	-rm ./**//**/*.o

compiler: $(compiler_objects)
	gcc $(compiler_objects) $(flags) -o bin/$(compiler)
	xxd -b bin/$(compiler) >> bin/$(compiler).txt

grapher: $(grapher_objects)
	gcc $(grapher_objects) $(flags) -o bin/$(grapher)
	xxd -b bin/$(grapher) >> bin/$(grapher).txt

%.o: %.c include/%.h 
	gcc -c $(flags) $< -o $@

install:
	make
	cp bin/pacl /usr/local/bin/pacl
