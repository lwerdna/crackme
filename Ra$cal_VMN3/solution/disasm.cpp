// 2008 andrewl

// os
#include <windows.h>

// stdlib
#include <stdio.h>

// others libs
#pragma include_alias("extern.h", "c:\\code\\lib\\udis86\\extern.h")
#pragma comment(lib, "c:\\code\\lib\\udis86\\udis86.lib")
#include "extern.h" //udis86

// our stuff
#include "VM_Code.h"


// cool globals
PCHAR   context_dw_offs[] = {"ESI", "ESI", "EBP", "ESP", "EBX", "EDX", "ECX", "EAX", "EFLAGS"};

ULONG jump_label_to_vm_eip(ULONG jump_label)
{
    UINT EIP = 0x00407000;

    for(int i=0; i<sizeof(VM_Code); )
    {
        ULONG jmp_label = *(PULONG)(VM_Code+i+2);
        UINT size_instr = 0x0F + *(VM_Code+i+6);

        if(jmp_label == jump_label)
            return EIP;

        i+=size_instr;
        EIP+=size_instr;
    }

    printf("MOTHERbadwordIN' A!!!!!!!!!!!!!!!!!!!!!!!\n");

    return 0;
}

void main(void)
{
    UINT EIP = 0x00407000;

    UINT i = 0;

    UINT total_instrs=0;

    // UDIS86 Stuff
    ud_t ud_obj={0};
    ud_init(&ud_obj);
    ud_set_mode(&ud_obj, 32);
    ud_set_syntax(&ud_obj, UD_SYN_INTEL);

    for(i=0; i<sizeof(VM_Code); )
    {
        USHORT  opcode = *(PUSHORT)(VM_Code+i);
        ULONG   jmp_label = *(PULONG)(VM_Code+i+2);
        UINT    size_instr = 0x0F + *(VM_Code+i+6);
        ULONG   jmp_label_next = *(PULONG)(VM_Code+i+7);
        UCHAR   fbyte = *(VM_Code+i+0x0F);

        //printf("size_instr: %d\n", size_instr);

        printf("%08X: [%02X] ", EIP, opcode);

        switch(opcode)
        {
            //
            // put encoded call to memory, call
            //
            case 0x0001:
                {
                    DWORD   dest = *(PDWORD)(VM_Code+i+0x0F);
                    
                    printf("call ");
                    
                    if(dest==0xCEDAC8C3)
                        printf("kernel32!strlenA");
                    if(dest==0xCEDAC8C0)
                        printf("kernel32!GetComputerNameA");
                    if(dest==0x8EDAC8C6)
                        printf("user32!SetDlgItemTextA");
                    if(dest==0x8EDAC8C7)
                        printf("user32!SetDlgItemIntA");
                    if(dest==0x4EDAC8C6)
                        printf("user32!MessageBoxA");
                }
                
                break;

            case 0x0002:
                {
                   
                    ULONG   oper1 = *(PULONG)(VM_Code+i+0x0F);
                    ULONG   oper2 = *(PULONG)(VM_Code+i+0x13);

                    // dobfuscate operand 1
                        __asm
                        {
                            mov eax, [oper1];
                            mov ebx, 0x4C5BC478
                            mov ecx, 0x04;

                            again:
                            xor eax, ebx
                            ror eax, 7
                            rol ebx, 0x10
                            dec ecx
                            jnz again
                            xor eax, ebx

                            mov ebx, [oper2]
                            mov ecx, 4

                            again2:
                            xor eax, ebx
                            ror eax, 7
                            rol ebx, 0x10
                            dec ecx
                            jnz again2
                            xor eax, ebx

                            mov [oper1], eax
                        }

                    USHORT  cmdbyte = *(PUSHORT)(VM_Code+i+0x17);

                    cmdbyte ^= 0x9E3C;
                    UCHAR cmdbytelo = cmdbyte & 0x00FF;
                    UCHAR cmdbytehi = (cmdbyte & 0xFF00) >> 8;

                    // printf("CMDBYTE after xor is %04X\n", cmdbyte);

                    if((cmdbytehi & 0x0F) != 1)
                       printf("WTF on OP 02!!!!!\n");

                    // printf("looking up jump label %08X\n", oper1);
                    PCHAR mnem_lookup[] = {"jz", "jnz", "jg", "jwhat3", "jwhat4", "jnc", "jns"};

                    printf("%s 0x%X", mnem_lookup[cmdbytelo], jump_label_to_vm_eip(oper1));
                }

                break;

            case 0x0003:
                {
                    ULONG   jump_label = *(PULONG)(VM_Code+i+0x02);
                    ULONG   dword0f = *(PULONG)(VM_Code+i+0x0F);

                    //printf("jump label: %08X\n", jump_label);
                    //printf("dword0f before: %08X\n", dword0f);

                    __asm
                    {
                        mov eax, [dword0f]
                        mov ebx, [jump_label]
                        mov ecx, 4

                        lala:
                        xor eax, ebx
                        ror eax, 7
                        rol ebx, 0x10
                        dec ecx
                        jnz lala
                        xor eax, ebx

                        mov ebx, 0x4C5BC478
                        mov ecx, 4

                        lala2:
                        xor eax, ebx
                        ror eax, 7
                        rol ebx, 0x10
                        dec ecx
                        jnz lala2
                        xor eax, ebx

                        mov [dword0f], eax
                    }

                    printf("push 0x%X", dword0f);
                }

                break;

            case 0x0004:
                {
                    UCHAR   byte0f = *(PUCHAR)(VM_Code+i+0x0F);
                    ULONG   oper1 = *(PULONG)(VM_Code+i+0x10);

                    if((byte0f & 0x03) != 0)
                        printf("WTTTFFFFFFF in op 04!\n");

                    __asm
                    {
                        mov eax, [oper1]
                        mov ebx, 0x4C5BC478
                        mov ecx, 4
                        repll:
                        xor eax, ebx
                        ror eax, 7
                        rol ebx, 0x10
                        dec ecx
                        jnz repll
                        xor eax, ebx
                        mov [oper1], eax
                    }

                    if((byte0f >> 4)==0)
                        printf("add esp, 0x%X", oper1);
                    else if((byte0f >> 4)==1)
                        printf("sub esp, 0x%X", oper1);
                    else
                        printf("WTf in op 04\n");
                }

                break;

            case 0x0006:
                {
                    UCHAR   byte0f = *(PUCHAR)(VM_Code+i+0x0F);
                    ULONG   oper1 = *(PULONG)(VM_Code+i+0x11);

                    if((byte0f >> 4) != 0)
                        printf("WTF in op 06!\n");

                    printf("mov dword [esp], 0x%X", oper1);
                }
                
                break;

            case 0x0007:
                {
                    UCHAR   byte0f = *(PUCHAR)(VM_Code+i+0x0F);
                    ULONG   oper1 = *(PULONG)(VM_Code+i+0x10);
                    ULONG   oper2 = *(PULONG)(VM_Code+i+0x14);

                        __asm
                        {
                            mov eax, [oper1];
                            mov ebx, [oper2];
                            mov ecx, 0x04;

                            againz:
                            xor eax, ebx
                            ror eax, 7
                            rol ebx, 0x10
                            dec ecx
                            jnz againz
                            xor eax, ebx
                            mov [oper1], eax
                        }

                    if(byte0f == 0)
                        printf("WTF in op 07!!!!!!!!!!!!!!!\n");
                    if(oper1 == 0xFFFFFFFF)
                        printf("WTF2 in op 07!!!!!!!!!!!!!!!\n");

                    printf("jmp 0x%X", jump_label_to_vm_eip(oper1));
                }

                break;

            case 0x0010:
                {
                    UCHAR   vm_mem_offs = *(VM_Code+i+0x10);
                    INT     oper1 = *(PINT)(VM_Code+i+0x11);
                    UCHAR   cmdbyte = *(VM_Code+i+0x15);

                    if(cmdbyte == 0)
                    {
                        printf("VM_mem[%i] = %s", vm_mem_offs, context_dw_offs[fbyte]);
                        
                        if(oper1>=0)
                            printf("+");
                        else
                        {
                            printf("-");
                            oper1 *= -1;
                        }

                        printf("0x%X", oper1);
                    }
                    else
                        printf("WTF!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
                }

                break;

            case 0x0011:
                {
                    UCHAR   cmdbyte = *(VM_Code+i+0x17);
                    ULONG   oper1 = *(PULONG)(VM_Code+i+0x0F);
                    ULONG   oper2 = *(PULONG)(VM_Code+i+0x13);

                    if(cmdbyte == 3)
                        printf("[0x%08X] = [0x%08X]", oper1, oper2);
                    else if(cmdbyte == 1)
                        printf("%s = 0x%X", context_dw_offs[oper1], oper2);
                    else if(cmdbyte == 2)
                        printf("*VM_mem[%d] = 0x%X", oper1, oper2);
                    else if(cmdbyte == 0)
                        printf("*VM_mem[%d] = %s", oper1, context_dw_offs[oper2]);
                    else
                        printf("WHAT THE MOTHERbadwordIN' HELL DUDE?\n");
                }

                break;

            case 0x0012:
                {
                    UCHAR   cmdbyte = *(VM_Code+i+0x17);
                    ULONG   oper1 = *(PULONG)(VM_Code+i+0x0F);
                    ULONG   oper2 = *(PULONG)(VM_Code+i+0x13);

                    if(cmdbyte == 3)
                        printf("[%08X+4] = [[%08X]]", oper1, oper1);
                    else if(cmdbyte == 1)
                        printf("%s = 0x%08X", context_dw_offs[oper2], oper1);
                    else if(cmdbyte == 2)
                        printf("%s = 0x%08X", context_dw_offs[oper1], oper2); // mov immediate
                    else if(cmdbyte == 0)
                        printf("%s = *VM_mem[%d]", context_dw_offs[oper1], oper2);
                    else
                        printf("WHAT THE MOTHERbadwordIN' HELL, DUDE?\n");
                }

                break;
            //
            // put encoded instruction to memory, execute it in Context0
            //
            case 0x000A:
                {
                    UCHAR   instr_buff[64] = {0};
                    UINT    num_bytes = size_instr - 0x0F;

                    memcpy(instr_buff, VM_Code+i+0x0F, num_bytes);

                    UINT    var_ecx = num_bytes;
                    UINT    var_edx = 0x4C5BC478;
                    PUCHAR  var_esi = instr_buff;

                    __asm
                    {   
                        mov ecx, [var_ecx];
                        mov edx, [var_edx];
                        mov esi, [var_esi];

                        loc_40282B:
                        mov al, [esi]
                        mov bl, dl
                        rol al, cl
                        xor al, dl
                        mov [esi], al
                        inc esi
                        dec ecx
                        rol edx, 8
                        test ecx, ecx
                        jnz loc_40282B
                    }

                    ud_set_pc(&ud_obj, EIP);
                    ud_set_input_buffer(&ud_obj, (uint8_t *)instr_buff, 64);
                    ud_disassemble(&ud_obj);
                    printf("%s", ud_insn_asm(&ud_obj));
                }

                break;

            case 0x0013:
                {
                    UCHAR   byte17 = *(PUCHAR)(VM_Code+i+0x17);
                    ULONG   oper1 = *(PULONG)(VM_Code+i+0x0F);
                    ULONG   oper2 = *(PULONG)(VM_Code+i+0x13);

                    byte17 &= 0x03;

                    //printf("DARCAR: %04X\n", byte17);
                    //printf("oper1: %X\n", oper1);
                    //printf("oper2: %X\n", oper2);

                    if(byte17 == 3)
                        printf("mov dword [0x%X], 0x%X", oper1, oper2);
                    else if(byte17 == 1)
                        printf("mov %s, dword [0x%X]", context_dw_offs[oper2], oper1);
                    else if(byte17 == 0)
                        printf("xor %s, *VM_Mem[0x%X]", context_dw_offs[oper1], oper2);
                    else if(byte17 == 2)
                        printf("xor %s, *VM_Mem[0x%X] (with missing ror???)", context_dw_offs[oper1], oper2);
                    else
                        printf("major wtf in op 0C\n");
                    break;
                }

            case 0x0014:
                {
                    UCHAR   byte0F = *(PUCHAR)(VM_Code+i+0x0F);
                    UCHAR   byte10 = *(PUCHAR)(VM_Code+i+0x10);

                    /*
                    printf("source = VM_memory[0x%X] ([0x%08X])\n", byte0F, 0x405250+(byte0F<<2));
                    printf("               ");
                    printf("dest = VM_mem2+0x%X (0x%08X)\n", byte10<<5, 0x4051F0+(byte10<<5));
                    printf("               ");
                    printf("memset(dest, 0, 32)\n");
                    printf("               ");
                    printf("dest gets byte spread of bits from source");
                    */

                    printf("VM_mem2+0x%X (0x%08X) = spread bits to bytes from VM_memory[0x%X] ([0x%08X])",
                            byte10<<5,
                            0x4051F0+(byte10<<5),
                            byte0F, 
                            0x405250+(byte0F<<2)
                            );
                }

                break;

            case 0x0015:
                {
                    UCHAR   byte0F = *(PUCHAR)(VM_Code+i+0x0F);
                    UCHAR   byte10 = *(PUCHAR)(VM_Code+i+0x10);

                    printf("[VM_memory+0x%X] ([0x%08X]) = unspread bytes to bits from VM_mem2+0x%X (0x%08X)", 
                            byte0F<<2,
                            0x405250+(byte0F<<2),
                            byte10<<5,
                            0x4051F0+(byte10<<5)
                            );
                }

                break;

            case 0x0016:
                {
                    UCHAR   byte0F = *(PUCHAR)(VM_Code+i+0x0F);
                    UCHAR   byte10 = *(PUCHAR)(VM_Code+i+0x10);
                    UCHAR   byte11 = *(PUCHAR)(VM_Code+i+0x11);
                    UCHAR   byte12 = *(PUCHAR)(VM_Code+i+0x12);
                    UCHAR   byte13 = *(PUCHAR)(VM_Code+i+0x13);

                    printf("[VM_mem2+0x%X] ([0x%08X]) ^= [VM_mem2+0x%X] (0x%08X)", 
                            (byte0F<<5)+byte11,
                            0x4051F0+(byte0F<<5)+byte11,
                            (byte10<<5)+byte11,
                            0x4051F0+(byte10<<5)+byte11
                            );
                }

                break;

            case 0x0017:
                {
                    UCHAR   byte0F = *(PUCHAR)(VM_Code+i+0x0F);
                    UCHAR   byte10 = *(PUCHAR)(VM_Code+i+0x10);
                    UCHAR   byte11 = *(PUCHAR)(VM_Code+i+0x11);

                    if(byte11 == 1)
                        printf("VM_Mem[0x%X] = %s", byte0F, context_dw_offs[byte10]);
                    else if(byte11 == 0)
                        printf("%s = VM_Mem[0x%0X]", context_dw_offs[byte10], byte0F);
                    else
                        printf("major wtf in op 0017!!!\n");
                }

                break;

            case 0x0018:
                {
                    UCHAR   byte0F = *(PUCHAR)(VM_Code+i+0x0F);
                    UCHAR   byte10 = *(PUCHAR)(VM_Code+i+0x10);
                    UCHAR   byte11 = *(PUCHAR)(VM_Code+i+0x11);
                    UCHAR   byte12 = *(PUCHAR)(VM_Code+i+0x12);
                    UCHAR   byte13 = *(PUCHAR)(VM_Code+i+0x13);

                    printf("VM_Mem2+0x%X (0x%08X) <xor %d bytes> VM_Mem2+0x%X (0x%08X)", 
                        (byte12<<5) + byte13 - byte11 + 1,
                        0x4051F0+(byte12<<5) + byte13 - byte11 + 1,
                        byte11,
                        (byte0F<<5) + byte10 - byte11 + 1,
                        0x4051F0+(byte0F<<5)+byte10 - byte11 + 1
                        );
                }

                break;

            case 0x0019:
                {
                    UCHAR   byte0F = *(PUCHAR)(VM_Code+i+0x0F);

                    printf("zero 32 bytes at VM_mem2+0x%X (0x%08X)", byte0F<<5, 0x004051F0 + (byte0F << 5));
                }

                break;

            case 0x000D:
                {
                    printf("[esp] = deobfuscate_string([esp])");
                }

                break;

            default:
                __asm
                {
                    nop
                }
        }


        printf("\n");

        i += size_instr;
        EIP += size_instr;
        total_instrs++;
    }

    printf("Total instructions: %d\n", total_instrs);
}
