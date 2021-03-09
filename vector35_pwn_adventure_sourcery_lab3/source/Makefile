all: keyme

main.o: main.s
	nasm main.s -f elf32 -o main.o

parse.o: parse.s
	nasm parse.s -f elf32 -o parse.o

xtea.o: xtea.s
	nasm xtea.s -f elf32 -o xtea.o

keyme: main.o parse.o xtea.o
	ld -m elf_i386 main.o parse.o xtea.o -o keyme

clean:
	rm *.o keyme
