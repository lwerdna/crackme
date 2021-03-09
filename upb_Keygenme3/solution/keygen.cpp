#define INFO "keygen to upb's \"keygenme 3\"/keygenme sheg - nov3_2009 andrewl/crackmes.de"

// includes
#include <windows.h>
#include <stdio.h>
#include <conio.h>

// non-default libs
#pragma comment(lib,"user32.lib")

// custom types
//
#define GATE_TYPE_AND 0
#define GATE_TYPE_NOT 1
#define GATE_TYPE_XOR 2
#define GATE_TYPE_TERMINAL 3
#define GATE_TYPE_LITERAL 4
#define GATE_TYPE_OR 5
class GATE;
class GATE
{
    public:
        GATE(UINT init_type) { this->type=init_type; this->left=0; this->right=0; }
        GATE(UINT init_type, GATE *init_left) { this->type=init_type; this->left=init_left; this->right=0; }
        GATE(UINT init_type, GATE *init_left, GATE *init_right) { this->type=init_type; this->left=init_left; this->right=init_right; }
        UINT type;
        GATE *left;
        GATE *right;
};

// globals
//
PCHAR lookup="OWNAGETHISPLZK7X";

PBYTE encodec_bits; // used by recursive circuit builder
UINT encodec_i;

// functions
//
UINT GetBits(PBYTE data,UINT start,UINT n)
{
    UINT res=0;
    while(n--)
    {
        res<<=1; // make room for new bit
        BYTE newbit=(data[start/8]&(1<<(start%8)))?1:0;
        res|=newbit;
        start++;
    }
    return res;
}

UINT DoVM(PBYTE code, PBYTE input)
// code is array of bits
{
    #define VM_ERR 3
    
    UINT stack[1024];
    UINT esp=-1;

    UINT eip=0;
    
    UINT amtA=1;
    UINT amtB=2;
    
    while(1)
    {
        BYTE opcode=GetBits(code,eip,2); eip+=2;

        BYTE operand;

        if(opcode==0)
        {
            operand=GetBits(code,eip,4); eip+=4;

            // xor
            if(operand==0)
            {
                if(esp<1) return VM_ERR;
                stack[esp-1]^=stack[esp];
                esp--;
            }
            // and
            else if(operand==2)
            {
                if(esp<1) return VM_ERR;
                stack[esp-1]&=stack[esp];
                esp--;
            }
            // return
            else if(operand==4)
            {
                if(esp!=0) return VM_ERR;
                return stack[esp];  
            }
            else
                return VM_ERR;  
        }
        else if(opcode==1)
        {
            // push input
            operand=GetBits(code,eip,amtB); eip+=amtB;

            if(operand>=4)
                return VM_ERR;
            esp++;
            stack[esp]=input[operand];
        }
        else if(opcode==2)
        {
            // push immediate
            operand=GetBits(code,eip,amtA); eip+=amtA;
            esp++;
            stack[esp]=operand;
        }
        else if(opcode==3)
        {
            // change addressing size??
            operand=GetBits(code,eip,2); eip+=2;

            if(operand==0)
            {
                amtB=GetBits(code,eip,8);
                eip+=8;
            }
            else if(operand==1)
            {
                amtA=GetBits(code,eip,8);
                eip+=8;
            }
            else
                return VM_ERR;
        }
    }
}

VOID display_circuit(GATE *circuit, UINT depth)
{
    if(!circuit)
        return;
    
    for(INT i=0; i<depth; ++i)
        printf("  ");

    if(circuit->type==GATE_TYPE_AND)
    {
        printf("AND\n");
        display_circuit(circuit->left,depth+1);
        display_circuit(circuit->right,depth+1);
    }
    if(circuit->type==GATE_TYPE_NOT)
    {
        printf("NOT\n");
        display_circuit(circuit->left,depth+1);
    }
    if(circuit->type==GATE_TYPE_TERMINAL)
        printf("b%d\n",circuit->left);
    if(circuit->type==GATE_TYPE_LITERAL)
        printf("%s",circuit->left?"TRUE\n":"FALSE\n");
    if(circuit->type==GATE_TYPE_OR)
    {
        printf("OR\n");
        display_circuit(circuit->left,depth+1);
        display_circuit(circuit->right,depth+1);
    }
}

