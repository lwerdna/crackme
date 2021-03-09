Vect FieldAdd(Vect addend_a, Vect addend_b);
Vect FieldMul(Vect multiplicand, Vect multiplier, Vect modulus);
Vect FieldDivide(Vect dividend, Vect divisor, Vect *remainder);
BOOL IsGreaterThan(Vect a, Vect b);
Vect FieldEGCD(Vect a, Vect b, Vect primitive, Vect *r, Vect *s);
Vect FieldInvert(Vect a, Vect primitive);


