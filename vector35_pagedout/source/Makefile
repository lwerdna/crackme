.PHONY: all

all: poc_encrypt poc_decrypt chal_encrypt chal_decrypt challenge

challenge.o: challenge.asm
	nasm -f macho64 challenge.asm -o challenge.o

challenge: challenge.o
	ld -macosx_version_min 10.7.0 -lSystem challenge.o -o challenge

poc_encrypt.o: poc_encrypt.asm
	nasm -f macho64 poc_encrypt.asm -o poc_encrypt.o

poc_encrypt: poc_encrypt.o
	ld -macosx_version_min 10.7.0 -lSystem poc_encrypt.o -o poc_encrypt

poc_decrypt.o: poc_decrypt.asm
	nasm -f macho64 poc_decrypt.asm -o poc_decrypt.o

poc_decrypt: poc_decrypt.o
	ld -macosx_version_min 10.7.0 -lSystem poc_decrypt.o -o poc_decrypt

chal_encrypt.o: chal_encrypt.asm
	nasm -f macho64 chal_encrypt.asm -o chal_encrypt.o

chal_encrypt: chal_encrypt.o
	ld -macosx_version_min 10.7.0 -lSystem chal_encrypt.o -o chal_encrypt

chal_decrypt.o: chal_decrypt.asm
	nasm -f macho64 chal_decrypt.asm -o chal_decrypt.o

chal_decrypt: chal_decrypt.o
	ld -macosx_version_min 10.7.0 -lSystem chal_decrypt.o -o chal_decrypt
