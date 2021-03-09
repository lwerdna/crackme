#include <windows.h>

#include <stdio.h>

#include "bitvects.h"
#include "random.h"

Vect::Vect()
{
    hi=lo=0;
}

Vect::Vect(UINT64 a)
{
    hi=0;
    lo=a;
}

Vect::Vect(UINT64 a, UINT64 b)
{
    hi=a;
    lo=b;
}

BOOL Vect::IsZero()
{
    return (hi==0 && lo==0);
}

VOID Vect::Zero()
{
    hi=0;
    lo=0;
}

VOID Vect::Xor(Vect a)
{
    hi ^= a.hi;
    lo ^= a.lo;
}

VOID Vect::And(Vect a)
{
    hi &= a.hi;
    lo &= a.lo;
}

VOID Vect::Random()
{
    InitRandom();
    GetRandom(&lo);
    GetRandom(&hi);
}

bool Vect::operator==(const Vect &other) const 
{
    return (other.lo == lo) && (other.hi == hi); 
}

const Vect Vect::operator+(const Vect &other) const 
{
    Vect result = *this;
    result.lo ^= other.lo;
    result.hi ^= other.hi;
    return result;
}

const Vect Vect::operator&(const Vect &other) const
{
    Vect result = *this;
    result.lo &= other.lo;
    result.hi &= other.hi;
    return result; 
}

const Vect Vect::operator|(const Vect &other) const
{
    Vect result = *this;
    result.lo |= other.lo;
    result.hi |= other.hi;
    return result; 
}

bool Vect::operator!=(const Vect &other) const 
{
    return !(*this == other);
}

VOID Vect::Shl()
{
    hi <<= 1;

    if(lo & 0x8000000000000000)
        hi |= 1;

    lo <<= 1;
}

VOID Vect::Shr()
{
    lo >>= 1;

    if(hi & 1)
        lo |= 0x8000000000000000;

    hi >>= 1;
}

BYTE Vect::Bit(UINT n)
{
    UINT64 src = lo;

    if(n >= 64)
    {
        src = hi;
        n-=64;
    }

    if(src & (((UINT64)1) << n))
        return 1;

    return 0;
}

VOID Vect::SetBit(UINT n)
{
    UINT64 *src = &lo;

    if(n >= 64)
    {
        src = &hi;
        n-=64;
    }

    *src |= (UINT64)1 << n;
}

VOID Vect::ClearBit(UINT n)
{
    UINT64 *src = &lo;

    if(n >= 64)
    {
        src = &hi;
        n-=64;
    }

    UINT64 mask = 0xFFFFFFFFFFFFFFFF;
    mask ^= ((UINT64)1 << n);
    *src &= mask;
}

VOID Vect::SwapBits(UINT a, UINT b)
{
    BYTE bitA = Bit(a);
    BYTE bitB = Bit(b);

    if(bitA == bitB)
        return;

    if(bitA)
        SetBit(b);
    else
        ClearBit(b);

    if(bitB)
        SetBit(a);
    else
        ClearBit(a);
}

VOID Vect::SetBitTo(UINT n, CHAR value)
{
    if(value)
        SetBit(n);
    else
        ClearBit(n);
}

INT Vect::CountBits()
{
    INT count=0;

    for(INT i=0; i<128; ++i)
        if(Bit(i))
            count++;

    return count;
}

UINT Vect::GetFirstBitSetPosition()
{
    for(INT i=127; i>=0; --i)
        if(this->Bit(i))
            return i;

    return -1;
}

VOID Vect::Print()
{
    printf("%016I64X, %016I64X ", hi, lo);
}

VOID Vect::Print(PCHAR name)
{
    printf("%s: ", name);
    Println();
}

VOID Vect::Println()
{
    Print();
    printf("\n");
}

VOID Vect::PrintPari()
{
    printf("v = [");
    for(INT j=127; j>=0; --j)
    {
        if(Bit(j))
            printf("1");
        else
            printf("0");

        if(j!=0)
            printf(",");
        else
            printf("];\n");
    }
}

