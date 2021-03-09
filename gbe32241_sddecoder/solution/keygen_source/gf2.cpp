#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#include "bitvects.h"

// ********************************************************************************************
//
// GF(2) stuff
//
// ********************************************************************************************

Vect FieldAdd(Vect addend_a, Vect addend_b)
{
    return addend_a + addend_b;
}

Vect FieldMul(Vect multiplicand, Vect multiplier, Vect modulus)
{
    Vect result;

    // measure the degree of the modulus

    Vect d_mask(1);

    while((d_mask & modulus) == 0)
        d_mask.Shl();

    // calculate the product
    Vect low_bit(0x8000000000000000, 0x0000000000000000);

    while(!multiplier.IsZero())
    {
        // if the current coeff of the multiplier is set
        //   then add the multiplicand to the result
        if(!((multiplier & low_bit)==0))
            result = FieldAdd(result, multiplicand);

        multiplier.Shl();
        multiplicand.Shr();

        // if degree(multiplicand) >= degree(modulus)
        //   then subtract the modulus
        if(!((multiplicand & d_mask)==0))
            multiplicand = FieldAdd(multiplicand, modulus);
    }

    return result;
}

Vect FieldDivide(Vect dividend, Vect divisor, Vect *remainder)
{
    // position the divisor all the way to the right
    // count the degree of this divisor
    INT degree = 127;

    while((divisor & 1) == 0)
    {
        divisor.Shr();
        degree--;
    }

    Vect quotient;

    for(INT bit=127; bit >= degree; --bit)
    {
        if(dividend.Bit(127-bit))
        {
            quotient.SetBit(127-(bit-degree));

            dividend = FieldAdd(dividend, divisor);
        }

        // slide the divisor to the left across the dividend
        divisor.Shl();
    }

    *remainder = dividend;

    return quotient;
}

BOOL IsGreaterThan(Vect a, Vect b)
{
    for(INT i=0; i<128; ++i)
    {
        if(a.Bit(i) == b.Bit(i))
            continue;

        if(a.Bit(i) && !b.Bit(i))
            return 1;
        else
            return 0;
    }

    return 0;
}

Vect FieldEGCD(Vect a, Vect b, Vect primitive, Vect *r, Vect *s)
{
    Vect sum;
    Vect product;
    Vect quotient;
    Vect remainder;

    // 
    Vect gcd = 0;

    Vect r_a(0x8000000000000000, 0), s_a; // a = 1*a + 0*b
    Vect r_b, s_b(0x8000000000000000, 0); // b = 0*b + 1*a

    while(!a.IsZero() && !b.IsZero())
    {
        if(IsGreaterThan(a,b))
        {
            quotient = FieldDivide(a, b, &remainder);
            a = remainder;

            product = FieldMul(quotient, r_b, primitive);
            r_a = FieldAdd(r_a, product);       // r_a = r_a - quotient * (r_b);

            product = FieldMul(quotient, s_b, primitive);
            s_a = FieldAdd(s_a, product);       // s_a = s_a - quotient * (s_b);
        }
        else
        {
            quotient = FieldDivide(b, a, &remainder);
            b = remainder;

            product = FieldMul(quotient, r_a, primitive);
            r_b = FieldAdd(r_b, product);       // r_a = r_a - quotient * (r_a);

            product = FieldMul(quotient, s_a, primitive);
            s_b = FieldAdd(s_b, product);       // s_b = s_b - quotient * (s_a);
        }
    }

    if(!a.IsZero())
    {
        *s = s_a;
        *r = r_a;
        return a;
    }
    else
    {
        *s = s_b;
        *r = r_b;
        return b;
    }
}

Vect FieldInvert(Vect a, Vect primitive)
{
    Vect r, s;

    FieldEGCD(a, primitive, primitive, &r, &s);

    return r;
}

