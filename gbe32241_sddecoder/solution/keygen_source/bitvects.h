class Vect;
class Vect
{
    public:
    Vect();
    Vect(UINT64 a);
    Vect(UINT64 a, UINT64 b);
    UINT GetFirstBitSetPosition();
    VOID Xor(Vect a); 
    VOID And(Vect a);
    BOOL IsZero();
    VOID Zero();
    BYTE Bit(UINT n);
    VOID SwapBits(UINT a, UINT b);
    VOID SetBit(UINT n);
    VOID Vect::SetBitTo(UINT n, CHAR value);
    VOID ClearBit(UINT n);
    VOID SwapBit(UINT a, UINT b);
    VOID Shl();
    VOID Shr();
    INT CountBits();
    VOID Random();
    VOID Vect::Print();
    VOID Vect::Print(PCHAR);
    VOID Vect::Println();
    VOID Vect::PrintPari();
    bool Vect::operator==(const Vect &other) const;
    const Vect Vect::operator+(const Vect &other) const;
    const Vect Vect::operator&(const Vect &other) const;
    const Vect Vect::operator|(const Vect &other) const;
    bool Vect::operator!=(const Vect &other) const;

    UINT64 lo;
    UINT64 hi;
};

class BitBasis
{
    public:
    BitBasis();
    VOID Add(UINT64 v1, UINT64 v2);
    VOID Add(Vect a);
    VOID AddFast(UINT64 v1, UINT64 v2);
    VOID AddFast(Vect a);
    VOID AddN(PUINT64 p, UINT n);
    VOID RowReduce();
    VOID Print();
    VOID Print(PCHAR name);
    VOID PrintPari(PCHAR name);
    Vect SpanRandom();
    Vect ChooseRows(Vect a);
    BOOL DoesSpan(Vect a);
    VOID SpanAllInit();
    BOOL SpanAllNext(Vect *a);
    VOID Join(BitBasis a);
    UINT64 span_i;
    UINT64 span_i_limit;
    Vect SolveRowsFor(Vect target);

    Vect vects[129]; 
    UINT dimension;
};

