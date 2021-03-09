// keygen to EasyCrack by Kwazy Webbit
// 8/28/2007 andrewl
//
#include <stdio.h>

int main(int argc, char * argv[])
{
    int i = 0;
    unsigned int runner = 0;

    int key = 0;

    if(argc < 2)
    {
        printf("supply name\n");
        return -1;
    }

    for(i=0; i<strlen(argv[1]); ++i)
    {
        runner += argv[1][i];
       
// my friend Ilkhom thought of much more interesting way to implement rol:
//
// // __asm {rol hash, 1} ;
// hash = ((unsigned)hash << 1) | !!((unsigned)hash & (1 << 31)) ;
//
//
// and Rossignol from #c4n implements it with variable rotation arg:
//
// unsigned long rol (unsigned long iNum, int n = 1)
// {
//	return (iNum << n) | (iNum >> (8 * sizeof(iNum) - n)); 
// }

        if(runner & 0x80000000)
            runner = runner * 2 + 1;
        else
            runner = runner * 2;

        runner *= argv[1][i];
        runner += argv[1][i];
        runner ^= argv[1][i];
    }

    printf("runner: 0x%x\n", runner);

    key = (~runner + 0xBADC0DE5)^(0x1337C0DE);

//    printf("key before: 0x%x\n", key);

//    printf("key stage 1: 0x%x\n", key ^ 0x1337C0DE);
//    printf("key stage 2: 0x%x\n", (key ^ 0x1337C0DE) - 0x0BADC0DE5);
//    printf("key stage 3: 0x%x\n", ~((key ^ 0x1337C0DE) - 0x0BADC0DE5));

    printf("Your key is %u\n", key);

    return 0;
}