BitBasis::BitBasis()
{
    dimension=0;
}

VOID BitBasis::Print(PCHAR name)
{
    printf("UINT64 %s_vects[%d] = { // dimension: %d\n", name, 2*dimension, dimension); // each 128 bit vector is 2x 64-bit
    for(INT i=0; i<dimension; ++i)
        printf("0x%016I64X, 0x%016I64X, \n", vects[i].hi, vects[i].lo);
    printf("};\n");
    printf("BitBasis %s;\n", name);
    printf("%s.AddN(%s_vects, %d);\n\n", name, name, dimension);
}

VOID BitBasis::PrintPari(PCHAR name)
{
    printf("%s = [ \\\n", name);

    for(INT i=0; i<dimension; ++i)
    {
        for(INT j=127; j>=0; --j)
        {
            if(vects[i].Bit(j))
                printf("1");
            else
                printf("0");

            if(j==0)
            {
                if(i!=(dimension-1))
                    printf("; \\\n");
                else
                    printf("\\\n");
            }
            else
                printf(",");

        }
    }

    printf("];\n");
}

VOID BitBasis::Print()
{
    Print("BASISNAME");
}

Vect BitBasis::SpanRandom()
{
    Vect temp;
    temp.Random();

    Vect result;

    for(INT i=0; i<dimension; ++i)
        if(temp.Bit(i))
            result.Xor(vects[i]);

    return result;
}

VOID BitBasis::SpanAllInit()
{
    span_i = 0;

    span_i_limit = 1;

    for(INT i=0; i<dimension; ++i)
        span_i_limit *= 2;
}

BOOL BitBasis::SpanAllNext(Vect *a)
{
    if(span_i >= span_i_limit)
        return 0;

    a->lo = 0;
    a->hi = 0;

    for(UINT64 i=0; i<dimension; ++i)
       if(span_i & (1<<i))
           a->Xor(vects[i]);

    span_i++;

    return 1;
}

VOID BitBasis::AddFast(Vect a)
{
    if(a.IsZero())
        return;

    // k this thing has to be as fast as fucking possible
    // keep updated table of setbit lookups
    // don't sort into eschelon

    // y = setbit_to_vector[x] -> vects[y] is where bit x is set
    BYTE setbit_to_vector[128];
    memset(setbit_to_vector, 0xFF, 128);
    for(INT i=0; i<dimension; ++i)
        setbit_to_vector[vects[i].GetFirstBitSetPosition()] = i; 

    for(INT i=127; i>=0; i--)
    {
        // if bit is set in other vector

        // if bit is set in new guy
        if(a.Bit(i))
        {
            INT vect_i = setbit_to_vector[i];

            // if another vector has this bit set
            if(vect_i != 0xFF)
            {
                // add that other vector
                //printf("xoring %016I64X with %016I64X ", a.lo, vects[vect_i].lo);
                a.Xor(vects[vect_i]);
                //printf("result: %016I64X\n", a.lo);
                // if that makes new guy 0, we're done
                if(!a.lo && !a.hi)
                    return;
            }
        }
    }

    vects[dimension++]=a;
}

VOID BitBasis::Add(Vect a)
{
    if(a.IsZero())
        return;
    vects[dimension++] = a;
    RowReduce();
}

VOID BitBasis::AddFast(UINT64 a, UINT64 b)
{
    AddFast(Vect(a,b));
}

VOID BitBasis::Add(UINT64 a, UINT64 b)
{
    Add(Vect(a,b));
}

VOID BitBasis::AddN(PUINT64 p, UINT n)
{
    while(n--)
    {
        Add(*p, *(p+1));
        p+=2;
    }
}

