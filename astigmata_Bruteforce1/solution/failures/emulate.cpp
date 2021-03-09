// 2008 andrewl

#include <windows.h>

#include <stdio.h>

DWORD rcr_c_rcr(DWORD x, BYTE n, BYTE cf)
{
    BYTE new_cf;

    __asm
    {
        pushf;
        mov cl, [cf];
        rcr cl, 1;
        mov cl, [n];
        mov eax, [x];
        rcr eax, cl;
        mov [x], eax;
        popf;
    }

    return x;
}

__declspec(naked) DWORD rcr_asm_shifts(DWORD x, BYTE n, BYTE cf)
{
    __asm
    {
        mov eax, [esp+4]            // input
        mov cl, [esp+8]             // amount to rotate
        mov ch, [esp+0x0C]          // carry flag state

        and cl, 0x1F                // mod 32
        jz  e

        // right side
        mov esi, eax 
        shr esi, cl

        neg cl     
        add cl, 32              // cl = 32 - shift amount

        // slide carry
        movzx edi, ch
        shl edi, cl
        
        or esi, edi
        mov edi, eax
        mov eax, esi

        add cl, 1               // cl = 33 - shift amount
        cmp cl, 31
        ja  e

        // left side
        shl edi, cl
        or eax, edi

    e:  ret
    }
}

__declspec(naked) DWORD crackme(DWORD inp)
{
    __asm
    {
            clc
            mov     eax, [esp+4]
            xor     ebx, ebx
            mov     ecx, 0x5F5E100
        agn:
            push    ecx
            mov     cl, al
            rcr     eax, cl
            add     eax, ebx
            add     eax, 0x11223344
            xchg    eax, ebx
            pop     ecx
            dec     ecx
            jne     agn

            xor     eax, ebx
            ret
    }
}

__declspec(naked) DWORD crackme_noxchg(DWORD inp)
{
    __asm
    {
            clc
            mov     eax, [esp+4]
            xor     ebx, ebx
            mov     ecx, 0x2FAF080
        agn:
            push    ecx

            mov     cl, al
            rcr     eax, cl
            add     eax, ebx
            add     eax, 0x11223344

            mov     cl, bl
            rcr     ebx, cl
            add     ebx, eax
            add     ebx, 0x11223344

            pop     ecx
            dec     ecx
            jne     agn

            xor     eax, ebx
            ret
    }
}

__declspec(naked) DWORD crackme_noxchg_nopush(DWORD inp)
{
    __asm
    {
            clc
            mov     eax, [esp+4]
            xor     ebx, ebx
            mov     edx, 0x2FAF080
        agn:
            mov     cl, al
            rcr     eax, cl
            add     eax, ebx
            add     eax, 0x11223344

            mov     cl, bl
            rcr     ebx, cl
            add     ebx, eax
            add     ebx, 0x11223344

            dec     edx
            jne     agn

            xor     eax, ebx
            ret
    }
}

__declspec(naked) DWORD crackme_noxchg_nopush_unrolled(DWORD inp)
{
    // need 50,000,000 of these
    #define BODY            __asm \
                            { \
                            __asm   mov     cl, al \
                            __asm   rcr     eax, cl \
                            __asm   add     eax, ebx \
                            __asm   add     eax, 0x11223344 \
                            __asm   mov     cl, bl \
                            __asm   rcr     ebx, cl \
                            __asm   add     ebx, eax \
                            __asm   add     ebx, 0x11223344 \
                            }

    // or 25,000,000 of these
    #define BODY2 BODY \
                    BODY

    // or 12,500,000 of these
    #define BODY4 BODY2 \
                    BODY2

    // or 6,250,000 of these
    #define BODY8 BODY4 \
                    BODY4

    // or 3,125,000 of these
    #define BODY16 BODY8 \
                    BODY8

    // or 1,562,500 of these
    #define BODY32 BODY16 \
                    BODY16

    // or 781,250 of these
    #define BODY64 BODY32 \
                    BODY32

    // or 390,625 of these
    #define BODY128 BODY64 \
                    BODY64



    __asm
    {
            clc
            mov     eax, [esp+4]
            xor     ebx, ebx
            mov     edx, 390625
        agn:
    }


            BODY128

    __asm
    {
            dec     edx
            jne     agn

            xor     eax, ebx
            ret
    }
}

unsigned long emulate_c(unsigned long inp)
{
    unsigned long i;
    unsigned long CF;
    unsigned long eax;
    unsigned long ebx;
    unsigned long shamt;

    CF = 0;
    eax = inp;
    ebx = 0;

    for(i=0; i<100000000; ++i)
    {
        // emulate RCR EAX, AL

        if((eax ^ ebx) == 0x3FF9CF26)
            __asm int 3;

        shamt = eax & 0x1F;

        if(shamt)
        {
            unsigned long left = 0, right, ceffect;

            right = eax >> shamt;

            shamt = 32 - shamt;
            ceffect = CF << shamt;

            if(++shamt < 32)
                left = eax << shamt;
            
            eax = left | ceffect | right;          
        }

        eax += ebx;
        eax += 0x11223344;

        CF = 0;
        if(eax < 0x11223344)
            CF = 1;

        eax ^= ebx;
        ebx ^= eax;
        eax ^= ebx;
    }

    return eax ^ ebx;
}

