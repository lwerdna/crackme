#include <windows.h>
#include <stdio.h>

void getorder(UINT inp, UINT out[21])
{
    UINT outi=0;
    UINT arr[21]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
    for(INT i=21; i>=1; --i)
    {
        /*
        printf("array: ");
        for(INT j=0; j<i; ++j)
            printf("%02X ", arr[j]&0xFF);
        printf("\n");
        */

        INT src=inp % i;
        //printf("retrieving array[(%08X %% %02X) == %02X] == %02X\n",inp,i,src,arr[src]);
        //printf("---\n");
        out[outi++]=arr[src];
        memcpy(arr+src, arr+src+1, (i-src)*4);
    }
}

int main(int ac, PCHAR *av)
{
    for(UINT i=0x0; i<0xFFFFFFFF; ++i)
    {
        UINT order[21];
        getorder(i, order);
        
        /*
        printf("order: ");
        for(INT i=0; i<21; ++i)
            printf("%02X,", order[i]);
        printf("\n");
        */

        if( order[0]==0 &&
            (order[0x02]==0x12 || order[0x02]==0x10) &&
            (order[0x0A]==0x12 || order[0x0A]==0x10) &&
            order[0x04]==0x14 &&
            order[0x07]==0x0b &&
            order[0x0D]==0x03 &&
            order[0x11]==0x0a && 
            order[0x13]==0x13
        )
        {
            printf("%08X passes! ", i);

            printf("or: ");
            for(INT i=0; i<21; ++i)
                printf("%02X,", order[i]);
            printf("\n"); 
        }

        if(!(i & 0xFFFFFF))
            printf("on: %08X\n", i);
    }
}