BOOL BitBasis::DoesSpan(Vect a)
{
    // y = setbit_to_vector[x] -> vects[y] is where bit x is set
    BYTE setbit_to_vector[128];
    memset(setbit_to_vector, 0xFF, 128);
    for(INT i=0; i<dimension; ++i)
        setbit_to_vector[vects[i].GetFirstBitSetPosition()] = i; 

    for(INT i=127; i>=0; i--)
    {
        // if bit is set in new guy
        if(a.Bit(i))
        {
            INT vect_i = setbit_to_vector[i];

            // if another vector has this bit set
            if(vect_i != 0xFF)
                a.Xor(vects[vect_i]);
            else
                break;
        }
    }

    return a.IsZero();
}

Vect BitBasis::SolveRowsFor(Vect target)
{
    Vect t;

    // assumes independent vectors entered!!

    // make transpose
    //
    BitBasis transp;
    for(INT i=127; i>=0; --i)       // every bit
    {
        t.lo=t.hi=0;
         
        for(INT j=0; j<128; ++j)    // every row
        {
            if(vects[j].Bit(i))
            {
                t.SetBit(127-j);
            }
        }

        transp.vects[transp.dimension++]=t;
    }

    //transp.Print("trans");

    INT next_insert = 0;

    // for every bit position
    for(INT i=127; i>=0; --i)
    {
        // find pivot
        INT j;
        for(j=next_insert; j<128; ++j)
            if(transp.vects[j].Bit(i))
                break;

        if(j>=128)
            continue;

        // place into position
        t = transp.vects[next_insert];
        transp.vects[next_insert] = transp.vects[j];
        transp.vects[j] = t;

        target.SwapBits(127-next_insert, 127-j);

        // apply pivot to other rows, when necessary
        for(j=0; j<128; ++j)
        {
            if(j!=next_insert && transp.vects[j].Bit(i))
            {
                transp.vects[j].Xor(transp.vects[next_insert]);

                target.SetBitTo(127-j, target.Bit(127-j) ^ target.Bit(127-next_insert));
            }
        }

        // continue;
        next_insert++;
    }

    return target;
}

Vect BitBasis::ChooseRows(Vect a)
{
    Vect result;

    for(INT i=0; i<128; ++i)
    {
        if(a.Bit(127-i))
        {
            result.Xor(vects[i]);
        }
    }

    return result;
}

VOID BitBasis::Join(BitBasis b)
{
    for(INT i=0; i<b.dimension; i++)
        vects[dimension++] = b.vects[i];
//        AddFast(b.vects[i]);
}

VOID BitBasis::RowReduce()
{
    INT curr_row = 0;

    // for each coefficient in the vects
    for(INT coeff=127; (coeff>=0) && (curr_row < dimension); --coeff)
    {
        // hunt first equation with nonzero coeff
        INT pivot=-1;
        for(INT i=curr_row; i<dimension; ++i)
            if(vects[i].Bit(coeff))
            {
                pivot=i;
                break;
            }
        if(pivot==-1)
            continue;

        // swap pivot into position
        //printf("pivot at: %d\n", pivot);

        Vect temp = vects[pivot];
        vects[pivot] = vects[curr_row];
        vects[curr_row] = temp;

        // for any remaining row with <coeff> bit set, xor with pivot
        for(INT i=curr_row+1; i<dimension; ++i)
            if(vects[i].Bit(coeff))
                vects[i].Xor(vects[pivot]);

        // 
        curr_row++;
    }

    // collapse all zero vects
    // 
    BOOL bRescan;

    for(INT i=0; i<dimension; )
    {
        bRescan=0;

        if(vects[i].IsZero())
        {
            bRescan=1;
            for(INT j=i; j<dimension; ++j)
                vects[j] = vects[j+1];
            vects[dimension]=Vect(0);
        }

        if(!bRescan)
            break;
        else
            i++;
    }

    // recount the vects
    //
    for(dimension=0; dimension<256; ++dimension)
        if(vects[dimension].IsZero())
            break;

    //printf("dimension reset to: %d\n", dimension);
}