VOID encode_circuit(GATE *circuit)
{
    if(!circuit)
        return;

    if(circuit->type==GATE_TYPE_TERMINAL)
    {
        // push mem
        encodec_bits[encodec_i++]=0; // opcode: 1
        encodec_bits[encodec_i++]=1;
        encodec_bits[encodec_i++]=(((UINT)circuit->left) & 2)?1:0; // hi bit of mem index
        encodec_bits[encodec_i++]=((UINT)circuit->left)&1; // lo bit of mem index
        printf("PUSH INPUT[%d]\n",circuit->left);
    }
    if(circuit->type==GATE_TYPE_LITERAL)
    {
        // push immediate
        encodec_bits[encodec_i++]=1; // opcode: 2
        encodec_bits[encodec_i++]=0;
        encodec_bits[encodec_i++]=circuit->left?1:0; // operand: 0 or 1
        printf("PUSH IMMEDIATE %d\n",circuit->left); 
    }
    if(circuit->type==GATE_TYPE_AND)
    {
        encode_circuit(circuit->left);
        encode_circuit(circuit->right);
        encodec_bits[encodec_i++]=0; // opcode: 0
        encodec_bits[encodec_i++]=0; //
        encodec_bits[encodec_i++]=0; // operand: 2
        encodec_bits[encodec_i++]=0; //
        encodec_bits[encodec_i++]=1; //
        encodec_bits[encodec_i++]=0; //
        printf("AND\n");
    }
    if(circuit->type==GATE_TYPE_NOT)
    {
        encode_circuit(circuit->left);
        // not is encoded with a push immediate of 1
        encodec_bits[encodec_i++]=1;
        encodec_bits[encodec_i++]=0; // opcode: 2
        encodec_bits[encodec_i++]=1; // operand: 1
        // followed by an xor
        encodec_bits[encodec_i++]=0; // opcode: 0
        encodec_bits[encodec_i++]=0; //
        encodec_bits[encodec_i++]=0; // operand: 0
        encodec_bits[encodec_i++]=0; //
        encodec_bits[encodec_i++]=0; //
        encodec_bits[encodec_i++]=0; //
        printf("NOT\n");
    }
}

// not(not(a)) == a
VOID prune_nots(GATE *circuit)
{
    if(!circuit || circuit->type == GATE_TYPE_TERMINAL || circuit->type == GATE_TYPE_LITERAL)
        return;

    if(circuit->left && circuit->left->type==GATE_TYPE_NOT)
        if(circuit->left->left && circuit->left->left->type==GATE_TYPE_NOT)
            circuit->left=circuit->left->left->left;

    if(circuit->right && circuit->right->type==GATE_TYPE_NOT)
        if(circuit->right->right && circuit->right->right->type==GATE_TYPE_NOT)
            circuit->right=circuit->right->right->right;

    prune_nots(circuit->left);
    prune_nots(circuit->right);
}

VOID GenTargetBuffer(PCHAR name, BYTE target[16])
{
    memset(target,0,16);
    for(INT i=0; i<128; ++i)
        target[i%16]^=GetBits((PBYTE)lookup,i,1);
    for(INT i=0; i<strlen(name)*8; ++i)
        target[i%16]^=GetBits((PBYTE)name,i,1);
}