//
// this is an attempt to make a function to emulate the
// crackme without using RCR and the carry flag (which PTX
// does not provide)
//
__declspec(naked) DWORD emulate(DWORD inp)
{
    __asm
    {
            mov     eax, [esp+4]
            xor     ebx, ebx
            mov     edx, 0x5F5E100
            clc
        agn:    
            // RCR
            mov     cl, al
            and     cl, 0x1F
            jz      krcr
            mov     esi, eax 
            shr     esi, cl
            neg     cl     
            add     cl, 32         
            movzx   edi, ch
            shl     edi, cl
            or      esi, edi
            mov     edi, eax
            mov     eax, esi
            add     cl, 1          
            cmp     cl, 31
            ja      krcr
            shl     edi, cl
            or      eax, edi

        krcr:
            add     eax, ebx
            add     eax, 0x11223344
           
            // CH = virtual CF
            jc      scf
            xor     ch, ch
            jmp     dcf
        scf:
            mov     ch, 1
        dcf:

            xchg    eax, ebx
            dec     edx
            jnz     agn

            xor     eax, ebx
            ret
    }
}

__declspec(naked) DWORD emulate_noxchg(DWORD inp)
{
    __asm
    {
            mov     eax, [esp+4]
            xor     ebx, ebx
            mov     edx, 0x2FAF080
            clc
        agn:    
            // RCR
            mov     cl, al
            and     cl, 0x1F
            jz      krcr0
            mov     esi, eax 
            shr     esi, cl
            neg     cl     
            add     cl, 32         
            movzx   edi, ch
            shl     edi, cl
            or      esi, edi
            mov     edi, eax
            mov     eax, esi
            add     cl, 1          
            cmp     cl, 31
            ja      krcr0
            shl     edi, cl
            or      eax, edi

        krcr0:
            add     eax, ebx
            add     eax, 0x11223344

            // CH = virtual CF
            jc      scf0
            xor     ch, ch
            jmp     dcf0
        scf0:
            mov     ch, 1
        dcf0:

            // RCR
            mov     cl, bl
            and     cl, 0x1F
            jz      krcr1
            mov     esi, ebx 
            shr     esi, cl
            neg     cl     
            add     cl, 32         
            movzx   edi, ch
            shl     edi, cl
            or      esi, edi
            mov     edi, ebx
            mov     ebx, esi
            add     cl, 1          
            cmp     cl, 31
            ja      krcr1
            shl     edi, cl
            or      ebx, edi

        krcr1:
            add     ebx, eax
            add     ebx, 0x11223344
           
            // CH = virtual CF
            jc      scf1
            xor     ch, ch
            jmp     dcf1
        scf1:
            mov     ch, 1
        dcf1:

            dec     edx
            jnz     agn

            xor     eax, ebx
            ret
    }
}

