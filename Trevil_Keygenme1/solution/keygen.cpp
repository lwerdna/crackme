// 02/21/2009 andrewl
// keygen to Trevil's Keygenme #1

#include <stdio.h>
#include <string.h>

// exponentiation by squaring
unsigned int expmod(unsigned int b, unsigned int e, unsigned int n)
{
    unsigned long long temp;
    unsigned int answer=1;
    unsigned int runner=b;

    for(unsigned int i=0; e; ++i)
    {
        if(e & 1)
        {
            temp = (unsigned long long)answer * runner;
            answer = temp % n;
        }

        temp = (unsigned long long)runner * runner;
        runner = temp % n;
        e >>= 1;
    }

    return answer;
}

void main(int ac, char **av)
{
    char *name="Trevil";

    if(ac>1)
        name = av[1];

    printf("user: %s\n", name);
    printf("serial: ");
    for(int i=0; i<strlen(name); ++i)
    {
        unsigned int r = expmod(name[i], 78789071, 29201279);
        printf("%d", r);
    }
    printf("\n");
}

