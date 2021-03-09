#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#ifndef M_PI
#define M_PI (acos(-1.0))
#endif

#define RANDOM (1 + rand() % 0x1E)

int main(int ac, char *av)
{
    srand(time(0));

    unsigned int dw1,dw2,dw3,dw4,dw5,dw6,dw7;

    dw1 = dw2 = RANDOM;
    dw3 = dw4 = RANDOM;
    dw6 = RANDOM;
    dw5 = dw6 + 90;
    dw7 = RANDOM;

    printf("%u-%u-%u-%u-%u-%u-%u\n", dw1, dw2, dw3, dw4, dw5, dw6, dw7);

    printf("ctrL+C to quit!\n");
    while(1);

    return 0;
}