void main(void)
{
    DWORD r0, r1, r2, r3;

    DWORD trials[8] = {0xDEADBEEF, 0xCAFEBABE, 0x23fb18c0, 0x03fb2d04, 0x51515151, 0x08715109, 0x66600066, 0xFFFFFFFF};

    FILETIME t0, t1;

    emulate_c(0xDEADBEEF);
    printf("hi\n");

    //
    // test that the RCR implemented with shifts is equivalent to
    // the real RCR
    //
    if(0)
    {
        for(int i=0; i<8; ++i)          // over each trial
            for(int j=0; j<2; ++j)      // over each carry flag
                for(int k=0; k<256; ++k) // over each shift amount
                {
                    r0 = rcr_asm_shifts(trials[i], k, j);
                    r1 = rcr_c_rcr(trials[i], k, j);
    
                    if(r0 != r1)
                    {
                        printf("failed on 0x%08X shamt=%d CF=%d\n", trials[i], k, j);
                        goto quit;
                    }
                }
    }

    //
    // test that the emulated crackme implemented with shifts is
    // equivalent to the real crackme code
    //
    if(0)
    {
        for(int i=0; i<8; ++i)
        {
            //r0 = emulate(trials[i]);
            r1 = crackme(trials[i]);
            //r2 = crackme_noxchg(trials[i]);
            //r3 = emulate_noxchg(trials[i]);

            /*
            if(r0 != r1)
            {
                printf("non-equivalent crackme() behavior on %08X", trials[i]);
                goto quit;
            }

            if(r2 != r1)
            {
                printf("non-equivalent crackme_noxchg() behavior on %08X", trials[i]);
                goto quit;
            }

            if(r3 != r1)
            {
                printf("non-equivalent emulate_noxchg() behavior on %08X", trials[i]);
                goto quit;
            }
            */

            /*
            r3 = crackme_noxchg_nopush(trials[i]);
            if(r3 != r1)
            {
                printf("non-equivalent emulate_noxchg_nopush() behavior on %08X", trials[i]);
                goto quit;
            }
            */
           
            /*
            r3 = crackme_noxchg_nopush_unrolled(trials[i]);
            if(r3 != r1)
            {
                printf("non-equivalent emulate_noxchg_nopush() behavior on %08X", trials[i]);
                goto quit;
            }
            */

            r3 = emulate_c(trials[i]);
            if(r3 != r1)
            {
                printf("non-equivalent emulate_c() behavior on %08X", trials[i]);
                goto quit;
            }
        }
    }

    //
    // clock the time taken to do 100 crackme trials
    //
    if(1)
    {
        DWORD trials = 10;

        // time crackme()
        GetSystemTimeAsFileTime(&t0);

        for(int i=0; i<trials; ++i)
            crackme(i);

        GetSystemTimeAsFileTime(&t1);

        ULONGLONG s1 = ((ULONGLONG)t1.dwHighDateTime << 32) | t1.dwLowDateTime;
        ULONGLONG s0 = ((ULONGLONG)t0.dwHighDateTime << 32) | t0.dwLowDateTime;
        ULONGLONG diff = (s1 - s0);
        float difff = diff / (float)10000000;
        printf("crackme() took %f seconds, meaning %f seconds per trial\n", difff, difff/(float)trials);

        // time emulate()
        GetSystemTimeAsFileTime(&t0);

        for(int i=0; i<trials; ++i)
            emulate(i);

        GetSystemTimeAsFileTime(&t1);

        s1 = ((ULONGLONG)t1.dwHighDateTime << 32) | t1.dwLowDateTime;
        s0 = ((ULONGLONG)t0.dwHighDateTime << 32) | t0.dwLowDateTime;
        diff = (s1 - s0);
        difff = diff / (float)10000000;
        printf("emulate() took %f seconds, meaning %f seconds per trial\n", difff, difff/(float)trials);

        // time crackme_noxchg()
        GetSystemTimeAsFileTime(&t0);

        for(int i=0; i<trials; ++i)
            crackme_noxchg(i);

        GetSystemTimeAsFileTime(&t1);

        s1 = ((ULONGLONG)t1.dwHighDateTime << 32) | t1.dwLowDateTime;
        s0 = ((ULONGLONG)t0.dwHighDateTime << 32) | t0.dwLowDateTime;
        diff = (s1 - s0);
        difff = diff / (float)10000000;
        printf("crackme_noxchg() took %f seconds, meaning %f seconds per trial\n", difff, difff/(float)trials);

        // time emulate_noxchg()
        GetSystemTimeAsFileTime(&t0);

        for(int i=0; i<trials; ++i)
            emulate_noxchg(i);

        GetSystemTimeAsFileTime(&t1);

        s1 = ((ULONGLONG)t1.dwHighDateTime << 32) | t1.dwLowDateTime;
        s0 = ((ULONGLONG)t0.dwHighDateTime << 32) | t0.dwLowDateTime;
        diff = (s1 - s0);
        difff = diff / (float)10000000;
        printf("emulate_noxchg() took %f seconds, meaning %f seconds per trial\n", difff, difff/(float)trials);

        // time crackme_noxchg_nopush()
        GetSystemTimeAsFileTime(&t0);

        for(int i=0; i<trials; ++i)
            crackme_noxchg_nopush(i);

        GetSystemTimeAsFileTime(&t1);

        s1 = ((ULONGLONG)t1.dwHighDateTime << 32) | t1.dwLowDateTime;
        s0 = ((ULONGLONG)t0.dwHighDateTime << 32) | t0.dwLowDateTime;
        diff = (s1 - s0);
        difff = diff / (float)10000000;
        printf("crackme_noxchg_nopush() took %f seconds, meaning %f seconds per trial\n", difff, difff/(float)trials);

        // time crackme_noxchg_nopush()
        GetSystemTimeAsFileTime(&t0);

        for(int i=0; i<trials; ++i)
            crackme_noxchg_nopush_unrolled(i);

        GetSystemTimeAsFileTime(&t1);

        s1 = ((ULONGLONG)t1.dwHighDateTime << 32) | t1.dwLowDateTime;
        s0 = ((ULONGLONG)t0.dwHighDateTime << 32) | t0.dwLowDateTime;
        diff = (s1 - s0);
        difff = diff / (float)10000000;
        printf("crackme_noxchg_nopush_unrolled() took %f seconds, meaning %f seconds per trial\n", difff, difff/(float)trials);

        // time emulate_c()
        GetSystemTimeAsFileTime(&t0);

        for(int i=0; i<trials; ++i)
            emulate_c(i);

        GetSystemTimeAsFileTime(&t1);

        s1 = ((ULONGLONG)t1.dwHighDateTime << 32) | t1.dwLowDateTime;
        s0 = ((ULONGLONG)t0.dwHighDateTime << 32) | t0.dwLowDateTime;
        diff = (s1 - s0);
        difff = diff / (float)10000000;
        printf("emulate_c() took %f seconds, meaning %f seconds per trial\n", difff, difff/(float)trials);

    }

    quit:
    __asm nop
}
