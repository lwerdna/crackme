./genxtea.py 372 > xtea_wb.c
gcc -Os -c xtea_wb.c -o xtea_wb.o
objdump -M intel -d ./xtea_wb.o
objdump -M intel -d ./xtea_wb.o | ./rip.py xtea > ~/Downloads/challenge/xtea.s