INT main(INT ac,PCHAR *av)
{
    printf("\n" INFO "\n\n");

    PCHAR name="upb";
    if(ac>1)
        name=av[1];
    else
        printf("supply argument to generate for different name\n");

    // generate target buffer
    //
    BYTE target[16];
    GenTargetBuffer(name,target);
    printf("16 target bits: ");
    for(INT i=0; i<16; ++i)
        printf("%d ",target[i]);
    printf("\n");

    // on the i'th iteration [0,15], the i'th bit in the target array is not checked!
    // here is lookup:
    UINT iterToCheckedBit[16]={0,8,4,12,2,10,6,14,1,9,5,13,3,11,7,15};

    // build circuit... not going to get too fancy here, there are possibly 64 leaf nodes
    //

    GATE *phase1[64]; // literals and complements of literals using terminals and inverters

    for(INT i=0; i<16; ++i)
    {
        phase1[i*4]=new GATE(GATE_TYPE_TERMINAL, (GATE *)3);    // input[3] is bit0 of the count [0..15]
        if(!(i&1))
            phase1[i*4]=new GATE(GATE_TYPE_NOT,phase1[i*4]);

        phase1[i*4+1]=new GATE(GATE_TYPE_TERMINAL, (GATE *)2);  // input[2] is bit1
        if(!(i&2))
            phase1[i*4+1]=new GATE(GATE_TYPE_NOT,phase1[i*4+1]);

        phase1[i*4+2]=new GATE(GATE_TYPE_TERMINAL, (GATE *)1);  // input[1] is bit2
        if(!(i&4))
            phase1[i*4+2]=new GATE(GATE_TYPE_NOT,phase1[i*4+2]);

        phase1[i*4+3]=new GATE(GATE_TYPE_TERMINAL, (GATE *)0);  // input[0] is bit3
        if(!(i&8))
            phase1[i*4+3]=new GATE(GATE_TYPE_NOT,phase1[i*4+3]);
    }

    GATE *phase2[16]; // conjuction of literals using and

    for(INT i=0; i<16; ++i)
    {
        if(!target[iterToCheckedBit[i]])
        //if(!target[i]) // for testing
            phase2[i] = new GATE(GATE_TYPE_LITERAL,0);
        else
            phase2[i] = new GATE(   GATE_TYPE_AND,
                                    new GATE(   GATE_TYPE_AND,
                                                new GATE(   GATE_TYPE_AND,
                                                            phase1[i*4],
                                                            phase1[i*4+1]
                                                        ),
                                                phase1[i*4+2]
                                            ),
                                    phase1[i*4+3]
                                );
    }

    //
    // join the conjunctions with OR's
    // remember we synthesize OR's using /AND(/A,/B)
    GATE *circuit = new GATE(   GATE_TYPE_NOT,
                                new GATE(   GATE_TYPE_AND,
                                            new GATE(   GATE_TYPE_NOT,
                                                        phase2[0]
                                                    ),
                                            new GATE(   GATE_TYPE_NOT,
                                                        phase2[1]
                                                    )
                                        )
                            );

    for(INT i=2; i<16; ++i)
        circuit = new GATE(   GATE_TYPE_NOT,
                                new GATE(   GATE_TYPE_AND,
                                            new GATE(   GATE_TYPE_NOT,
                                                        circuit
                                                    ),
                                            new GATE(   GATE_TYPE_NOT,
                                                        phase2[i]
                                                    )
                                        )
                            );

    // prune away double not's
    //
    prune_nots(circuit);

    printf("circuit:\n"); 
    display_circuit(circuit,0);
    printf("\n");

    //
    // k now encode the gates into a serial
    BYTE bits[2048];
    encodec_bits=bits;
    encodec_i=0;           

    printf("\nencoding circuit to bits (instructions for VM)...\n");
    encode_circuit(circuit);
    // add a return
    encodec_bits[encodec_i++]=0; // opcode: 0
    encodec_bits[encodec_i++]=0; //
    encodec_bits[encodec_i++]=0; // operand: 4
    encodec_bits[encodec_i++]=1; //
    encodec_bits[encodec_i++]=0; //
    encodec_bits[encodec_i++]=0; //
    printf("encoded %d bits\n",encodec_i);
    while(encodec_i%8)
        encodec_bits[encodec_i++]=0;

    // convert to bytes
    CHAR encoded[256];
    memset(encoded,0,256);
    UINT n_bytes=encodec_i/8;
    for(INT i=0;i<n_bytes;++i)
        encoded[i]=encodec_bits[i*8] |
                    (encodec_bits[i*8+1]<<1) |
                    (encodec_bits[i*8+2]<<2) |
                    (encodec_bits[i*8+3]<<3) |
                    (encodec_bits[i*8+4]<<4) |
                    (encodec_bits[i*8+5]<<5) |
                    (encodec_bits[i*8+6]<<6) |
                    (encodec_bits[i*8+7]<<7);
  
    printf("\n");
    for(UINT i=0;i<n_bytes;++i)
        printf("%02X ", encoded[i]&0xFF);
    printf("\n");

    // simulate
    printf("\nsimulating in new VM...\n");
    for(UINT i=0; i<16; ++i)
    {
        BYTE input[4];
        input[0]=(i&8)>>3;
        input[1]=(i&4)>>2;
        input[2]=(i&2)>>1;
        input[3]=i&1;
        printf("on input %d%d%d%d, DoVM() returned %d\n",input[0],input[1],input[2],input[3],DoVM((PBYTE)encoded,input));
    }

    // encode that to base16 with crackme alphabet
    printf("n_bytes: %d\n",n_bytes);
    CHAR serial[512];
    memset(serial,0,512);
    for(INT i=0;i<n_bytes;++i)
    {
        serial[2*i]=lookup[(encoded[i]&0xF0)>>4];
        serial[2*i+1]=lookup[(encoded[i]&0xF)];
    }

    // finally done :)
    printf("\n**********************************************************\n");
    printf("  USER:\n");
    printf("    %s\n", name);
    printf("SERIAL:\n");
    printf("    %s\n", serial);
    printf("**********************************************************\n");

    printf("----- hit a key to copy the serial to clipboard, ctrl+c to quit\n");
    _getch();

    OpenClipboard(NULL);
    EmptyClipboard();
    HGLOBAL hData = GlobalAlloc(GMEM_DDESHARE, strlen(serial)+1);
    PCHAR pdata = (PCHAR)GlobalLock(hData);
    memcpy(pdata,serial,strlen(serial)+1);
    GlobalUnlock(hData);
    SetClipboardData(CF_TEXT, hData);
    CloseClipboard();

    printf("----- hit a key to close\n");
    _getch();
}
