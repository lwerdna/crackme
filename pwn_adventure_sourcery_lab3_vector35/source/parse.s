
global parse_uint32_hex

parse_nib:
parse_0: push   ebp
parse_1: mov    ebp,esp
parse_3: push   ebx
parse_4: mov    eax,dword [ebp+0x8]
parse_7: mov    ecx,dword [ebp+0xc]
parse_a: mov    dl,byte [eax]
parse_c: lea    eax,[edx-0x30]
parse_f: cmp    al,0x9
parse_11: ja    parse_17
parse_13: mov    byte [ecx],al
parse_15: jmp    parse_33
parse_17: lea    eax,[edx-0x61]
parse_1a: cmp    al,0x5
parse_1c: ja    parse_23
parse_1e: sub    edx,0x57
parse_21: jmp    parse_31
parse_23: lea    ebx,[edx-0x41]
parse_26: or     eax,0xffffffff
parse_29: cmp    bl,0x5
parse_2c: ja    parse_35
parse_2e: sub    edx,0x37
parse_31: mov    byte [ecx],dl
parse_33: xor    eax,eax
parse_35: pop    ebx
parse_36: pop    ebp
parse_37: ret    

parse_value_hex:
parse_38: push   ebp
parse_39: mov    ebp,esp
parse_3b: push   edi
parse_3c: push   esi
parse_3d: push   ebx
parse_3e: sub    esp,0x1c
parse_41: mov    ebx,dword [ebp+0x8]
parse_44: cmp    byte [ebx],0x30
parse_47: jne    parse_56
parse_49: mov    al,byte [ebx+0x1]
parse_4c: and    eax,0xffffffdf
parse_4f: cmp    al,0x58
parse_51: jne    parse_56
parse_53: add    ebx,0x2
parse_56: or     eax,0xffffffff
parse_59: cmp    byte [ebx],0x0
parse_5c: je    parse_af
parse_5e: mov    ecx,ebx
parse_60: xor    esi,esi
parse_62: xor    edi,edi
parse_64: mov    eax,ecx
parse_66: sub    eax,ebx
parse_68: cmp    eax,dword [ebp+0xc]
parse_6b: jge    parse_a5
parse_6d: cmp    byte [ecx],0x0
parse_70: je    parse_a5
parse_72: lea    eax,[ebp-0x11]
parse_75: mov    dword [ebp-0x24],ecx
parse_78: push   eax
parse_79: push   ecx
parse_7a: call    parse_nib
parse_7f: mov    ecx,dword [ebp-0x24]
parse_82: pop    edx
parse_83: pop    edx
parse_84: inc    ecx
parse_85: test   eax,eax
parse_87: jne    parse_a0
parse_89: mov    edx,edi
parse_8b: mov    eax,esi
parse_8d: xor    edi,edi
parse_8f: shld   edx,esi,0x4
parse_93: movzx  esi,byte [ebp-0x11]
parse_97: shl    eax,0x4
parse_9a: add    esi,eax
parse_9c: adc    edi,edx
parse_9e: jmp    parse_64
parse_a0: or     eax,0xffffffff
parse_a3: jmp    parse_af
parse_a5: mov    eax,dword [ebp+0x10]
parse_a8: mov    dword [eax],esi
parse_aa: mov    dword [eax+0x4],edi
parse_ad: xor    eax,eax
parse_af: lea    esp,[ebp-0xc]
parse_b2: pop    ebx
parse_b3: pop    esi
parse_b4: pop    edi
parse_b5: pop    ebp
parse_b6: ret    

parse_uint8_hex:
parse_b7: push   ebp
parse_b8: mov    ebp,esp
parse_ba: sub    esp,0x14
parse_bd: lea    eax,[ebp-0x8]
parse_c0: push   eax
parse_c1: push   0x2
parse_c3: push   dword [ebp+0x8]
parse_c6: call    parse_value_hex
parse_cb: add    esp,0x10
parse_ce: test   eax,eax
parse_d0: jne    parse_dc
parse_d2: mov    edx,dword [ebp+0xc]
parse_d5: mov    ecx,dword [ebp-0x8]
parse_d8: mov    byte [edx],cl
parse_da: jmp    parse_df
parse_dc: or     eax,0xffffffff
parse_df: leave  
parse_e0: ret    

parse_uint16_hex:
parse_e1: push   ebp
parse_e2: mov    ebp,esp
parse_e4: sub    esp,0x14
parse_e7: lea    eax,[ebp-0x8]
parse_ea: push   eax
parse_eb: push   0x4
parse_ed: push   dword [ebp+0x8]
parse_f0: call    parse_value_hex
parse_f5: add    esp,0x10
parse_f8: test   eax,eax
parse_fa: jne    parse_107
parse_fc: mov    edx,dword [ebp+0xc]
parse_ff: mov    ecx,dword [ebp-0x8]
parse_102: mov    word [edx],cx
parse_105: jmp    parse_10a
parse_107: or     eax,0xffffffff
parse_10a: leave  
parse_10b: ret    

parse_uint32_hex:
parse_10c: push   ebp
parse_10d: mov    ebp,esp
parse_10f: sub    esp,0x14
parse_112: lea    eax,[ebp-0x8]
parse_115: push   eax
parse_116: push   0x8
parse_118: push   dword [ebp+0x8]
parse_11b: call    parse_value_hex
parse_120: add    esp,0x10
parse_123: test   eax,eax
parse_125: jne    parse_131
parse_127: mov    edx,dword [ebp+0xc]
parse_12a: mov    ecx,dword [ebp-0x8]
parse_12d: mov    dword [edx],ecx
parse_12f: jmp    parse_134
parse_131: or     eax,0xffffffff
parse_134: leave  
parse_135: ret    

parse_uint64_hex:
parse_136: push   ebp
parse_137: mov    ebp,esp
parse_139: push   ebx
parse_13a: lea    eax,[ebp-0x10]
parse_13d: sub    esp,0x18
parse_140: push   eax
parse_141: push   0x10
parse_143: push   dword [ebp+0x8]
parse_146: call    parse_value_hex
parse_14b: add    esp,0x10
parse_14e: test   eax,eax
parse_150: jne    parse_162
parse_152: mov    edx,dword [ebp+0xc]
parse_155: mov    ecx,dword [ebp-0x10]
parse_158: mov    ebx,dword [ebp-0xc]
parse_15b: mov    dword [edx],ecx
parse_15d: mov    dword [edx+0x4],ebx
parse_160: jmp    parse_165
parse_162: or     eax,0xffffffff
parse_165: mov    ebx,dword [ebp-0x4]
parse_168: leave  
parse_169: ret    
